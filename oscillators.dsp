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

import("midi.dsp");
import("utils.dsp");

// oscillators

lfo1 = vgroup("lfo1", oscillator(type, freq, width) 
  : fade_in(fade_in_samples, gate)
  : delay(SR, delay_in_samples))
with {
  type = hslider("lfo1_type", 0, 0, 2, 1);
  freq = hslider("lfo1_freq", 0, 1, 50, 1);
  width = hslider("lfo1_width", 0.5, 0.0, 1.0, 0.01);
  fade_in_samples = hslider("lfo1_fade_in", 0, 0, 5, 0.01) * SR;
  delay_in_samples = hslider("lfo1_delay", 0, 0, 1, 0.01) * SR;
};

lfo2 = vgroup("lfo2", oscillator(type, freq, width) 
  : fade_in(fade_in_samples, gate)
  : delay(SR, delay_in_samples))
with {
  type = hslider("lfo2_type", 0, 0, 2, 1);
  freq = hslider("lfo2_freq", 0, 1, 50, 1);
  width = hslider("lfo2_width", 0.5, 0.0, 1.0, 0.01);
  fade_in_samples = hslider("lfo2_fade_in", 0, 0, 5, 0.01) * SR;
  delay_in_samples = hslider("lfo2_delay", 0, 0, 1, 0.01) * SR;
};

osc1(lfo) = vgroup("osc1", 
  oscillator(
    type, 
    key2hz(440.0, kbd_track * (pitch - A4) + tune + finetune + lfo_to_p * lfo), 
    width + lfo_to_w * lfo : normalize(0,1)) * level
  : split(f1_to_f2))
with {
  type = hslider("osc1_type", 0, 0, 2, 1);
  kbd_track = hslider("osc1_kbd", 1, -12, 12, 0.1);
  tune = hslider("osc1_tune", 0, -24, 24, 1);
  finetune = hslider("osc1_finetune", 0, -1, 1, 0.01);
  lfo_to_p = hslider("osc1_lfo_to_p", 0, -12, 12, 0.1);
  width = hslider("osc1_width", 0.5, 0.0, 1.0, 0.01);
  lfo_to_w = hslider("osc1_lfo_to_w", 0, -0.5, 0.5, 0.01);
  level = hslider("osc1_level", 0.5, 0, 1, 0.01);
  f1_to_f2 = hslider("osc1_f1_to_f2", 0, 0, 1, 0.01);
};

osc2(lfo) = vgroup("osc2", 
  oscillator(
    type, 
    key2hz(440.0, kbd_track * (pitch - A4) + tune + finetune + lfo_to_p * lfo), 
    width + lfo_to_w * lfo : normalize(0,1)) * level
  : split(f1_to_f2))
with {
  type = hslider("osc2_type", 0, 0, 2, 1);
  kbd_track = hslider("osc1_kbd", 1, -12, 12, 0.1);
  tune = hslider("osc2_tune", 0, -24, 24, 1);
  finetune = hslider("osc2_finetune", 0, -1, 1, 0.01);
  lfo_to_p = hslider("osc2_lfo_to_p", 0, -12, 12, 0.1);
  width = hslider("osc2_width", 0.5, 0.0, 1.0, 0.01);
  lfo_to_w = hslider("osc2_lfo_to_w", 0, -0.5, 0.5, 0.01);
  level = hslider("osc2_level", 0.5, 0, 1, 0.01);
  f1_to_f2 = hslider("osc2_f1_to_f2", 0, 0, 1, 0.01);
};

// noise

noisegen = vgroup("noise", noise 
    : lowpass(1, noise_color) * noise_level 
    : split(f1_to_f2))
with {
  noise_color = hslider("noise_color", 2000, 200, 5000, 50);
  noise_level = hslider("noise_level", 0, 0, 1, 0.01);
  f1_to_f2 = hslider("noise_f1_to_f2", 0, 0, 1, 0.01);
};

// helpers

// TODO : more wavetypes
// TODO : add sawtooth width
oscillator(type, freq, width) = select3(type,
  oscws(freq), // sine
  sawtooth(freq), // sawtooth 
  squarewave(freq, width))
with {

  squarewave(freq, width) = 2 * pulsetrainpos(freq, width) - 1;

};

//process = osc1(0) : (gate * gain*_, gate * gain*_);

