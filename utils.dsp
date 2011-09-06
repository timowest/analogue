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

// utilities

split(ratio) = _ <: ((1-ratio) * _, ratio * _);

// mix variant of select2
mix2(ratio, a, b) = ratio * b + (1 - ratio) * a;

select4(i) = select2(i > 2, select3(i, _, _, _), _);

select5(i) = select2(i > 3, select4(i, _, _, _, _), _);

fade_in(samples, gate) = (fade(gate) ~ _) * _
with {
    fade(gate,x) = select2(x < 1, 1, select2(gate != 0, 0, x + step));
    step = 1/samples;
};

normalize(min_val,max_val) = max(min_val) : min(max_val);

A4 = 69.0; // 440 Hz

key2hz(base_freq, x) = base_freq * pow(2.0, x / 12); 
