#ifndef COLLECTOR_UI_H
#define COLLECTOR_UI_H

#include "dsp.h"

#include <map>
#include <string>
//#include <iostream>

class CollectorUI : public UI {    
    
   public:

        CollectorUI(){
            boxIndex = 0;  
            inputs = 0;
            outputs = 0;
        }    

        virtual void addButton(const char* label, float* zone) { 
            addZone(label, zone); 
        }

        virtual void addToggleButton(const char* label, float* zone) { 
            addZone(label, zone); 
        }

        virtual void addCheckButton(const char* label, float* zone) { 
            addZone(label, zone); 
        }
        
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) { 
            addZone(label, zone); 
        }

        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)     { 
            addZone(label, zone); 
        }

        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) { 
            addZone(label, zone); 
        }
    
        virtual void addNumDisplay(const char* label, float* zone, int precision) { 
            addZone(label, zone); 
        }

        virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) {
            addZone(label, zone); 
        }

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) { 
            addZone(label, zone); 
        }

        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) { 
            addZone(label, zone); 
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

        float** getInputs() {
            return inputs;
        }

        float** getOutputs() {
            return outputs;
        }    

        void setInputs(float** i) {
            inputs = i;
        }

        void setOutputs(float** o) {
            outputs = o;
        }

        float* getZone(std::string name) {
            return labelToZone[name];
        }

    private:
    
        float** inputs;
        float** outputs;
        int boxIndex;
        const char* boxes[5];

        std::map<std::string, float *> labelToZone;

        void addZone(const char* label, float* zone) {
            char fullPath[50];
            strcpy(fullPath, boxes[1]);
            strcat(fullPath, "_");
            for (int i = 2; i < boxIndex; i++) {
                strcat(fullPath, boxes[i]);
                strcat(fullPath, "_");
            }
            strcat(fullPath, label);
            //std::cout << fullPath << std::endl;

            std::string name(fullPath);
            labelToZone[name] = zone;
        }
        
        void openBox(const char* label) {
            boxes[boxIndex++] = label;
        }

};

#endif
