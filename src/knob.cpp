#include "knob.h"
#include <gdkmm/general.h>  // for cairo helper functions
#include <iostream>
#include <cstring>

#include <iostream>
#include <stdio.h>

Knob::Knob(float min, float max, float step) : value(0.0), min(min), max(max), step(step)
{  
  set_size_request(50, 50);
  range = max - min;
  sensitivity = range / step;
  activeColor = Gdk::Color("black");
  passiveColor = Gdk::Color("gray");

  add_events( Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON1_MOTION_MASK);
  signal_motion_notify_event().connect(mem_fun(this, &Knob::on_motion_notify));
  signal_button_press_event().connect(mem_fun(this, &Knob::on_button_press));
}

Knob::~Knob()
{
}

float Knob::get_value() 
{
    return value; 
}

void Knob::set_value(float val) 
{
    value = val;
}

sigc::signal<void> Knob::signal_value_changed()
{
    return value_changed;
}

bool Knob::on_motion_notify(GdkEventMotion* event) 
{
    float offset = (origin_y - event->y) * range / sensitivity;
    float new_value = origin_val + ((step == 0.0) ? offset : step * floor ((offset / step) + 0.5));   
    if (new_value > max) {
        new_value = max;
    } else if (new_value < min) {
        new_value = min;
    }   
    value = new_value;    
    refresh();
    return true;
}

bool Knob::on_button_press(GdkEventButton* event)
{
    origin_val = value;
    origin_y = event->y;
    return true;
}

void Knob::refresh() 
{
    // force our program to redraw the entire clock.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}

bool Knob::on_expose_event(GdkEventExpose* event) {
  Glib::RefPtr<Gdk::Window> window = get_window();
  
  if (window) {
    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int xc = width / 2;
    int yc = height / 2;
    double val = (value - min) / (max - min);

    double radius = 15.0;
    double angle1 = 0.75 * M_PI; 
    double angle2 = (0.75 + val * 1.5) * M_PI; 
    double angle3 = 2.25  * M_PI;

    cr->save();
    Gdk::Cairo::set_source_color(cr, activeColor);
    cr->set_line_width(6.0);
    cr->arc(xc, yc, radius, angle1, angle2);
    cr->stroke();
    cr->restore();

    Gdk::Cairo::set_source_color(cr, passiveColor);
    cr->set_line_width(6.0);
    cr->arc(xc, yc, radius, angle2, angle3);
    cr->stroke();

  } 

  return true;
} // on_expose_event()


