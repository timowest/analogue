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

import("env.dsp");
import("midi.dsp");
import("utils.dsp");

// amplifiers

amp1(lfo) = vgroup("amp1", ((gate : amp1_env), _) <: (_,!,level * _ * _)  : amp1_stereo(lfo))
with {
  level = main_level + kbd_to_level * (pitch - A4) + lfo_to_level * lfo : normalize(0,1);
  kbd_to_level = hslider("amp1_kbd_to_level", 0, -0.1, 0.1, 0.01) * 0.1; 
  lfo_to_level = hslider("amp1_lfo_to_level", 0, -0.5, 0.5, 0.01);
  main_level = hslider("amp1_level", 1, 0, 1, 0.01); 
};

amp1_stereo(lfo, env) = to_stereo(0.5 * (pan+1))
with {
  pan = main_pan + kbd_to_pan * (pitch - A4) + lfo_to_pan * lfo + env_to_pan * env : normalize(-1,1);
  main_pan = hslider("amp1_pan", 0, -1, 1, 0.01);
  kbd_to_pan = hslider("amp1_kbd_to_pan", 0, -0.1, 0.1, 0.01) * 0.1; 
  lfo_to_pan = hslider("amp1_lfo_to_pan", 0, -0.5, 0.5, 0.01);
  env_to_pan = hslider("amp1_env_to_pan", 0, -0.5, 0.5, 0.01);
};

amp2(lfo) = vgroup("amp2", ((gate : amp2_env), _) <: (_,!,level * _ * _)  : amp1_stereo(lfo))
with {
  level = main_level + kbd_to_level * (pitch - A4) + lfo_to_level * lfo : normalize(0,1);
  kbd_to_level = hslider("amp2_kbd_to_level", 0, -0.1, 0.1, 0.01) * 0.1; 
  lfo_to_level = hslider("amp2_lfo_to_level", 0, -0.5, 0.5, 0.01);
  main_level = hslider("amp2_level", 1, 0, 1, 0.01); 
};

amp2_stereo(lfo, env) = to_stereo(0.5 * (pan+1))
with {
  pan = main_pan + kbd_to_pan * (pitch - A4) + lfo_to_pan * lfo + env_to_pan * env : normalize(-1,1);
  main_pan = hslider("amp2_pan", 0, -1, 1, 0.01);
  kbd_to_pan = hslider("amp2_kbd_to_pan", 0, -0.1, 0.1, 0.01) * 0.1; 
  lfo_to_pan = hslider("amp2_lfo_to_pan", 0, -0.5, 0.5, 0.01);
  env_to_pan = hslider("amp2_env_to_pan", 0, -0.5, 0.5, 0.01);
};

to_stereo(pan) = _ <: (1-pan) * _, pan * _;

//process = 1 : amp1(1);

