#include "analogue.h"    

#include <vector>

#include <sndfile.hh>
#include <iostream>
#include <cmath>
#include <stdio.h>

int main() {
    int bufferSize = 88200;
    float buffer_l[bufferSize];    
    float buffer_r[bufferSize];    

    float controls[p_n_ports-3];
    for (int i = 0; i < p_n_ports-3; i++)  {
        controls[i] = p_port_meta[i].default_value;
    }

    // init Analogue
    Analogue analogue(44100.0f);
    // connect audio ports
    analogue.connect_port(p_audio_l, &buffer_l[0]);
    analogue.connect_port(p_audio_r, &buffer_r[0]);
    // connect control ports
    for (int i = 3; i < p_n_ports; i++) {
        //std::cout << "connect " << i << std::endl;    
        analogue.connect_port(i, &controls[i-3]);
    }

    // override defaults
    //controls[p_jetFilterFreq - 3] = 4000.0f;
    //controls[p_boreFilterFreq - 3] = 4000.0f;
    //controls[p_noiseFreqCutoff - 3] = 1500.0;
    //controls[p_jetReflection - 3] = 0.6;
    //controls[p_endReflection - 3] = 0.4;

    //int format=SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    int format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    int channels = 1;
    int sampleRate = 44100;

    const char* names[] = {"c","c#","d","d#","e","f","f#","g","g#","a","a#","b"};
   
    for (int i = 0; i < 12; i++) {
        // render output
        analogue.on(64 + i, 64);
        analogue.render(0, 44100);
        analogue.off(64 + i, 0);
        analogue.render(44100, bufferSize);

        // write to WAV
        char filename[10];
        sprintf(filename, "gen/%s4.wav", names[i]);

        SndfileHandle outfile(filename, SFM_WRITE, format, channels, sampleRate);
        if (!outfile) {
            return -1;
        }
        outfile.write(&buffer_l[0], bufferSize);
    }

    return 0;
}
