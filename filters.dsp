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

import("filter.lib");

import("midi.dsp");
import("env.dsp");
import("utils.dsp");

// filters

// in : lfo, signal
filter1 = (_, (gate : filter1_env),_) : _filter1;

// TODO : distortion
_filter1(lfo, env) = vgroup("filter1", 
  filter(
    type, 
    key2hz(cutoff, kbd_track * (pitch - A4) + lfo_to_f * lfo +  env_to_f * env), 
    q + lfo_to_q * lfo + env_to_q * env) 
  <: (_, to_f2 * _))
with {
  type = hslider("filter1_type", 0, 0, 3, 1);
  cutoff = hslider("filter1_cutoff", 440, 0, 5000, 10);
  kbd_track = hslider("filter1_kbd", 1, -12, 12, 0.1);
  lfo_to_f = hslider("filter1_lfo_to_f",0,-12,12,0.1);
  env_to_f = hslider("filter1_env_to_f",0,-12,12,0.1);
  q = hslider("filter1_q",0.5,0,1,0.01);
  lfo_to_q = hslider("filter1_lfo_to_q",0,-1,1,0.1);
  env_to_q = hslider("filter1_env_to_q",0,-1,1,0.1);
  to_f2 = hslider("filter1_to_f2",0,0,1,0.01);
};

// in : lfo, signal
filter2 = (_, (gate : filter2_env),_) : _filter2;

_filter2(lfo, env) = vgroup("filter2", 
  filter(
    type, 
    key2hz(cutoff, kbd_track * (pitch - A4) + lfo_to_f * lfo +  env_to_f * env), 
    q + lfo_to_q * lfo + env_to_q * env))
with {
  type = hslider("filter2_type", 0, 0, 3, 1);
  cutoff = hslider("filter2_cutoff", 440, 0, 5000, 10);
  kbd_track = hslider("filter2_kbd", 1, -12, 12, 0.1);
  lfo_to_f = hslider("filter2_lfo_to_f",0,-12,12,0.1);
  env_to_f = hslider("filter2_env_to_f",0,-12,12,0.1);
  q = hslider("filter2_q",0.5,0,1,0.01);
  lfo_to_q = hslider("filter2_lfo_to_q",0,-1,1,0.1);
  env_to_q = hslider("filter2_env_to_q",0,-1,1,0.1);
};

// helpers

filter(type, freq, res) = _ <: select4(type,
  resonlp(freq, res, 1.0), // lowpass
  resonhp(freq, res, 1.0), // highpass
  resonbp(freq, res, 1.0), // bandpass
  resonbr(freq, res, 1.0)) // bandreject
with {

  resonbr(fc,Q,gain,x) = gain*x-resonbp(fc,Q,gain,x);

};

//process = (1,1) : filter1;
