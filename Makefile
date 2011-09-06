#BUNDLE = lv2-Flute.lv2
INSTALL_DIR = /usr/local/lib/lv2
ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`

standalone: 
	faust -a alsa-gtk.cpp standalone.dsp > standalone.cpp
	g++ -Wall standalone.cpp  $(ALSA_GTK) -lm -I/usr/local/lib/faust/ -o standalone

oscdemo:
	faust -a alsa-gtk.cpp oscdemo.dsp > oscdemo.cpp
	g++ -Wall oscdemo.cpp  $(ALSA_GTK) -lm -I/usr/local/lib/faust/ -o oscdemo

simple:
	faust -a alsa-gtk.cpp simple.dsp > simple.cpp
	g++ -Wall simple.cpp  $(ALSA_GTK) -lm -I/usr/local/lib/faust/ -o simple

clean:
	rm -rf *.cpp *-svg standalone oscdemo simple
