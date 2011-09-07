//-----------------------------------------------------
//
// Code generated with Faust 0.9.43 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
#include <math.h>
#include <cmath>
template <int N> inline float faustpower(float x) 		{ return powf(x,N); } 
template <int N> inline double faustpower(double x) 	{ return pow(x,N); }
template <int N> inline int faustpower(int x) 			{ return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x) 		{ return 1; }
template <> 	 inline int faustpower<1>(int x) 		{ return x; }
/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it 
    and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 3 of 
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License 
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work 
	that contains this FAUST architecture section and distribute  
	that work under terms of your choice, so long as this FAUST 
	architecture section is not modified. 


 ************************************************************************
 ************************************************************************/

#include <libgen.h>
#include <stdlib.h>
#include <iostream>

#include "gui/FUI.h"
#include "misc.h"
#include "gui/faustgtk.h"
#include "audio/alsa-dsp.h"

#ifdef OSCCTRL
#include "gui/OSCUI.h"
#endif

/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/



#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

typedef long double quad;

class mydsp : public dsp {
  private:
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	int 	iConst0;
	float 	fConst1;
	float 	fRec0[2];
	float 	fConst2;
	float 	fConst3;
	float 	fVec1[2];
	float 	fVec2[2];
	float 	fConst4;
	float 	fVec3[2];
	float 	fRec1[2];
	float 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fConst5;
	FAUSTFLOAT 	fbutton0;
	float 	fRec3[2];
	int 	IOTA;
	float 	fVec4[262144];
	int 	iConst6;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	int 	iRec4[2];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	int 	iConst7;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	int 	iRec6[2];
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	float 	fRec7[2];
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	float 	fConst8;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT 	fslider33;
	float 	fConst9;
	float 	fRec9[2];
	float 	fConst10;
	float 	fConst11;
	float 	fVec5[2];
	float 	fConst12;
	float 	fConst13;
	float 	fVec6[2];
	float 	fRec10[2];
	float 	fRec11[2];
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	float 	fRec8[3];
	FAUSTFLOAT 	fslider37;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/version", "1.28");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/version", "1.10");
		m->declare("oscillator.lib/license", "STK-4.3");
	}

	virtual int getNumInputs() 	{ return 0; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		fslider0 = 0.5f;
		fslider1 = 0.0f;
		iConst0 = min(192000, max(1, fSamplingFreq));
		fConst1 = float(iConst0);
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fConst2 = (1.0f / fConst1);
		fConst3 = (2.0f / fConst1);
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		fConst4 = (6.283185307179586f / iConst0);
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fConst5 = (1.0f / iConst0);
		fbutton0 = 0.0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		IOTA = 0;
		for (int i=0; i<262144; i++) fVec4[i] = 0;
		iConst6 = (iConst0 - 1);
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		for (int i=0; i<2; i++) iRec4[i] = 0;
		fslider6 = 1.0f;
		fslider7 = 1.0f;
		fslider8 = 1.0f;
		fslider9 = 0.0f;
		iConst7 = faustpower<2>(iConst0);
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider10 = 0.0f;
		fslider11 = 0.0f;
		fslider12 = 64.0f;
		fslider13 = 0.0f;
		fslider14 = 0.0f;
		fslider15 = 1.0f;
		fslider16 = 0.0f;
		fslider17 = 0.0f;
		for (int i=0; i<2; i++) iRec6[i] = 0;
		fslider18 = 1.0f;
		fslider19 = 1.0f;
		fslider20 = 1.0f;
		fslider21 = 0.0f;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		fslider22 = 0.0f;
		fslider23 = 1.0f;
		fslider24 = 4.4e+02f;
		fConst8 = (3.141592653589793f / iConst0);
		fslider25 = 0.0f;
		fslider26 = 0.0f;
		fslider27 = 0.5f;
		fslider28 = 0.0f;
		fslider29 = 0.5f;
		fslider30 = 0.0f;
		fslider31 = 0.0f;
		fslider32 = 1.0f;
		fslider33 = 0.0f;
		fConst9 = (0.0022727272727272726f * fConst1);
		for (int i=0; i<2; i++) fRec9[i] = 0;
		fConst10 = (4.4e+02f / fConst1);
		fConst11 = (8.8e+02f / fConst1);
		for (int i=0; i<2; i++) fVec5[i] = 0;
		fConst12 = (0.0022727272727272726f * iConst0);
		fConst13 = (2764.601535159018f / iConst0);
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		fslider34 = 0.0f;
		fslider35 = 0.0f;
		fslider36 = 0.5f;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		fslider37 = 0.0f;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("simple");
		interface->openVerticalBox("midi");
		interface->addButton("gate", &fbutton0);
		interface->addHorizontalSlider("pitch", &fslider12, 64.0f, 32.0f, 1e+02f, 1.0f);
		interface->closeBox();
		interface->openHorizontalBox("simple");
		interface->openVerticalBox("amp1");
		interface->openVerticalBox("amp2_env");
		interface->addHorizontalSlider("attack", &fslider9, 0.0f, 0.0f, 4.0f, 0.01f);
		interface->addHorizontalSlider("decay", &fslider8, 1.0f, 0.0f, 4.0f, 0.01f);
		interface->addHorizontalSlider("release", &fslider7, 1.0f, 0.0f, 4.0f, 0.01f);
		interface->addHorizontalSlider("sustain", &fslider6, 1.0f, 0.0f, 1.0f, 0.01f);
		interface->closeBox();
		interface->addHorizontalSlider("env_to_pan", &fslider10, 0.0f, -0.5f, 0.5f, 0.01f);
		interface->addHorizontalSlider("kbd_to_level", &fslider14, 0.0f, -0.1f, 0.1f, 0.01f);
		interface->addHorizontalSlider("kbd_to_pan", &fslider11, 0.0f, -0.1f, 0.1f, 0.01f);
		interface->addHorizontalSlider("level", &fslider15, 1.0f, 0.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("lfo_to_level", &fslider16, 0.0f, -0.5f, 0.5f, 0.01f);
		interface->addHorizontalSlider("lfo_to_pan", &fslider5, 0.0f, -0.5f, 0.5f, 0.01f);
		interface->addHorizontalSlider("pan", &fslider13, 0.0f, -1.0f, 1.0f, 0.01f);
		interface->closeBox();
		interface->openVerticalBox("filter1");
		interface->addHorizontalSlider("cutoff", &fslider24, 4.4e+02f, 0.0f, 5e+03f, 1e+01f);
		interface->addHorizontalSlider("env_to_f", &fslider22, 0.0f, -12.0f, 12.0f, 0.1f);
		interface->addHorizontalSlider("env_to_q", &fslider26, 0.0f, -1.0f, 1.0f, 0.1f);
		interface->openVerticalBox("filter1_env");
		interface->addHorizontalSlider("attack", &fslider21, 0.0f, 0.0f, 4.0f, 0.01f);
		interface->addHorizontalSlider("decay", &fslider20, 1.0f, 0.0f, 4.0f, 0.01f);
		interface->addHorizontalSlider("release", &fslider19, 1.0f, 0.0f, 4.0f, 0.01f);
		interface->addHorizontalSlider("sustain", &fslider18, 1.0f, 0.0f, 1.0f, 0.01f);
		interface->closeBox();
		interface->addHorizontalSlider("kbd", &fslider23, 1.0f, -12.0f, 12.0f, 0.1f);
		interface->addHorizontalSlider("lfo_to_f", &fslider17, 0.0f, -12.0f, 12.0f, 0.1f);
		interface->addHorizontalSlider("lfo_to_q", &fslider25, 0.0f, -1.0f, 1.0f, 0.1f);
		interface->addHorizontalSlider("q", &fslider27, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("type", &fslider37, 0.0f, 0.0f, 3.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("lfo1");
		interface->addHorizontalSlider("delay", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("fade_in", &fslider3, 0.0f, 0.0f, 5.0f, 0.01f);
		interface->addHorizontalSlider("freq", &fslider1, 0.0f, 1.0f, 5e+01f, 1.0f);
		interface->addHorizontalSlider("type", &fslider2, 0.0f, 0.0f, 2.0f, 1.0f);
		interface->addHorizontalSlider("width", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->closeBox();
		interface->openVerticalBox("osc1");
		interface->addHorizontalSlider("f1_to_f2", &fslider35, 0.0f, 0.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("finetune", &fslider31, 0.0f, -1.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("kbd", &fslider32, 1.0f, -12.0f, 12.0f, 0.1f);
		interface->addHorizontalSlider("level", &fslider36, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->addHorizontalSlider("lfo_to_p", &fslider33, 0.0f, -12.0f, 12.0f, 0.1f);
		interface->addHorizontalSlider("lfo_to_w", &fslider28, 0.0f, -0.5f, 0.5f, 0.01f);
		interface->addHorizontalSlider("tune", &fslider30, 0.0f, -24.0f, 24.0f, 1.0f);
		interface->addHorizontalSlider("type", &fslider34, 0.0f, 0.0f, 2.0f, 1.0f);
		interface->addHorizontalSlider("width", &fslider29, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->closeBox();
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = fslider0;
		float 	fSlow1 = fslider1;
		float 	fSlow2 = (fConst1 / fSlow1);
		float 	fSlow3 = (fConst2 * fSlow1);
		float 	fSlow4 = (fConst3 * fSlow1);
		float 	fSlow5 = (iConst0 / fSlow1);
		float 	fSlow6 = cosf((fConst4 * fSlow1));
		float 	fSlow7 = sqrtf(((1 + fSlow6) / (1 - fSlow6)));
		float 	fSlow8 = (1.0f / fSlow7);
		float 	fSlow9 = (0 - fSlow7);
		int 	iSlow10 = int(fslider2);
		float 	fSlow11 = fslider3;
		float 	fSlow12 = ((int(((iConst0 * fSlow11) > 0)))?(fConst5 / fSlow11):1);
		float 	fSlow13 = fbutton0;
		int 	iSlow14 = int((fSlow13 != 0));
		int 	iSlow15 = int((int((iConst0 * fslider4)) & iConst6));
		float 	fSlow16 = fslider5;
		int 	iSlow17 = (fSlow13 > 0);
		int 	iSlow18 = (fSlow13 <= 0);
		float 	fSlow19 = (100 * fslider6);
		float 	fSlow20 = (fSlow19 + (0.001f * (fSlow19 == 0.0f)));
		float 	fSlow21 = fslider7;
		float 	fSlow22 = (1 - (1.0f / powf((1e+03f * fSlow20),(1.0f / ((fSlow21 == 0.0f) + (iConst0 * fSlow21))))));
		float 	fSlow23 = fslider8;
		float 	fSlow24 = (1 - powf(fSlow20,(1.0f / ((fSlow23 == 0.0f) + (iConst0 * fSlow23)))));
		float 	fSlow25 = fslider9;
		float 	fSlow26 = (1.0f / (((iConst0 * fSlow25) == 0.0f) + (iConst7 * fSlow25)));
		float 	fSlow27 = fslider10;
		float 	fSlow28 = (fslider12 - 69.0f);
		float 	fSlow29 = (fslider13 + (0.1f * (fSlow28 * fslider11)));
		float 	fSlow30 = (fslider15 + (0.1f * (fSlow28 * fslider14)));
		float 	fSlow31 = fslider16;
		float 	fSlow32 = fslider17;
		float 	fSlow33 = (100 * fslider18);
		float 	fSlow34 = (fSlow33 + (0.001f * (fSlow33 == 0.0f)));
		float 	fSlow35 = fslider19;
		float 	fSlow36 = (1 - (1.0f / powf((1e+03f * fSlow34),(1.0f / ((fSlow35 == 0.0f) + (iConst0 * fSlow35))))));
		float 	fSlow37 = fslider20;
		float 	fSlow38 = (1 - powf(fSlow34,(1.0f / ((fSlow37 == 0.0f) + (iConst0 * fSlow37)))));
		float 	fSlow39 = fslider21;
		float 	fSlow40 = (1.0f / (((iConst0 * fSlow39) == 0.0f) + (iConst7 * fSlow39)));
		float 	fSlow41 = fslider22;
		float 	fSlow42 = (fSlow28 * fslider23);
		float 	fSlow43 = (fConst8 * fslider24);
		float 	fSlow44 = fslider25;
		float 	fSlow45 = fslider26;
		float 	fSlow46 = fslider27;
		float 	fSlow47 = fslider28;
		float 	fSlow48 = fslider29;
		float 	fSlow49 = ((fSlow28 * fslider32) + (fslider31 + fslider30));
		float 	fSlow50 = fslider33;
		int 	iSlow51 = int(fslider34);
		float 	fSlow52 = fslider35;
		float 	fSlow53 = (fslider36 * (fSlow52 + (1 - fSlow52)));
		float 	fSlow54 = fslider37;
		int 	iSlow55 = int(fSlow54);
		int 	iSlow56 = int((fSlow54 > 2));
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec0[0] = fmodf((1.0f + fRec0[1]),fSlow2);
			float fTemp0 = faustpower<2>(((fSlow4 * fRec0[0]) - 1.0f));
			fVec1[0] = fTemp0;
			fVec2[0] = 0.25f;
			fVec3[0] = fSlow7;
			float fTemp1 = (fSlow8 * (((1 + fVec3[1]) - iVec0[1]) * fRec2[1]));
			float fTemp2 = (fSlow6 * (fRec1[1] + fTemp1));
			fRec1[0] = ((1 + (fTemp1 + fTemp2)) - iVec0[1]);
			fRec2[0] = (fTemp2 - fRec1[1]);
			fRec3[0] = ((int((fRec3[1] < 1)))?((iSlow14)?(fSlow12 + fRec3[1]):0):1);
			fVec4[IOTA&262143] = (fRec3[0] * ((iSlow10==0)? (fSlow9 * fRec2[0]) : ((iSlow10==1)?(fSlow5 * (fVec2[1] * (fVec1[0] - fVec1[1]))):((2 * float(((fSlow3 * fRec0[0]) <= fSlow0))) - 1)) ));
			float fTemp3 = fVec4[(IOTA-iSlow15)&262143];
			iRec4[0] = (iSlow17 & (iRec4[1] | (fRec5[1] >= 1)));
			int iTemp4 = (iSlow18 & (fRec5[1] > 0));
			fRec5[0] = (((iTemp4 == 0) | (fRec5[1] >= 1e-06f)) * ((fSlow26 * (((iRec4[1] == 0) & iSlow17) & (fRec5[1] < 1))) + (fRec5[1] * ((1 - (fSlow24 * (iRec4[1] & (fRec5[1] > fSlow19)))) - (fSlow22 * iTemp4)))));
			float fTemp5 = (1 + min(1, max(-1, (fSlow29 + ((fSlow27 * fRec5[0]) + (fSlow16 * fTemp3))))));
			iRec6[0] = (iSlow17 & (iRec6[1] | (fRec7[1] >= 1)));
			int iTemp6 = (iSlow18 & (fRec7[1] > 0));
			fRec7[0] = (((iTemp6 == 0) | (fRec7[1] >= 1e-06f)) * ((fSlow40 * (((iRec6[1] == 0) & iSlow17) & (fRec7[1] < 1))) + (fRec7[1] * ((1 - (fSlow38 * (iRec6[1] & (fRec7[1] > fSlow33)))) - (fSlow36 * iTemp6)))));
			float fTemp7 = tanf((fSlow43 * powf(2.0f,(0.08333333333333333f * (fSlow42 + ((fSlow41 * fRec7[0]) + (fSlow32 * fTemp3)))))));
			float fTemp8 = (2.0f / (fSlow46 + ((fSlow45 * fRec7[0]) + (fSlow44 * fTemp3))));
			float fTemp9 = (1.0f / fTemp7);
			float fTemp10 = (1 + ((fTemp9 + fTemp8) / fTemp7));
			float fTemp11 = powf(2.0f,(0.08333333333333333f * ((fSlow50 * fTemp3) + fSlow49)));
			fRec9[0] = fmodf((1.0f + fRec9[1]),(fConst9 / fTemp11));
			float fTemp12 = (fRec9[0] * fTemp11);
			float fTemp13 = faustpower<2>(((fConst11 * fTemp12) - 1.0f));
			fVec5[0] = fTemp13;
			float fTemp14 = cosf((fConst13 * fTemp11));
			float fTemp15 = sqrtf(((1 + fTemp14) / (1 - fTemp14)));
			fVec6[0] = fTemp15;
			float fTemp16 = ((((1 + fVec6[1]) - iVec0[1]) * fRec11[1]) / fVec6[0]);
			float fTemp17 = (fTemp14 * (fRec10[1] + fTemp16));
			fRec10[0] = ((1 + (fTemp16 + fTemp17)) - iVec0[1]);
			fRec11[0] = (fTemp17 - fRec10[1]);
			float fTemp18 = (fSlow53 * ((iSlow51==0)? (fRec11[0] * (0 - fVec6[0])) : ((iSlow51==1)?(fConst12 * ((fVec2[1] * (fVec5[0] - fVec5[1])) / fTemp11)):((2 * float(((fConst10 * fTemp12) <= min(1, max(0, (fSlow48 + (fSlow47 * fTemp3))))))) - 1)) ));
			fRec8[0] = (fTemp18 - (((fRec8[2] * (1 + ((fTemp9 - fTemp8) / fTemp7))) + (2 * (fRec8[1] * (1 - (1.0f / faustpower<2>(fTemp7)))))) / fTemp10));
			float fTemp19 = (((fRec8[2] * (0 - fTemp9)) + (fRec8[0] / fTemp7)) / fTemp10);
			float fTemp20 = ((fRec8[2] + (fRec8[0] + (2.0f * fRec8[1]))) / fTemp10);
			float fTemp21 = ((fRec5[0] * ((iSlow56)?(fTemp18 - fTemp19):((iSlow55==0)? fTemp20 : ((iSlow55==1)?(fTemp18 - fTemp20):fTemp19) ))) * min(1, max(0, ((fSlow31 * fTemp3) + fSlow30))));
			output0[i] = (FAUSTFLOAT)(fTemp21 * (1 - (0.5f * fTemp5)));
			output1[i] = (FAUSTFLOAT)(0.5f * (fTemp21 * fTemp5));
			// post processing
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fVec6[1] = fVec6[0];
			fVec5[1] = fVec5[0];
			fRec9[1] = fRec9[0];
			fRec7[1] = fRec7[0];
			iRec6[1] = iRec6[0];
			fRec5[1] = fRec5[0];
			iRec4[1] = iRec4[0];
			IOTA = IOTA+1;
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fVec3[1] = fVec3[0];
			fVec2[1] = fVec2[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			iVec0[1] = iVec0[0];
		}
	}
};



/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
mydsp	DSP;

list<GUI*>               GUI::fGuiList;

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	char	appname[256];
	char  	rcfilename[256];
	char* 	home = getenv("HOME");
	
	snprintf(appname, 255, "%s", basename(argv[0]));
	snprintf(rcfilename, 255, "%s/.%src", home, appname);

	GUI* interface 	= new GTKUI (appname, &argc, &argv);
	FUI* finterface	= new FUI();
	DSP.buildUserInterface(interface);
	DSP.buildUserInterface(finterface);

#ifdef OSCCTRL
	GUI* oscinterface = new OSCUI(appname, argc, argv);
	DSP.buildUserInterface(oscinterface);
#endif

	alsaaudio audio (argc, argv, &DSP);
	audio.init(appname, &DSP);
	finterface->recallState(rcfilename);	
	audio.start();
	
#ifdef OSCCTRL
	oscinterface->run();
#endif
	interface->run();
	
	audio.stop();
	finterface->saveState(rcfilename);
  	return 0;
}


/********************END ARCHITECTURE SECTION (part 2/2)****************/

