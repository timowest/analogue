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

import("midi.dsp");
filters = library("filters.dsp");
oscillators = library("oscillators.dsp");
amps = library("amps.dsp");
import("utils.dsp");

// Simplified version for testing

// process

// LFO > OSC > FILTER > AMP
process = hgroup("simple", lfo1 <: (_,osc1) : (_,_+_) <: (_,!,filter1) : (_,_,!) : amp1)
with {
  lfo1 = oscillators.lfo1(mono_gate);
  osc1 = oscillators.osc1(mono_pitch);
  filter1 = filters.filter1(mono_gate, mono_pitch);
  amp1 = amps.amp1(mono_gate, mono_gain, mono_pitch);
};

