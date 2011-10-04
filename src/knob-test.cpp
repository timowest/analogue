#include "knob.h"  
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);

  Knob knob(0.0, 1.0, 0.01);

  Gtk::Window window;
  window.set_title("Analogue");
  window.set_default_size(800, 400);
  window.add(knob);
  window.show_all();

  Gtk::Main::run(window);

  return 0;

}
