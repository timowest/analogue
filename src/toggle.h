#ifndef TOGGLE_H
#define TOGGLE_H

#include <gtkmm.h>
#include <iostream>
#include <stdio.h>

#include "changeable.h"

class Toggle : public Gtk::DrawingArea, public Changeable {
public:

  Toggle(bool invert = false) : invert(invert) {  
    set_size_request(15, 15);
    value = 1.0f;

    add_events( Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(mem_fun(this, &Toggle::on_button_press));
  }

  bool on_expose_event(GdkEventExpose* event) {
    static Gdk::Color bgColor = Gdk::Color("black");
    Glib::RefPtr<Gdk::Window> window = get_window();
  
    if (window) {
      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      Gtk::Allocation allocation = get_allocation();
      int xc =  allocation.get_width() / 2;
      int yc = allocation.get_height() / 2;
      
      cr->set_antialias(ANTIALIAS_SUBPIXEL);
      
      Gdk::Cairo::set_source_color(cr, bgColor);
      cr->arc(xc, yc, 5.0, 0, 2.0 * M_PI);      
      if ((value == 1.0f && !invert) || (value == 0.0f && invert)) {
          cr->fill(); 
      } else {
          cr->stroke();      
      }         
    } 

    return true;
  } 

  bool on_button_press(GdkEventButton* event) {
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
      value = (value == 1.0) ? 0.0 : 1.0f;
      refresh();
      value_changed.emit();
      return true;
    } else {
      return false;
    }
  }

  float get_value() {
     return value;  
  }

  void set_value(float val) {
     value = val;
  }

  Gtk::Widget* get_widget() {
    return this;
  }

  void connect(sigc::slot<void> s) {
    value_changed.connect( s );
  }

  void refresh() {
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
  }

private:

  bool invert;

  float value;

  sigc::signal<void> value_changed;
};

#endif //TOGGLE_H
