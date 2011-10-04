#include <gtkmm.h>
#include <lv2gui.hpp>

#include "knob.h"
#include "analogue.peg"
#include "analogue-meta.h"
#include <string.h>

using namespace sigc;
using namespace Gtk;

class AnalogueGUI : public LV2::GUI<AnalogueGUI, LV2::URIMap<true>, LV2::WriteMIDI<false> > {
    public:

        AnalogueGUI(const std::string& URI) {
            int control_ports = p_n_ports - 3;

            //initialize sliders
            for (int i = 0; i < control_ports; i++) {
                Knob* knob = new Knob(p_port_meta[i].min, p_port_meta[i].max, p_port_meta[i].step);
                if (isEnvControl(i)) {
                    knob->set_size(30);
                    knob->set_radius(10);
                    knob->set_line_width(1.5);
                } else if (isModControl(i)) {
                    knob->set_radius(12.0);
                }
                scales[i] = manage(knob);                
            }

            //connect widgets to control ports (change control values when sliders are moved)
            for (int i = 0; i < control_ports; i++) {
                slot<void> slot1 = compose(bind<0>(mem_fun(*this, &AnalogueGUI::write_control), i + 3),
                    mem_fun(*scales[i], &Knob::get_value));
                slot<void> slot2 = compose(bind<0>(mem_fun(*this, &AnalogueGUI::change_status_bar), i + 3),
                    mem_fun(*scales[i], &Knob::get_value));
                scales[i]->signal_value_changed().connect(slot1);
                scales[i]->signal_value_changed().connect(slot2);
            }

            //connect all faders to the 'notify' function to inform the plugin to recalculate
            /*for (int i = 0; i < control_ports; i++) {
                scales[i]->signal_value_changed().connect(
            mem_fun(*this, &AnalogueGUI::notify_param_change));
            }*/

            HBox* header = manage(new HBox());           
            header->pack_start(*manage(new Image("analogue.png")));
            header->set_border_width(5);
            mainBox.pack_start(*align(header));

            Table* block1 = manage(new Table(2,4));
            block1->attach(*createOSC1(),    0, 1, 1, 2);
            block1->attach(*createFilter1(), 1, 2, 1, 2); 
            block1->attach(*createAmp1(),    2, 3, 1, 2);
            block1->attach(*createLFO1(),    3, 4, 1, 2);
            
            block1->attach(*createLFO2(),    0, 1, 2, 3);
            block1->attach(*createOSC2(),    1, 2, 2, 3);
            block1->attach(*createFilter2(), 2, 3, 2, 3);
            block1->attach(*createAmp2(),    3, 4, 2, 3);
            mainBox.pack_start(*align(block1));    

/*
            Table* block1 = manage(new Table(2,3));
            block1->attach(*createOSC1(),    0, 1, 1, 2);
            block1->attach(*createFilter1(), 1, 2, 1, 2); 
            block1->attach(*createAmp1(),    2, 3, 1, 2);
            block1->attach(*createOSC2(),    0, 1, 2, 3);
            block1->attach(*createFilter2(), 1, 2, 2, 3);
            block1->attach(*createAmp2(),    2, 3, 2, 3);
            mainBox.pack_start(*align(block1));            

            HBox* block2 = manage(new HBox());
            block2->pack_start(*createNoise());
            block2->pack_start(*createLFO1());
            block2->pack_start(*createLFO2());
            mainBox.pack_start(*align(block2));
*/
            HBox* block3 = manage(new HBox());
            block3->pack_start(*createFilter1Env());
            block3->pack_start(*createFilter2Env());
            block3->pack_start(*createAmp1Env());
            block3->pack_start(*createAmp2Env());
            mainBox.pack_start(*block3);

            // TODO : HBox for Chorus, Delay and Reverb

            mainBox.pack_end(statusbar);

            add(*align(&mainBox));
        }

        Widget* createOSC1() {
            Table* table = manage(new Table(4,5));
            // row 1 
            control(table, "Type", p_osc1_type, 0, 1);
            control(table, "Tune", p_osc1_tune, 1, 1);
            control(table, "PW", p_osc1_width, 2, 1);
            control(table, "Kbd", p_osc1_kbd, 3, 1);
            //addControl(table, "Sync", p_osc1_type, 0, 1);
            // row 2
            control(table, "Level", p_osc1_level, 0, 3);
            control(table, "Finetune", p_osc1_finetune, 1, 3);
            control(table, "LFO1", p_osc1_lfo_to_w, 2, 3);
            control(table, "LFO1", p_osc1_lfo_to_p, 3, 3);
            control(table, "F1 F2", p_osc1_f1_to_f2, 4, 3);
            return frame("OSC1", table); 
        }

