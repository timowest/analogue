/*
 *  Copyright (C) 2011 Timo Westkämper
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */
import("effect.lib");

import("filter.lib");

import("utils.dsp");
 
// filters

// in : lfo, signal
filter1(gate, pitch) = vgroup("filter1", (_,(gate : env),_) : filter(pitch) <: (_, to_f2 * _) )
with {
  to_f2 = hslider("to_f2",0,0,1,0.01);
};

// in : lfo, signal
filter2(gate, pitch) = vgroup("filter2", (_,(gate : env),_) : filter(pitch) );

filter(pitch, lfo, env) = bypass1(checkbox("bypass"), reson_filter(
    type, 
    key2hz(cutoff, kbd_track * (pitch - A4) + (lfo_to_f * lfo) +  (env_to_f * env)), 
    q + (lfo_to_q * lfo) + (env_to_q * env),
    dist_amount, dist_drive))
with {
  type = hslider("type", 0, 0, 7, 1);
  cutoff = hslider("cutoff", 440, 0, 5000, 10);
  kbd_track = hslider("kbd", 1, -12, 12, 0.1);
  lfo_to_f = hslider("lfo_to_f",0,-12,12,0.1);
  env_to_f = hslider("env_to_f",0,-12,12,0.1);
  q = hslider("q",0.5,0,10,0.01);
  lfo_to_q = hslider("lfo_to_q",0,-1,1,0.1);
  env_to_q = hslider("env_to_q",0,-1,1,0.1);

  dist_amount = hslider("dist_amount", 0.5, 0, 1, 0.01);
  dist_drive = hslider("dist_drive", 1, 0, 2, 0.01);
};

reson_filter(t,fr,res,da,dd) = (+ : seq(i,4,pole(p)) : *(unitygain(p))) ~ *(mk)
with {
     p = 1.0 - fr * 2.0 * PI / SR; // good approximation for fr << SR
     unitygain(p) = pow(1.0-p,4.0); // one-pole unity-gain scaling
     mk = -4.0 * max(0,min(res,0.999999)); // need mk > -4 for stability
};

// Moog Ladder Filter
//
// Reference : New Approaches to Digital Subtractive Synthesis
// Antti Huovilainen and Vesa Välimäki
reson_filter_(type, freq, res, dist_amount, drive) = filter : mix
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
    (db24 - db12) + 2/3*db0); // notch

};


