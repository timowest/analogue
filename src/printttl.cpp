#include "dsp.h"
#include "DumpRDFUI.h"

int main() {
    DumpRDFUI* ui = new DumpRDFUI();

    dsp* synth = createDSP();
    synth->init(44100);
    synth->buildUserInterface(ui);

    delete ui;
    delete synth;
};
