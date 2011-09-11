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


// Polyphonic Analogue Synth

// replace mono controls with voice controls
voice(i) = component("analogue.dsp")[gain=poly_gain(i); gate=poly_gate(i); pitch=poly_pitch(i);]
with {
    poly_pitch(i) = hslider("/v:midi/pitch%i", 64, 32, 100, 1);
    poly_gain(i) = nentry("/v:midi/gain%i", 1, 0, 1, 0.01); 
    poly_gate(i) = button("/v:midi/gate%i");
};

// TODO : effects
process = par(i, 16, voice(i)) :> (_,_);



