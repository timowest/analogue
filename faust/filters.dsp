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
    key2hz(cutoff, kbd_track * (pitch - A4) + (lfo_to_f * lfo) + (env_to_f * env)),
    q + (lfo_to_q * lfo) + (env_to_q * env)))
with {
  type = hslider("type", 0, 0, 3, 1);
  cutoff = hslider("cutoff", 440, 0, 5000, 10);
  kbd_track = hslider("kbd", 1, -12, 12, 0.1);
  lfo_to_f = hslider("lfo_to_f",0,-12,12,0.1);
  env_to_f = hslider("env_to_f",0,-12,12,0.1);
  q = hslider("q",0.5,0,10,0.01);
  lfo_to_q = hslider("lfo_to_q",0,-1,1,0.1);
  env_to_q = hslider("env_to_q",0,-1,1,0.1);
};

// helpers

reson_filter(type, freq, res) = _ <: select4(type,
  resonlp(freq, res, 1.0), // lowpass
  resonhp(freq, res, 1.0), // highpass
  resonbp(freq, res, 1.0), // bandpass
  resonbr(freq, res, 1.0)) // bandreject
with {

  resonbr(fc,Q,gain,x) = (gain * x) - resonbp(fc,Q,gain,x);

};

