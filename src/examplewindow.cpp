#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_MyWidget(0.0, 1.0, 0.1), m_Button_Quit("Quit")
{
  set_title("Custom Widget example");
  set_border_width(6);
  set_default_size(400, 200);

  add(m_VBox);
  m_VBox.pack_start(m_MyWidget, Gtk::PACK_EXPAND_WIDGET);
  m_MyWidget.set_value(0.5);
  m_MyWidget.show();

  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(6);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}
