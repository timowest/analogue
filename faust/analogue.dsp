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

import("music.lib");

import("midi.dsp");
filters = library("filters.dsp");
oscillators = library("oscillators.dsp");
amps = library("amps.dsp");

import("effects.dsp");
import("utils.dsp");

// Analogue Synth

voice(gate, gain, pitch) = (lfo1, lfo2) <: (_,_,osc1,osc2,noisegen)
    : (_,_,pre_filter_mix) // l1, l2, f1_in, f2_in
    // to filters 
    <: ((_,_,!,_), ((_,!,_,!) : filter1)) // l1, l2, f2_in, filter1, filter1_to_f2
    <: ((_,!,!,_,!), (!,_,!,!,!), ((!,_,_,!,_) : (_,_+_) : filter2)) // l1, f1_out, l2, f2_out
    // to amps
    : (amp1, amp2)
with {
  lfo1 = oscillators.lfo1(gate);
  lfo2 = oscillators.lfo2(gate);
  osc1 = oscillators.osc1(pitch);
  osc2 = oscillators.osc2(pitch);
  noisegen = oscillators.noisegen;
  filter1 = filters.filter1(gate, pitch);
  filter2 = filters.filter2(gate, pitch);
  amp1 = amps.amp1(gate, gain, pitch);
  amp2 = amps.amp2(gate, gain, pitch);

  // in : o11, o12, o21, o22, n1, n2
  // out : f1_in, f2_in
  pre_filter_mix = bus6 <: (((_,!,_,!,_,!) : _+_+_), ((!,_,!,_,!,_) : _+_+_));

};

main_out = nentry("/h:amp/output", 1, 0, 1, 0.01); // TODO in dB

process = voice(mono_gate, mono_gain, mono_pitch) : effects :> (main_out * _, main_out * _);

