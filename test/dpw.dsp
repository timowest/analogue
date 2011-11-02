import("math.lib");

dpw_oscillator(type, freq, width) = phase(freq) <: select2(type > 0, sin(2*PI*_), dpw)
with {

    dpw = bi : shape <: -(mem) : scale : (SR/freq'*_);
                             
    // type                    tri          saw   square
    shape(x) = select3(type-1, x-x*abs(x),  x*x,  0); 
    scale    = select3(type-1, 0.5,         0.25, 1)*_;

};

phase(freq) = (+(q) : mod1) ~ _
with {
    q = float(freq)/float(SR);
};

// unipolar to bipolar
bi = 2.0*_ - 1.0;

mod1 = fmod(_, 1.0); 
