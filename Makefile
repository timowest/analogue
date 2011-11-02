BUNDLE = Analogue.lv2
INSTALL_DIR = /usr/local/lib/lv2
ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
JACK_GTK = `pkg-config --cflags --libs jack` `pkg-config --cflags --libs gtk+-2.0`
GTKMM = `pkg-config --cflags --libs gtkmm-2.4`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/
TESTS = gen/saw.cpp gen/saw2.cpp gen/sin.cpp gen/sin2.cpp gen/square.cpp gen/square2.cpp gen/tri.cpp gen/tri2.cpp

#CFLAGS=-O3 -mtune=native -march=native -mfpmath=sse -ffast-math -ftree-vectorize
CFLAGS=-mtune=native -march=native -mfpmath=sse -ffast-math -ftree-vectorize  

$(BUNDLE): manifest.ttl analogue.ttl Analogue.so AnalogueGUI.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp $^ $(BUNDLE)

Analogue.so: src/analogue.cpp gen/analogue.peg gen/analogue-meta.h gen/dsp.cpp
	g++ -shared -Wall -fPIC -DPIC src/analogue.cpp src/dsp.cpp $(PAQ) $(FAUST) $(CFLAGS) -Igen/ -lm -o Analogue.so

AnalogueGUI.so: src/analogue-gui.cpp gen/analogue.peg gen/analogue-meta.h
	g++ -shared -Wall -fPIC -DPIC src/analogue-gui.cpp $(GTKMM) $(PAQ) $(CFLAGS) -Igen/ -o AnalogueGUI.so

guitest: src/analogue-gui.cpp gen/analogue.peg gen/analogue-meta.h
	g++ -Wall src/analogue-gui-test.cpp $(GTKMM) $(PAQ) $(CFLAGS) -Igen/ -o guitest.out

knobtest: 
	g++ -Wall src/knob-test.cpp $(GTKMM) $(PAQ) $(CFLAGS) -Igen/ -o knobtest.out

comboboxestest: 
	g++ -Wall src/comboboxes-test.cpp $(GTKMM) $(PAQ) $(CFLAGS) -Igen/ -o comboboxestest.out

gen:
	mkdir gen

gen/dsp.cpp: gen
	faust -sch -fun -vec -a minimal.cpp faust/analogue-poly.dsp > gen/dsp.cpp

gen/analogue.peg: gen
	lv2peg analogue.ttl gen/analogue.peg

gen/analogue-meta.h: gen
	python portmeta.py

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

test2:
	faust -fun -vec -a alsa-gtk.cpp faust/test2.dsp > gen/test2.cpp
	g++ -Wall gen/test2.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o test2.out

gen/%.cpp: test/%-test.dsp
	faust -a minimal.cpp -cn $(patsubst gen/%.cpp,%,$@)dsp $< > $@

tests: $(TESTS)
	g++ -Wall -fpermissive test/tests.cpp $(FAUST) -lm -Igen/ -Isrc/ -lsndfile -o tests.out
	./tests.out

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
