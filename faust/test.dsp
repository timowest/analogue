//import("effect.lib");
import("filter.lib");
import("utils.dsp");
import("math.lib");

// FILTERS

// reference
moog_vcf(res,fr) = (+ : seq(i,4,pole(p)) : *(unitygain(p))) ~ *(mk)
with {
     p = 1.0 - fr * 2.0 * PI / SR; // good approximation for fr << SR
     unitygain(p) = pow(1.0-p,4.0); // one-pole unity-gain scaling
     mk = -4.0 * max(0,min(res,0.999999)); // need mk > -4 for stability
};

// by Victor Lazzarini
moogladder(f,res) = filter(f,res) : aver
with {
    v2 = 40000;
    fcor(f) = 1.8730*(f^3) + 0.4955*(f^2) - 0.6490*f + 0.9988;
    acor(f) = -3.9364*(f^2) + 1.8409*f + 0.9968;
    vg2(f) = v2*(1 - exp(-2*PI*fcor(f/(SR/2))*f/(SR)));
    sec(f) =  (/(v2) : tanh : *(vg2(f))) : + ~ (_ <: _, (/(v2) : tanh : *(vg2(f)) : *(-1)): + ); 
    filter(f,res) = (+ : sec(f) : sec(f) : sec(f) : sec(f)) ~ (*(4*res*acor(f/(SR/2))) :*(-1));
    aver(x) =  0.5*(x + x');
};

// Moog Ladder Filter
//
// Reference : New Approaches to Digital Subtractive Synthesis
// Antti Huovilainen and Vesa Välimäki
reson_filter(type, freq, res, dist_amount, drive) = filter : mix
with {
  
  filter(x) = (x+_ <: (lp,_) <: (lp,!,_,_) <: (lp,!,!,_,_,_) <: (lp,!,!,!,_,_,_,_)) ~ (distort : ((_-comp*x)*mk));
  comp = 0.5;
  lp = (_*1.3) : zero(-0.3) : (_*g) : pole(1-g);
  g = 1.0 - exp(-2.0 * PI * freq / SR);  
  mk = -4.0 * max(0, min(res,0.999999)); // need mk > -4 for stability
  
  distort = _ <: mix2(dist_amount, _, tanh(drive * _));

  mix(db0, db6, db12, db18, db24) = select8(type, db24, db18, db12, db6,         
    db0 - db24,  // hp
    db24 - db12, // bp12
    db18 - db24, // bp18/6 
    (db18 - db24) + 2/3*db0); // notch

};

// Moog Ladder Filter
// Digital Sound Generation - Beat Frei

process = reson_filter(0, 440, 1, 0, 0, 0.5);



