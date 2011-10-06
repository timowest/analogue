#ifndef PANEL_H
#define PANEL_H

#include <gtkmm.h>
#include <iostream>

using namespace Gtk;

class Panel : public VBox {
  public:
    Panel(const char* title, Widget* toggle, Widget* content) {
        set_border_width(5);
        strcpy(bold_title, "<b>");
        strcat(bold_title, title);
        strcat(bold_title, "</b>");

        Label* label = manage(new Label(bold_title));
        label->set_use_markup();   

        HBox* header = manage(new HBox());
        header->pack_start(*label, false, false);
        header->pack_end(*toggle, false, false);
        pack_start(*header);
        pack_start(*content);
    }

  private:
    char bold_title[40];
};

#endif //PANEL_H
