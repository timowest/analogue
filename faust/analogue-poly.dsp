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

analogue = library("analogue.dsp");
import("effects.dsp");

// Polyphonic Analogue Synth

// TODO : render only active voices
voice(i) = analogue.voice(gate(i), gain(i), pitch(i))
with {
  gate(i) = button("/h:midi/gate%i");
  gain(i) = nentry("/h:midi/gain%i", 0, 0, 1, 0.01);
  pitch(i) = hslider("/h:midi/pitch%i", 64, 32, 100, 1);
};

main_out = nentry("/h:amp/output", 1, 0, 1, 0.01); // TODO in dB

// TODO : effects
process = par(i, 8, voice(i)) :> (_,_,_,_) : effects :> (main_out * _, main_out * _);



