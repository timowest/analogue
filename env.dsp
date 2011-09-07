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

// envelopes
// driven by gate

filter1_env = vgroup("filter1_env", env);

filter2_env = vgroup("filter2_env", env);

amp1_env = vgroup("amp1_env", env);

amp2_env = vgroup("amp2_env", env);

// helpers

env = adsr(
   hslider("attack", 0, 0, 4, 0.01) * SR,
   hslider("decay", 1, 0, 4, 0.01),
   hslider("sustain", 1, 0, 1, 0.01) * 100,
   hslider("release", 1, 0, 4, 0.01));
