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

import("oscillator.lib");
import("music.lib");

import("midi.dsp");
import("utils.dsp");

// oscillators

// in : gate
lfo1 = vgroup("lfo1", select2(checkbox("power"), 0, lfo));

// in : gate
lfo2 = vgroup("lfo2", select2(checkbox("power"), 0, lfo));

lfo(gate) = oscillator(type, freq, width) : fade_in(fade_in_samples, gate) : delay(SR, delay_in_samples)
with {
  type = hslider("type", 0, 0, 4, 1);
  freq = hslider("freq", 1, 1, 50, 1);
  width = hslider("width", 0.5, 0.0, 1.0, 0.01);
  fade_in_samples = hslider("fade_in", 0, 0, 5, 0.01) * SR;
  delay_in_samples = hslider("delay", 0, 0, 1, 0.01) * SR;
};


// in : pitch, lfo
osc1 = vgroup("osc1", multiselect(2, checkbox("power"), 0, 0, osc_));

// in : pitch, lfo
osc2 = vgroup("osc2", multiselect(2, checkbox("power"), 0, 0, osc_));

osc_(pitch, lfo) = oscillator(
    type, 
    key2hz(440.0, kbd_track * (pitch - A4) + tune + finetune + (lfo_to_p * lfo)), 
    width + lfo_to_w * lfo : normalize(0,1)) * level
  : split(f1_to_f2)
with {
  type = hslider("type", 0, 0, 4, 1);
  kbd_track = hslider("kbd", 1, -12, 12, 0.1);
  tune = hslider("tune", 0, -24, 24, 1);
  finetune = hslider("finetune", 0, -1, 1, 0.01);
  lfo_to_p = hslider("lfo_to_p", 0, -12, 12, 0.1);
  width = hslider("width", 0.5, 0.0, 1.0, 0.01);
  lfo_to_w = hslider("lfo_to_w", 0, -0.5, 0.5, 0.01);
  level = hslider("level", 0.5, 0, 1, 0.01);
  f1_to_f2 = hslider("f1_to_f2", 0, 0, 1, 0.01);
};

// noise

noisegen = vgroup("noise", multiselect(2, checkbox("power"), 0, 0, noise 
    : lowpass(1, noise_color) * noise_level 
    : split(f1_to_f2)))
with {
  noise_color = hslider("color", 2000, 200, 5000, 50);
  noise_level = hslider("level", 0, 0, 1, 0.01);
  f1_to_f2 = hslider("f1_to_f2", 0, 0, 1, 0.01);
};

// helpers

oscillator(type, freq, width) = select5(type,
  osc(freq),
  triangle(freq),
  sawtooth(freq), 
  squarewave(freq, width),
  random)
with {

  squarewave(freq, width) = 2 * pulsetrainpos(freq, width) - 1;

  triangle(freq) = saw1(freq) : abs : (_*2-1);

  random = noise; // TODO : improve

};

//process = osc1(0) : (gate * gain*_, gate * gain*_);

