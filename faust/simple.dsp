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
import("filters.dsp");
import("oscillators.dsp");
import("amps.dsp");

import("utils.dsp");

// Simplified version for testing

// process

// LFO > OSC > FILTER > AMP
process = hgroup("simple", lfo1 <: (_,osc1) : (_,_+_) <: (_,!,filter1) : (_,_,!) : amp1);



