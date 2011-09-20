#include <gtkmm.h>
#include <lv2gui.hpp>

#include "knob.h"
#include "Analogue.peg"
#include "AnalogueMeta.h"

using namespace sigc;
using namespace Gtk;

class AnalogueGUI : public LV2::GUI<AnalogueGUI, LV2::URIMap<true>, LV2::WriteMIDI<false> > {
    public:

        AnalogueGUI(const std::string& URI) {
            int control_ports = p_n_ports - 3;

            //initialize sliders
            for (int i = 0; i < control_ports; i++) {
                // TODO : make sure max works inclusively
                scales[i] = manage(new Knob(p_port_meta[i].min, p_port_meta[i].max, p_port_meta[i].step));
            }

            /*unsigned char scale_size = 100;
            for (int i = 0; i < control_ports; i++) {
                scales[i]->set_size_request(scale_size, -1);
            }*/

            //connect widgets to control ports (change control values when sliders are moved)
            for (int i = 0; i < control_ports; i++) {
                slot<void> slot = compose(bind<0>(mem_fun(*this, &AnalogueGUI::write_control), i + 3),
                mem_fun(*scales[i], &Knob::get_value));
                scales[i]->signal_value_changed().connect(slot);
            }

            //connect all faders to the 'notify' function to inform the plugin to recalculate
            /*for (int i = 0; i < control_ports; i++) {
                scales[i]->signal_value_changed().connect(
            mem_fun(*this, &AnalogueGUI::notify_param_change));
            }*/

            mainBox.pack_start(*createFramedTable("OSC1", 61, 70), PACK_EXPAND_PADDING); // osc1
            mainBox.pack_start(*createFramedTable("OSC2", 70, control_ports), PACK_EXPAND_PADDING); // osc2
            mainBox.pack_start(*createFramedTable("Noise", 58, 61), PACK_EXPAND_PADDING); // noise
            mainBox.pack_start(*createFramedTable("LFO1", 48, 53), PACK_EXPAND_PADDING); // lfo1
            mainBox.pack_start(*createFramedTable("LFO2", 53, 58), PACK_EXPAND_PADDING); // lfo2
            mainBox.pack_start(*createFramedTable("Filter1", 22, 35), PACK_EXPAND_PADDING); // filter1
            mainBox.pack_start(*createFramedTable("Filter2", 35, 48), PACK_EXPAND_PADDING); // filter2
            mainBox.pack_start(*createFramedTable("Amp1", 0, 11), PACK_EXPAND_PADDING);  // amp1
            mainBox.pack_start(*createFramedTable("Amp2", 11, 22), PACK_EXPAND_PADDING); // amp2
            add(mainBox);
        }

        void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer) {
            if (port > 2) { 
                scales[port-3]->set_value(*static_cast<const float*>(buffer));
            }
        }

        Alignment *createFramedTable(const char* label, int start, int end) {
            Frame* frame = manage(new Frame());
            frame->set_label(label);
            frame->add(*createTable(start, end));
            return align(frame); 
        }

        Table *createTable(int start, int end) {
            Table* table = manage(new Table(2, end - start));
            for (int i = start; i < end; i++) {
                table->attach(*align(manage(new Label(p_port_meta[i].name))), 0, 1, i, i + 1);
                table->attach(*scales[i], 1, 2, i, i + 1);
            }
            return table;
            //return align(table);
        } 

        Alignment* align(Widget* widget) {
            Alignment* alignment = manage(new Alignment(0.0, 0.0, 0.0, 0.0));
            alignment->add(*widget);
            return alignment;
        }

    protected:
        HBox mainBox;
        
        Knob *scales[p_n_ports - 3];
};

static int _ = AnalogueGUI::register_class("http://www.westkamper.com/lv2/analogue/gui");
