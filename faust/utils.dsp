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

music = library("music.lib");

// utilities

split(ratio) = _ <: ((1-ratio) * _, ratio * _);

// mix variant of select2
mix2(ratio, a, b) = ratio * b + (1 - ratio) * a;

mix2_stereo(ratio, al, ar, bl, br) = mix2(ratio, al, bl), mix2(ratio, ar, br);

multiselect(n,s) = interleave(n,2) <: par(i,n, select2(s));

select4(i,a,b,c,d) = select2(i > 2, select3(i,a,b,c), d);

select5(i,a,b,c,d,e) = select2(i > 3, select4(i,a,b,c,d), e);

select6(i,a,b,c,d,e,f) = select2(i > 2, select3(i,a,b,c), select3(i-2,d,e,f));

select7(i,a,b,c,d,e,f,g) = select2(i > 3, select4(i,a,b,c,d), select3(i-3,e,f,g));

select8(i,a,b,c,d,e,f,g,h) = select2(i > 3, select4(i,a,b,c,d), select4(i-3,e,f,g,h));

fade_in(samples, gate) = select2(samples > 0, gate, fade(gate) ~ _) * _
with {
    fade(gate, x) = select2(x < 1, gate, x + (1/samples));
};

normalize(min_val,max_val) = max(min_val) : min(max_val);

bpm = nentry("/h:main/bpm", 120, 40, 280, 1);

A4 = 69.0; // 440 Hz

key2hz(base_freq, x) = base_freq * pow(2.0, x / 12); 

env = music.adsr(
   hslider("attack", 0, 0, 2, 0.005),
   hslider("decay", 1, 0, 4, 0.01),
   hslider("sustain", 1, 0, 1, 0.01) * 100,
   hslider("release", 1, 0, 4, 0.01));

