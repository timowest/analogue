#ifndef DUMP_RDF_UI_H
#define DUMP_RDF_UI_H

#include "dsp.h"

#include <stdio.h>
#include <string.h>


class DumpRDFUI : public UI {    
    
    private:
        
        int counter; // first port index
        int boxIndex;
        const char* boxes[5];
        
        void addZone(const char* label) {
            addZone(label, 1.0f, 0.0f, 0.0f, 1.0f);
        }

        void addZone(const char* label, float init, float min, float max, float step) {
            if (strcmp(boxes[1],"midi") == 0) return;            

            char fullPath[50];
            strcpy(fullPath, boxes[1]);
            strcat(fullPath, "_");
            for (int i = 2; i < boxIndex; i++) {
                strcat(fullPath, boxes[i]);
                strcat(fullPath, "_");
            }
            strcat(fullPath, label);

            printf("    [ a lv2:ControlPort, lv2:InputPort; lv2:index %d; lv2:symbol \"%s\"; lv2:name \"%s\";\n", counter++, fullPath, label);
            printf("        lv2:minimum %f; lv2:maximum %f; lv2:default %f; ext:step %f ],\n", min, max, init, step);
            puts("");
        }

        void openBox(const char* label) {
            boxes[boxIndex++] = label;
        }
        
   public:

        DumpRDFUI() {
            counter = 3;
            boxIndex = 0;  
        }

        virtual void addButton(const char* label, float* zone) { 
            addZone(label); 
        }

        virtual void addToggleButton(const char* label, float* zone) { 
            addZone(label); 
        }

        virtual void addCheckButton(const char* label, float* zone) { 
            addZone(label); 
        }
        
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) { 
            addZone(label, init, min, max, step); 
        }

        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) { 
            addZone(label, init, min, max, step); 
        }

        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) { 
            addZone(label, init, min, max, step); 
        }
    
        virtual void addNumDisplay(const char* label, float* zone, int precision) { 
            //addZone(label); 
        }

        virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) {
            //addZone(label); 
        }

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) { 
            //addZone(label); 
        }

        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) { 
            //addZone(label); 
        }

        virtual void declare(float*, const char*, const char*) { }
    
        virtual void openFrameBox(const char* label) { 
            openBox(label);
        }

        virtual void openTabBox(const char* label) { 
            openBox(label);
        }

        virtual void openHorizontalBox(const char* label) { 
            openBox(label);
        }

        virtual void openVerticalBox(const char* label) { 
            openBox(label);
        }

        virtual void closeBox() { 
            boxIndex--;   
        }
    
        virtual void show() { }

        virtual void run() { }

};

#endif
