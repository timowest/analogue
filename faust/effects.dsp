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

import("effect.lib");
import("oscillator.lib");
import("freeverb.dsp");

import("utils.dsp");

// chorus & flanger
// TODO : implement mix properly

flanger_effect = vgroup("flanger", bypass2(bp, flanger_stereo(dmax,curdel1,curdel2,depth,fb,invert)))
with {
   // parameters
   bp     = checkbox("bypass");
   invert = checkbox("invert");
   freq   = hslider("speed", 0.5, 0, 10, 0.01); // Hz
   depth  = hslider("depth", 1, 0, 1, 0.001);
   fb     = hslider("feedback", 0, -0.999, 0.999, 0.001);
   level  = hslider("output_level", 0, -60, 10, 0.1) : db2linear; // dB
   mix    = hslider("mix", 0.5, 0, 1, 0.01);

   dmax = 2048;
   dflange = 0.001 * SR * hslider("flange_delay", 10, 0, 20, 0.001); // ms
   odflange = 0.001 * SR * hslider("delay_offset", 1, 0, 20, 0.001); // ms
   curdel1 = odflange + dflange*(1 + oscrs(freq))/2; // sine for left 
   curdel2 = odflange + dflange*(1 + oscrc(freq))/2; // cosine for right
};

// delay (2 delay lines)
// Sync
// Mix (0-1) 
// Depth
// Rate (50ms - 3s) 

//delay TODO

delay_effect = vgroup("delay", bus2);

// reverb
// TODO : implement mix properly

// freeverb based
reverb_effect = vgroup("reverb", bypass2(bp, fxctrl(fixedgain, wetSlider, stereoReverb(combfeed, allpassfeed, dampSlider, stereospread))))
with {
   bp             = checkbox("bypass");

   dampSlider     = hslider("damp",0.720, 0, 1, 0.025)*scaledamp;
   roomsizeSlider = hslider("roomSize", 0.540, 0, 1, 0.025)*scaleroom + offsetroom;
   wetSlider      = hslider("wet", 0.141, 0, 1, 0.025);
   drySlider      = hslider("dry", 0, 0, 1, 0.025);
   combfeed       = roomsizeSlider;
};

// FIXME: doesn't work properly
// zita_rev1_stereo based effect
reverb_effect_zita = vgroup("reverb", bypass2(bp, zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax) : out_level))
with {
   // parameters
   bp    = checkbox("bypass");
   rdel  = hslider("predelay", 60,20,100,1); // delay (in ms) before reverberation begins (e.g., 0 to ~100 ms)
   f1    = hslider("crossover_freq", 200, 50, 1000, 1); // crossover frequency (Hz) separating dc and midrange frequencies
   f2    = hslider("hf_dumping", 6000, 1500, 0.49*fsmax, 1); // frequency (Hz) above f1 where T60 = t60m/2 (see below)
   t60dc = hslider("zero_decay", 3, 1, 8, 0.1); // desired decay time (t60) at frequency 0 (sec)
   t60m  = hslider("mid_decay", 2, 1, 8, 0.1); // desired decay time (t60) at midrange frequencies (sec)
   fsmax = 48000.0; //maximum sampling rate to be used (Hz)
   mix   = hslider("mix", 0.5, 0, 1, 0.01);

   out_level = _*gain, _*gain; 
   gain = db2linear(-40);
};

// topologies
// A - B - C
// B - A - C
// A/B - C
// B/A - C

effects = vgroup("effects", bus4 :> bus2 : flanger_effect : delay_effect : reverb_effect);
//effects = vgroup("effects", bus4 :> bus2 : flanger_effect);

