#include "dsp.h"
#include "dump-rdf.h"

int main() {
    DumpRDFUI* ui = new DumpRDFUI();

    dsp* synth = createDSP();
    synth->init(44100);
    synth->buildUserInterface(ui);

    delete ui;
    delete synth;
};
