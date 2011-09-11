BUNDLE = Analogue.lv2
INSTALL_DIR = /usr/local/lib/lv2
ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/

$(BUNDLE): manifest.ttl analogue.ttl Analogue.so AnalogueGUI.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp $^ $(BUNDLE)

Analogue.so: src/Analogue.cpp gen/Analogue.peg gen/AnalogueMeta.h gen/dsp.cpp
	g++ -shared -Wall -fPIC -DPIC src/Analogue.cpp src/dsp.cpp $(PAQ) $(FAUST) -Igen/ -lm -o Analogue.so

AnalogueGUI.so: src/AnalogueGUI.cpp gen/Analogue.peg gen/AnalogueMeta.h
	g++ -shared -Wall -fPIC -DPIC src/AnalogueGUI.cpp $(PAQ) -Igen/ -o AnalogueGUI.so

gen/dsp.cpp:
	faust -a minimal.cpp faust/analogue-poly.dsp > gen/dsp.cpp

gen/Analogue.peg:
	lv2peg analogue.ttl gen/Analogue.peg

gen/AnalogueMeta.h:
	python portmeta.py

standalone: 
	faust -a alsa-gtk.cpp faust/standalone.dsp > gen/standalone.cpp
	g++ -Wall gen/standalone.cpp  $(ALSA_GTK) $(FAUST) -lm -o standalone

oscdemo:
	faust -a alsa-gtk.cpp faust/oscdemo.dsp > gen/oscdemo.cpp
	g++ -Wall gen/oscdemo.cpp  $(ALSA_GTK) $(FAUST) -lm -o oscdemo

simple:
	faust -a alsa-gtk.cpp faust/simple.dsp > gen/simple.cpp
	g++ -Wall gen/simple.cpp  $(ALSA_GTK) $(FAUST) -lm -o simple

dumpports: gen/dsp.cpp
	g++ -Wall src/printttl.cpp src/dsp.cpp $(PAQ) $(FAUST) -lm -lsndfile -o dumpports.out
	./dumpports.out > gen/ports.ttl

svg:
	faust -svg faust/analogue.dsp
	faust -svg faust/oscdemo.dsp
	faust -svg faust/standalone.dsp
	faust -svg faust/simple.dsp

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) *.so *.out gen/* faust/*-svg standalone oscdemo simple
