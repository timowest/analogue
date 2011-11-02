import("math.lib");
osclib = library("oscillator.lib");

process = triangle(440);

triangle(freq) = osclib.saw1(freq) : abs : (_*2.0-1.0);