        Widget* createOSC2() {
            Table* table = manage(new Table(6,4));
            // row 1 
            control(table, "Type", p_osc2_type, 0, 1);
            control(table, "Tune", p_osc2_tune, 1, 1);
            control(table, "PW", p_osc2_width, 2, 1);
            control(table, "Kbd", p_osc2_kbd, 3, 1);
            //addControl(table, "Sync", p_osc1_type, 0, 1);
            // row 2
            control(table, "Level", p_osc2_level, 0, 3);
            control(table, "Finetune", p_osc2_finetune, 1, 3);
            control(table, "LFO2", p_osc2_lfo_to_w, 2, 3);
            control(table, "LFO2", p_osc2_lfo_to_p, 3, 3);
            control(table, "F1 F2", p_osc2_f1_to_f2, 4, 3);
            return frame("OSC2", table); 
        }

        Widget* createNoise() {
            Table* table = manage(new Table(2, 3));
            control(table, "Color", p_noise_color, 0, 1);
            control(table, "F1 F2", p_noise_f1_to_f2, 1, 1);
            control(table, "Level", p_noise_level, 2, 1);
            return frame("Noise", table);
        }

        Widget* createLFO1() {
            Table* table = manage(new Table(2, 5));
            control(table, "Type", p_lfo1_type, 0, 1);
            control(table, "Freq", p_lfo1_freq, 1, 1);
            control(table, "Delay", p_lfo1_delay, 2, 1);
            control(table, "Fade In", p_lfo1_fade_in, 3, 1);
            control(table, "Width", p_lfo1_width, 4, 1);
            return frame("LFO1", table);
        }

        Widget* createLFO2() {
            Table* table = manage(new Table(2, 5));
            control(table, "Type", p_lfo2_type, 0, 1);
            control(table, "Freq", p_lfo2_freq, 1, 1);
            control(table, "Delay", p_lfo2_delay, 2, 1);
            control(table, "Fade In", p_lfo2_fade_in, 3, 1);
            control(table, "Width", p_lfo2_width, 4, 1);
            return frame("LFO2", table);
        }

        Widget* createFilter1() {         
            Table* table = manage(new Table(4,5));
            // row 1 
            control(table, "Type", p_filter1_type, 0, 1);
            control(table, "Kbd", p_filter1_kbd, 1, 1);
            control(table, "Cutoff", p_filter1_cutoff, 2, 1);            
            control(table, "Q", p_filter1_q, 3, 1);
            control(table, "To F2", p_filter1_to_f2, 4, 1);
            // row 2
            // TODO : order
            control(table, "LFO1", p_filter1_lfo_to_f, 1, 3);
            control(table, "Env1", p_filter1_env_to_f, 2, 3);
            control(table, "LFO1", p_filter1_lfo_to_q, 3, 3);
            control(table, "Env1", p_filter1_env_to_q, 4, 3);
            return frame("Filter 1", table);
        }

        Widget* createFilter2() {
            Table* table = manage(new Table(4,5));
            // row 1 
            control(table, "Type", p_filter2_type, 0, 1);
            control(table, "Kbd", p_filter2_kbd, 1, 1);
            control(table, "Cutoff", p_filter2_cutoff, 2, 1);
            control(table, "Q", p_filter2_q, 3, 1);
            // row 2
            // TODO : order    
            control(table, "LFO2", p_filter2_lfo_to_f, 1, 3);
            control(table, "Env2", p_filter2_env_to_f, 2, 3);
            control(table, "LFO2", p_filter2_lfo_to_q, 3, 3);
            control(table, "Env2", p_filter2_env_to_q, 4, 3);
            return frame("Filter 2", table);
        }

        Widget* createAmp1() {
            Table* table = manage(new Table(4,4));
            // row 1
            control(table, "Kbd", p_amp1_kbd_to_level, 0, 1);
            control(table, "Level", p_amp1_level, 1, 1);
            control(table, "Kbd", p_amp1_kbd_to_pan, 2, 1);
            control(table, "Pan", p_amp1_pan, 3, 1);    
            // row 2  
            control(table, "LFO", p_amp1_lfo_to_level, 0, 3);
            // empty
            control(table, "LFO", p_amp1_lfo_to_pan, 2, 3);
            control(table, "Env", p_amp1_env_to_pan, 3, 3); 
            return frame("Amp 1", table);
        }

