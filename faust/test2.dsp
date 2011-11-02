//
import("math.lib");
osclib = library("oscillator.lib");
import("utils.dsp");

process = mix2(mix, oscillator_old(type, freq, width), dpw_oscillator(type, freq, width)) : (gain*_) <: (_,_)
with {
  mix = hslider("mix", 0.5, 0, 1, 0.1);
  type = hslider("type", 0, 0, 4, 1);
  freq = hslider("freq", 440, 10, 10000, 10);
  width = hslider("width", 0.5, 0.0, 1.0, 0.1);
  gain = hslider("gain", 0.5, 0, 1, 0.1);
};

// OLD

oscillator_old(type, freq, width) = select5(type,
  osclib.osc(freq),
  triangle(freq),
  osclib.saw1(freq), 
  squarewave(freq, width),
  random)
with {

  squarewave(freq, width) = 2.0 * osclib.pulsetrainpos(freq, width) - 1.0;

  triangle(freq) = osclib.saw1(freq) : abs : (_*2.0-1.0);

  random = osclib.noise; // TODO : improve

};

// DPW

// saw2(freq) = saw1(freq) <: * <: -(mem) : *(0.25'*SR/freq);

dpw_oscillator(type, freq, width) = phase(freq) <: select2(type > 0, sin(2*PI*_), dpw)
with {

    dpw = bi : shape <: -(mem) : scale : (SR/freq'*_);
                             
    // type                    tri          saw   square
    shape(x) = select3(type-1, x-x*abs(x),  x*x,  0); 
    scale    = select3(type-1, 0.5,         0.25, 1)*_;

};

// PHASE SHAPING OSCILLATORS

oscillator(type, freq, width) = phase(freq) : phase_to_osc(type, width);

oscillator_slave(type, freq, width, a1) = phase(freq) : (a1*_) : mod1 : phase_to_osc(type, width);

phase(freq) = (+(q) : mod1) ~ _
with {
    q = float(freq)/float(SR);
};

// oscillators should be stateless : no recursion, no delays 
phase_to_osc(type, width) = _ <: select5(type,
   sin(2*PI*_), // TODO : optimize
   tri,
   saw,
   square(width),
   osclib.noise);
    
// square (pwm)
square(w) = select2(_ < w, -1.0, 1.0);

saw = bi;

tri = bi : fabs : bi;

// PHASE SHAPERS

// triangle

gtri(a0, a1) = bi : fabs : glin(a0, a1) : mod1;

gpulse(freq, w, x) = x - mod1(x + SR/freq) + w;

// TODO
//gvtri(w, a0, a1) = svtri(m) : glin(a0, a1) : mod1;

gripple(m) = _ <: (_  + fmod(_,m));

mod1 = fmod(_, 1.0);

glin(a0, a1) = a1*_ + a0;

// unipolar to bipolar
bi = 2.0*_ - 1.0; 

// bipolar to unipolar
uni = 0.5*_ + 0.5; 
