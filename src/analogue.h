#ifndef ANALOGUE_H
#define ANALOGUE_H
//See associated .cpp file for copyright and other info

#include <lv2plugin.hpp>
#include <lv2_event_helpers.h>

#include "analogue-common.h"
#include "analogue.peg"
#include "analogue-meta.h"

#include "dsp.h"
#include "collector-ui.h"

class Analogue : public LV2::Plugin<Analogue, LV2::URIMap<true> > {
    private:
        typedef LV2::Plugin<Analogue, LV2::URIMap<true> > Parent;

        float rate;
        float *outputs[2];

        float* pitch[NVOICES];
        float* gain[NVOICES];
        float* gate[NVOICES];
        //float* pitchBend;
        //float* breathControl;

        float *zones[p_n_ports-3];
        
        dsp *synth;
        CollectorUI* synthUI;

    protected:

        uint32_t m_midi_input;
        uint32_t m_midi_type;
   
        template <typename T> T*& p(uint32_t port) {
            return reinterpret_cast<T*&>(Parent::m_ports[port]);
        }
  
        float*& p(uint32_t port) {
            return reinterpret_cast<float*&>(Parent::m_ports[port]);
        }


    public:
        Analogue(double rate);
        ~Analogue();

        void handle_midi(uint32_t size, unsigned char* data);
        void setPitchBend(float value);
        void setBreathControl(float value);
        void setVolumeControl(float value);
        void run(uint32_t sample_count);
                
        void on(unsigned char key, unsigned char velo);
        void off(unsigned char key, unsigned char velo);
        void render(uint32_t from, uint32_t to);
};
#endif
