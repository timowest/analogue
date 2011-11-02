#include "analogue-gui.cpp"  
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);

  AnalogueGUI guiBox("http://www.westkamper.com/lv2/analogue/gui"); 

  float controls[p_n_ports-3];
  for (int i = 0; i < p_n_ports-3; i++)  {
    controls[i] = p_port_meta[i].default_value;
  }

  Gtk::Window window;
  window.set_title("Analogue");
  window.set_default_size(800, 400);
  window.add(guiBox);
  window.show_all();

  Gtk::Main::run(window);

  return 0;

}
