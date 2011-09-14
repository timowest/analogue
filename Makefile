BUNDLE = Analogue.lv2
INSTALL_DIR = /usr/local/lib/lv2
ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/

#CFLAGS=-O3 -mtune=native -march=native -mfpmath=sse -ffast-math -ftree-vectorize
CFLAGS=-mtune=native -march=native -mfpmath=sse -ffast-math -ftree-vectorize  

$(BUNDLE): manifest.ttl analogue.ttl Analogue.so AnalogueGUI.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp $^ $(BUNDLE)

Analogue.so: src/Analogue.cpp gen/Analogue.peg gen/AnalogueMeta.h gen/dsp.cpp
	g++ -shared -Wall -fPIC -DPIC src/Analogue.cpp src/dsp.cpp $(PAQ) $(FAUST) $(CFLAGS) -Igen/ -lm -o Analogue.so

AnalogueGUI.so: src/AnalogueGUI.cpp gen/Analogue.peg gen/AnalogueMeta.h
	g++ -shared -Wall -fPIC -DPIC src/AnalogueGUI.cpp $(PAQ) $(CFLAGS) -Igen/ -o AnalogueGUI.so

gen/dsp.cpp:
	faust -sch -fun -vec -a minimal.cpp faust/analogue-poly.dsp > gen/dsp.cpp

gen/Analogue.peg:
	lv2peg analogue.ttl gen/Analogue.peg

gen/AnalogueMeta.h:
	python portmeta.py

test: gen/Analogue.peg gen/AnalogueMeta.h gen/dsp.cpp
	g++ -Wall src/LongNoteTest.cpp src/Analogue.cpp src/dsp.cpp $(PAQ) $(FAUST) -lm -lsndfile -Igen/ -o test.out
	./test.out

standalone: 
	faust -fun -vec -a alsa-gtk.cpp faust/standalone.dsp > gen/standalone.cpp
	g++ -Wall gen/standalone.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o standalone.out

poly: 
	faust -sch -fun -vec -a alsa-gtk.cpp faust/standalone-poly.dsp > gen/standalone-poly.cpp
	g++ -Wall gen/standalone-poly.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o standalone-poly.out

oscdemo:
	faust -fun -vec -a alsa-gtk.cpp faust/oscdemo.dsp > gen/oscdemo.cpp
	g++ -Wall gen/oscdemo.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o oscdemo.out

simple:
	faust -fun -vec -a alsa-gtk.cpp faust/simple.dsp > gen/simple.cpp
	g++ -Wall gen/simple.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o simple.out

dumpports: gen/dsp.cpp
	g++ -Wall src/printttl.cpp src/dsp.cpp $(PAQ) $(FAUST) -lm -lsndfile -o dumpports.out
	./dumpports.out > gen/ports.ttl

svg:
	faust -svg faust/analogue.dsp
	faust -svg faust/analogue-poly.dsp
	faust -svg faust/oscdemo.dsp
	faust -svg faust/standalone.dsp
	faust -svg faust/simple.dsp

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) *.so *.out gen/* faust/*-svg 
