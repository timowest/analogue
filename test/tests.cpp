#include <sndfile.hh>
#include <cstdlib>

#include "saw.cpp"
#include "saw2.cpp"
#include "sin.cpp"
#include "sin2.cpp"
#include "square.cpp"
#include "square2.cpp"
#include "tri.cpp"
#include "tri2.cpp"

#define SR   44100
#define SIZE 22050

void process(dsp* processor, const char* filename) {
    static int format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    static int channels = 1;
    static int sampleRate = SR;

    float buffer[SIZE];    
    float *outputs[] = {buffer};

    processor->init(SR);
    processor->compute(SIZE, 0, outputs);
  
    SndfileHandle outfile(filename, SFM_WRITE, format, channels, sampleRate);
    outfile.write(&buffer[0], SIZE);
    delete processor;
}

int main() {
    process(new sawdsp(),     "gen/saw.wav");
    process(new saw2dsp(),    "gen/saw2.wav");
    process(new sindsp(),     "gen/sin.wav");
    process(new sin2dsp(),    "gen/sin2.wav");
    process(new squaredsp(),  "gen/square.wav");
    process(new square2dsp(), "gen/square2.wav");
    process(new tridsp(),     "gen/tri.wav");
    process(new tri2dsp(),    "gen/tri2.wav");
}

