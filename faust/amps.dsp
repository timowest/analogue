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

import("utils.dsp");

// amplifiers

// in : gate, gain, pitch, lfo
amp1 = vgroup("amp1", multiselect(2, checkbox("power"), 0, 0, amp));

// in : gate, gain, pitch, lfo
amp2 = vgroup("amp2", multiselect(2, checkbox("power"), 0, 0, amp));

amp(gate, gain, pitch, lfo) = ((gate : env), _) <: (_,!,level*_*_) : amp_stereo(pitch, lfo)
with {
  level = main_level + (kbd_to_level * (pitch - A4)) + (lfo_to_level * lfo) : (_*gain) : normalize(0,1);
  kbd_to_level = hslider("kbd_to_level", 0, -0.1, 0.1, 0.01) * 0.1; 
  lfo_to_level = hslider("lfo_to_level", 0, -0.5, 0.5, 0.01);
  //gain_to_level = hslider("gain_to_level", 1, 0, 1, 0.01);
  main_level = hslider("level", 1, 0, 1, 0.01); 
};

amp_stereo(pitch, lfo, env) = to_stereo(0.5 * (pan+1))
with {
  pan = main_pan + (kbd_to_pan * (pitch - A4)) + (lfo_to_pan * lfo) + (env_to_pan * env) : normalize(-1,1);
  main_pan = hslider("pan", 0, -1, 1, 0.01);
  kbd_to_pan = hslider("kbd_to_pan", 0, -0.1, 0.1, 0.01) * 0.1; 
  lfo_to_pan = hslider("lfo_to_pan", 0, -0.5, 0.5, 0.01);
  env_to_pan = hslider("env_to_pan", 0, -0.5, 0.5, 0.01);
};

to_stereo(pan) = _ <: (1-pan)*_, pan*_;

