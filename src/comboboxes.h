#ifndef COMBOBOXES_H
#define COMBOBOXES_H

#include <gtkmm.h>
#include <iostream>

#include "changeable.h"

class ModelColumns : public Gtk::TreeModel::ColumnRecord {
public:

  ModelColumns() { 
    add(col_name); 
  }

  Gtk::TreeModelColumn<Glib::ustring> col_name;

};

class OSCTypeComboBox : public Gtk::ComboBoxText, public Changeable {
public:

  OSCTypeComboBox(){
    append("Sine"); 
    append("Tri");
    append("Saw");
    append("Square");
    append("Rand");
  }

  float get_value() {
    return (float)get_active_row_number();
  }

  void set_value(float val) {
    set_active((int)val);
  }

  Gtk::Widget* get_widget() {
    return this;
  }

  void connect(sigc::slot<void> s) {
    signal_changed().connect( s );
  }

};

class FilterTypeComboBox : public Gtk::ComboBoxText, public Changeable {
public:

  FilterTypeComboBox(){
    append("Low"); 
    append("High");
    append("Band");
    append("Reject");
  }

  float get_value() {
    return (float)get_active_row_number();
  }

  void set_value(float val) {
    set_active((int)val);
  }

  Gtk::Widget* get_widget() {
    return this;
  }

  void connect(sigc::slot<void> s) {
    signal_changed().connect( s );
  }

};

#endif //COMBOBOXES_H
