#include "analogue.h"
#include <iostream>
#include <stdio.h>

Analogue::Analogue(double r) : LV2::Plugin<Analogue, LV2::URIMap<true> >(p_n_ports) {
    //license notice
    std::cout << std::endl;
    std::cout << "Analogue v.0.1, Copyright (c) 2011 Timo Westkämper" << std::endl;
    std::cout << "This is free software, and you are welcome to redistribute it" << std::endl;
    std::cout << "under certain conditions; see LICENSE file for details." << std::endl;
    std::cout << std::endl;

    // TODO : presets

    rate = r;
    m_midi_input = 0;
    m_midi_type = Parent::uri_to_id(LV2_EVENT_URI, "http://lv2plug.in/ns/ext/midi#MidiEvent"); 

    synthUI = new CollectorUI();
    synthUI->setOutputs(outputs);

    synth = createDSP();
    synth->init((int)r);
    synth->buildUserInterface(synthUI);
  
    // zones for MIDI data
    //pitchBend = synthUI->getZone("pitchBend");
    //breathControl = synthUI->getZone("breathControl");

    char buffer[32];
    for (int i = 0; i < NVOICES; i++) {
        sprintf(buffer, "midi_pitch%d", i);
        pitch[i] = synthUI->getZone(buffer);
        sprintf(buffer, "midi_gain%d", i);
        gain[i] = synthUI->getZone(buffer);
        sprintf(buffer, "midi_gate%d", i);
        gate[i] = synthUI->getZone(buffer);
    }

    // zones for control ports
    for (int i = 0; i < p_n_ports - 3; i++) {
        zones[i] = synthUI->getZone(p_port_meta[i].symbol);
        if (zones[i] == 0) {
            // TODO Exception
            std::cout << "No zone for " << p_port_meta[i].symbol << std::endl;
        }
    }

    std::cout << "ready" <<std::endl;
}

Analogue::~Analogue() {
    delete synthUI;
    delete synth;
}

void Analogue::setVolumeControl(float value) {
    // TODO    
}

void Analogue::setBreathControl(float value) {
    std::cout << "b " << value<< std::endl;
    //*breathControl = value;
}

void Analogue::setPitchBend(float value) {
     //*pitchBend = value;
}

void Analogue::on(unsigned char key, unsigned char velo) { 
    std::cout << "on " << (int)key << std::endl;
    for (int i = 0; i < NVOICES; i++) {
        if (*gate[i] == 0.0f) {
            *gate[i] = 1.0f;
            *pitch[i] = (float)key;
            *gain[i] = scale_midi_to_f(velo);
            return;
        }
    }

    // TODO : proper voice stealing
    // take first voice, if no other could be allocated
    *gate[0] = 1.0f;
    *pitch[0] = (float)key;
    *gain[0] = scale_midi_to_f(velo);
}

void Analogue::off(unsigned char key, unsigned char velo) { 
    std::cout << "off " << (int)key << std::endl; 
    float fkey = (float)key;
    for (int i = 0; i < NVOICES; i++) {
        if (*pitch[i] == fkey) {
            *gate[i] = 0.0f;
            //*gain[i] = 0.0f;
            return;
        }
    }

    std::cout << "No active voice for " << (int)key << std::endl;
}

void Analogue::render(uint32_t from, uint32_t to) {
    //std::cout << "render" << std::endl;    
    // copy control port values to faust zones
    for (int i = 0; i < p_n_ports - 3; i++) {   
        *zones[i] = *p(i + 3);
    }

    // set audio buffers
    outputs[0] = &p(p_audio_l)[from];
    outputs[1] = &p(p_audio_r)[from];

    // render output via FAUST dsp  
    synth->compute(to - from, 0, outputs);    
}
    
void Analogue::run(uint32_t sample_count) {
    LV2_Event_Iterator iter;
    lv2_event_begin(&iter, p < LV2_Event_Buffer>(m_midi_input));
      
    uint8_t* event_data;
    uint32_t samples_done = 0;
      
    while (samples_done < sample_count) {
        uint32_t to = sample_count;
        LV2_Event* ev = 0;
        if (lv2_event_is_valid(&iter)) {
            ev = lv2_event_get(&iter, &event_data);
            to = ev->frames;
            lv2_event_increment(&iter);
        }

        if (to > samples_done) {
            render(samples_done, to);
            samples_done = to;
        }

        /* This is what we do with events:
           - if it's a MIDI event, pass it to handle_midi()
           - if it's something else, just ignore it (it's safe)
        */
        if (ev) {
            if (ev->type == m_midi_type) {
                handle_midi(ev->size, event_data);
            }         
        }
    }
      
}

void Analogue::handle_midi(uint32_t size, unsigned char* data) {
    //discard invalid midi messages
    if (size < 2) {
        return;
    }    

    //receive on all channels
    switch(data[0] & 0xf0) {

        //note off 
        case 0x80: {
            //discard invalid midi messages
            if (size != 3) {
                return;
            }               
            off(data[1], data[2]);
        }
        break;

        //note on
        case 0x90: {
            //discard invalid midi messages
            if (size != 3) {
                return;
            }
            on(data[1], data[2]);                
        }
        break;

        //pitch bend
        case 0xE0: {
            //discard invalid midi messages
            if (size != 3) {
               return;
        }
        
                setPitchBend(scale_pitchbend_to_f(data[1], data[2]));
        }
        break;
    
    case 0xB0: //controller
        //WIP: control preset parameters with assigned controllers
        {
            /*signed char param_id = -1;
        param_id = get_param_id_from_controller(data[1]);                
        if (param_id >= 0) {
            float new_value = scale_midi_to_f(data[2]);
            setParameter(param_id, new_value);
        }*/
        }

        // standard controller stuff
        switch(data[1])
        {
            //mod wheel
        case 0x01: 
            //discard invalid midi messages
            if (size != 3) {
                return;
            }                    
            //scale the mod value to cover the range [0..1]
            // DO NOTHING
                    std::cout << "mod " << (int)data[2] << std::endl;        
            break;

        // breath
        case 0x02:
            //discard invalid midi messages
            if (size != 3) {
                return;
            }                    
            setBreathControl(scale_midi_to_f(data[2]));
            break;

        //volume
        case 0x07:
            //discard invalid midi messages
            if (size != 3) {
                return;
            }                    
        
            setVolumeControl(scale_midi_to_f(data[2]));
            break;

        default:
            // TODO
            break;
        }
        break;

    default: 
        break;
    }
}

static int _ = Analogue::register_class(p_uri);
