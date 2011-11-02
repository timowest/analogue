osclib = library("oscillator.lib");

process = squarewave(440, 0.5);

squarewave(freq, width) = 2.0 * osclib.pulsetrainpos(freq, width) - 1.0;
