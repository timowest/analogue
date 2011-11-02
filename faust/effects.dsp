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
import("music.lib");
import("filter.lib");
import("freeverb.dsp");

import("utils.dsp");

// chorus & flanger

flanger_effect = vgroup("flanger", bypass2(bp, bus2 <: (bus2, flanger_stereo(dmax,curdel1,curdel2,depth,fb,invert)) : mix2_stereo(mix)))
with {
   // parameters
   bp     = checkbox("bypass");
   invert = checkbox("invert");
   freq   = hslider("speed", 0.5, 0, 10, 0.01); // Hz
   depth  = 1.0;
   //depth  = hslider("depth", 1, 0, 1, 0.001);
   fb     = hslider("feedback", 0, -0.999, 0.999, 0.01);
   //level  = hslider("output_level", 0, -60, 10, 0.1) : db2linear; // dB
   mix    = hslider("mix", 0.5, 0, 1, 0.01);

   dmax = 2048;
   dflange = 0.001 * SR * hslider("flange_delay", 10, 0, 20, 0.01); // ms
   //odflange = 0.001 * SR * hslider("delay_offset", 1, 0, 20, 0.001); // ms
   odflange = 0.0;
   curdel1 = odflange + dflange * (1 + oscrs(freq))/2; // sine for left 
   curdel2 = odflange + dflange * (1 + oscrc(freq))/2; // cosine for right
};

//delay 

delay_effect = vgroup("delay", bypass2(bp, bus2 <: (bus2, stereo_delay) : mix2_stereo(mix)))
with {
    bp            = checkbox("bypass");
    length        = 0.001 * SR * hslider("length", 10, 0, 1000, 1); // ms
    cutoff        = hslider("cutoff", 200, 0, 10000, 10);
    depth         = hslider("depth", 0.5, 0, 1, 0.01);
    lp_delay      = lowpass(2,cutoff) : delay(SR,length);
    stereo_delay  = bus2 : (((depth*_,depth*_,_,_) :> bus2) ~ (lp_delay, lp_delay));
    mix           = hslider("mix", 0.5, 0, 1, 0.01);
};

// reverb

// freeverb based
reverb_effect = vgroup("reverb", bypass2(bp, fxctrl(fixedgain, mix, stereoReverb(combfeed, allpassfeed, dampSlider, stereospread))))
with {
   bp             = checkbox("bypass");
   dampSlider     = hslider("damp",0.720, 0, 1, 0.025) * scaledamp;
   roomsizeSlider = hslider("roomSize", 0.540, 0, 1, 0.025) * scaleroom + offsetroom;
   combfeed       = roomsizeSlider;
   mix            = hslider("mix", 0.141, 0, 1, 0.025);
};


// topologies
// A - B - C
// B - A - C
// A/B - C
// B/A - C

effects = vgroup("effects", bus4 :> bus2 : flanger_effect : delay_effect : reverb_effect);


