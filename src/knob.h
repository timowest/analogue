#ifndef KNOB_H
#define KNOB_H

// TODO : optimize imports
#include <gtkmm.h>

class Knob : public Gtk::DrawingArea
{
public:
  Knob(float min, float max, float step);
  virtual ~Knob();
  bool on_expose_event(GdkEventExpose* event);
  bool on_motion_notify(GdkEventMotion* event);
  bool on_button_press(GdkEventButton* event);
  float get_value();
  void set_value(float val);
  void refresh();
  sigc::signal<void> signal_value_changed();

protected:
  Gdk::Color bgColor, activeColor, passiveColor;
  float value;
  float min, max, step;
  float range, sensitivity, origin_val, origin_y;
  sigc::signal<void> value_changed;

};

#endif //KNOB_H
