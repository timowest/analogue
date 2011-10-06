#ifndef TOGGLE_H
#define TOGGLE_H

#include <gtkmm.h>
#include <iostream>

#include "changeable.h"

class Toggle : public Gtk::ToggleButton, public Changeable {
public:

  Toggle(bool invert = false) {  
    set_size_request(15, 15);
    if (invert) {
      on = 0.0f;
      off = 1.0f;
    } else {
      on = 1.0f;
      off = 0.0f;
    } 
  }

  float get_value() {
    return get_active() ? on : off;
  }

  void set_value(float val) {
    set_active(val == on);
  }

  Gtk::Widget* get_widget() {
    return this;
  }

  void connect(sigc::slot<void> s) {
    signal_toggled().connect( s );
  }

private:

  float on, off;

};

#endif //TOGGLE_H
