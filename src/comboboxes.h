#ifndef COMBOBOXES_H
#define COMBOBOXES_H

#include <gtkmm.h>
#include <iostream>
#include <stdio.h>

#include "changeable.h"

class SelectComboBox : public Gtk::EventBox, public Changeable {
public:

  SelectComboBox(const char** labels, int count) : labels(labels), count(count){
    add(label);
    // menu shown on button press
    signal_button_press_event().connect(sigc::mem_fun(*this, &SelectComboBox::on_button_press_event) );

    // menu creation
    for (int i = 0; i < count; i++) {
        Gtk::MenuItem* menuItem = manage(new Gtk::MenuItem(labels[i]));
        menuItem->signal_activate().connect(
            sigc::bind(sigc::mem_fun(*this, &SelectComboBox::on_menu_selection), i));
        menuPopup.append(*menuItem);
    }
    menuPopup.show_all();
    set_value(0.0f);
  }

  bool on_button_press_event(GdkEventButton* event) {
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
      menuPopup.popup(event->button, event->time);
      return true;
    } else {
      return false;
    }
  }

  void on_menu_selection(int i) {    
    index = i;
    label.set_text(labels[index]);
    value_changed.emit();
  }

  float get_value() {
    return (float)index;
  }

  void set_value(float val) {
    index = (int)val;
    label.set_text(labels[index]);
  }

  Gtk::Widget* get_widget() {
    return this;
  }

  void connect(sigc::slot<void> s) {
    value_changed.connect(s);
  }

private:
  const char** labels;
  int count;
  int index;

  Gtk::Menu menuPopup;
  Gtk::EventBox eventBox;
  Gtk::Label label;

  sigc::signal<void> value_changed;
  
};

const char* oscType[] = {"Sin", "Tri", "Saw", "Squ", "Rnd"};

const char* filterType[] = {"Low", "Hi", "Bnd", "Rej"};

// TODO : use generics here ?!?

class OSCTypeComboBox : public SelectComboBox {
public:   
    OSCTypeComboBox() : SelectComboBox(oscType, 5) {}
};

class FilterTypeComboBox : public SelectComboBox {
public:   
    FilterTypeComboBox() : SelectComboBox(filterType, 4) {}
};

#endif //COMBOBOXES_H
