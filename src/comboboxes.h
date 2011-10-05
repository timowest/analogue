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

class OSCTypeComboBox : public Gtk::ComboBox, public Changeable {
public:

  OSCTypeComboBox(){
    treeModel = Gtk::ListStore::create(columns);
    set_model(treeModel);

    Gtk::TreeModel::Row row = *(treeModel->append());
    row[columns.col_name] = "Sine"; 
    row = *(treeModel->append());
    row[columns.col_name] = "Tri";
    row = *(treeModel->append());
    row[columns.col_name] = "Saw";
    row = *(treeModel->append());
    row[columns.col_name] = "Square";
    row = *(treeModel->append());
    row[columns.col_name] = "Rand";

    pack_start(columns.col_name);
  }

  virtual ~OSCTypeComboBox(){}

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

protected:

  ModelColumns columns;

  Glib::RefPtr<Gtk::ListStore> treeModel;

};

class FilterTypeComboBox : public Gtk::ComboBox, public Changeable {
public:

  FilterTypeComboBox(){
    treeModel = Gtk::ListStore::create(columns);
    set_model(treeModel);

    Gtk::TreeModel::Row row = *(treeModel->append());
    row[columns.col_name] = "Low"; 
    row = *(treeModel->append());
    row[columns.col_name] = "High";
    row = *(treeModel->append());
    row[columns.col_name] = "Band";
    row = *(treeModel->append());
    row[columns.col_name] = "Reject";

    pack_start(columns.col_name);
  }

  virtual ~FilterTypeComboBox(){}

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

protected:

  ModelColumns columns;

  Glib::RefPtr<Gtk::ListStore> treeModel;

};

#endif //COMBOBOXES_H
