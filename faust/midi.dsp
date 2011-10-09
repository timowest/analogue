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

// MIDI

mono_pitch = hslider("/h:midi/pitch", 64, 32, 100, 1);

mono_gain = hslider("/h:midi/gain", 1, 0, 1, 0.01); 

mono_gate = button("/h:midi/gate");


