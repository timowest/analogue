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

filter1_env = vgroup("filter1_env", env(
   hslider("filter1_env_attack", 0, 0, 4, 0.01),
   hslider("filter1_env_decay", 1, 0, 4, 0.01),
   hslider("filter1_env_sustain", 1, 0, 1, 0.01),
   hslider("filter1_env_release", 1, 0, 4, 0.01)));

filter2_env = vgroup("filter2_env", env(
   hslider("filter2_env_attack", 0, 0, 4, 0.01),
   hslider("filter2_env_decay", 1, 0, 4, 0.01),
   hslider("filter2_env_sustain", 1, 0, 1, 0.01),
   hslider("filter2_env_release", 1, 0, 4, 0.01)));

amp1_env = vgroup("amp1_env", env(
   hslider("amp1_env_attack", 0, 0, 4, 0.01),
   hslider("amp1_env_decay", 1, 0, 4, 0.01),
   hslider("amp1_env_sustain", 1, 0, 1, 0.01),
   hslider("amp1_env_release", 1, 0, 4, 0.01)));

amp2_env = vgroup("amp2_env", env(
   hslider("amp2_env_attack", 0, 0, 4, 0.01),
   hslider("amp2_env_decay", 1, 0, 4, 0.01),
   hslider("amp2_env_sustain", 1, 0, 1, 0.01),
   hslider("amp2_env_release", 1, 0, 4, 0.01)));

// helpers

env(a, d, s, r) = adsr(a * SR, d, s * 100, r);