        Widget* createAmp2() {
            Table* table = manage(new Table(4,4));
            // row 1
            control(table, "Kbd", p_amp2_kbd_to_level, 0, 1);
            control(table, "Level", p_amp2_level, 1, 1);
            control(table, "Kbd", p_amp2_kbd_to_pan, 2, 1);
            control(table, "Pan", p_amp2_pan, 3, 1);    
            // row 2  
            control(table, "LFO", p_amp2_lfo_to_level, 0, 3);
            // empty
            control(table, "LFO", p_amp2_lfo_to_pan, 2, 3);
            control(table, "Env", p_amp2_env_to_pan, 3, 3); 
            return frame("Amp 2", table);
        }

        Widget* createFilter1Env() {
            Table* table = manage(new Table(2,4));
            control(table, "A", p_filter1_attack, 0, 1);
            control(table, "D", p_filter1_decay, 1, 1);
            control(table, "S", p_filter1_sustain, 2, 1);
            control(table, "R", p_filter1_release, 3, 1);
            return smallFrame("Filter1 Env", table);
        }

        Widget* createFilter2Env() {
            Table* table = manage(new Table(2,4));
            control(table, "A", p_filter2_attack, 0, 1);
            control(table, "D", p_filter2_decay, 1, 1);
            control(table, "S", p_filter2_sustain, 2, 1);
            control(table, "R", p_filter2_release, 3, 1);
            return smallFrame("Filter2 Env", table);
        }

        Widget* createAmp1Env() {
            Table* table = manage(new Table(2,4));
            control(table, "A", p_amp1_attack, 0, 1);
            control(table, "D", p_amp1_decay, 1, 1);
            control(table, "S", p_amp1_sustain, 2, 1);
            control(table, "R", p_amp1_release, 3, 1);
            return smallFrame("Amp1 Env", table);
        }

        Widget* createAmp2Env() {
            Table* table = manage(new Table(2,4));
            control(table, "A", p_amp2_attack, 0, 1);
            control(table, "D", p_amp2_decay, 1, 1);
            control(table, "S", p_amp2_sustain, 2, 1);
            control(table, "R", p_amp2_release, 3, 1);
            return smallFrame("Amp2 Env", table);
        }

        void control(Table* table, const char* label, int port_index, int left, int top) {
            table->attach(*scales[port_index - 3], left, left + 1, top, top + 1);
            table->attach(*manage(new Label(label)), left, left + 1, top + 1, top + 2);
        }

        Widget* smallFrame(const char* label, Table* content) {
            content->set_border_width(5);
            content->set_col_spacings(2);
            content->set_spacings(2);

            Frame* frame = manage(new Frame());
            frame->set_label_align(0.0f, 0.0f);
            frame->set_border_width(5);
            frame->set_label(label);
            frame->add(*content);
            
            Alignment* alignment = manage(new Alignment(0.0, 0.0, 1.0, 0.0));
            alignment->add(*frame);
            return alignment;
        }

        Widget* frame(const char* label, Table* content) {
            content->set_border_width(10);
            content->set_col_spacings(5);
            content->set_spacings(5);

            Frame* frame = manage(new Frame());
            frame->set_label_align(0.0f, 0.0f);
            frame->set_border_width(5);
            frame->set_label(label);
            frame->add(*content);
            frame->set_shadow_type(SHADOW_OUT);
            
            Alignment* alignment = manage(new Alignment(0.0, 0.0, 1.0, 0.0));
            alignment->add(*frame);
            return alignment;
        }

        Alignment* align(Widget* widget) {
            Alignment* alignment = manage(new Alignment(0.0, 0.0, 0.0, 0.0));
            alignment->add(*widget);
            return alignment;
        }

        bool isEnvControl(int i) {
             const char* symbol = p_port_meta[i].symbol;
            return strstr(symbol, "_attack") || strstr(symbol, "_decay") || strstr(symbol, "_sustain") || strstr(symbol, "_release");
        }

        bool isModControl(int i) {
            const char* symbol = p_port_meta[i].symbol;
            return strstr(symbol, "_kbd_") || strstr(symbol, "_lfo_") || strstr(symbol, "_env_");
        } 

        void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer) {
            if (port > 2) { 
                scales[port-3]->set_value(*static_cast<const float*>(buffer));
            }
        }

        void change_status_bar(uint32_t port, float value) {

        }

    protected:
        VBox mainBox;
        Statusbar statusbar;
        
        Knob *scales[p_n_ports - 3];
};

static int _ = AnalogueGUI::register_class("http://www.westkamper.com/lv2/analogue/gui");

