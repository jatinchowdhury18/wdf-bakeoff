/* ------------------------------------------------------------
name: "lpf2"
Code generated with Faust 2.32.6 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	int iRec0[2];
	int fSampleRate;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst7;
	float fConst8;
	float fRec1[2];
	int iRec2[2];
	float fVec0[2];
	float fRec3[2];
	float fConst9;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "lpf2.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "lpf2");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("wdmodels.lib/builddown:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/builddown:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/builddown:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/buildout:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/buildout:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/buildout:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/buildtree:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/buildtree:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/buildtree:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/capacitor:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/capacitor:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/capacitor:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/capacitor_Vout:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/capacitor_Vout:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/capacitor_Vout:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/getres:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/getres:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/getres:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/name", "Faust Wave Digital Model Library");
		m->declare("wdmodels.lib/parallel:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/parallel:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/parallel:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/parres:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/parres:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/parres:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/resistor:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/resistor:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/resistor:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/series:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/series:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/series:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/u_voltage:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/u_voltage:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/u_voltage:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/version", "0.2.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (3086419.75f / fConst0);
		fConst2 = (fConst1 + 1000.0f);
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / ((3.24000013e-07f * fConst0) + fConst3));
		fConst5 = (1.0f / (fConst4 + 1000.0f));
		float fConst6 = ((6172839.5f / fConst0) + 1000.0f);
		fConst7 = (1.0f / fConst6);
		fConst8 = (1000.0f / fConst6);
		fConst9 = (0.5f / fConst2);
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec2[l2] = 0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("lpf2");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = 0;
			float fTemp0 = (fConst2 * fRec1[1]);
			float fTemp1 = (float((-1 * iRec2[1])) - fRec3[1]);
			float fTemp2 = (fConst1 * fTemp1);
			float fTemp3 = (fTemp0 + fTemp2);
			float fTemp4 = (fConst5 * (((0.0f - (fConst4 * (((2.0f * float(input0[i])) + (fConst7 * fTemp3)) - float((-1 * iRec0[1]))))) + (0.0f - (fConst4 * float(iRec0[1])))) + (fConst8 * fTemp3)));
			fRec1[0] = (fTemp4 + (fConst7 * (fTemp2 + (0.0f - (fConst1 * fRec1[1])))));
			iRec2[0] = 0;
			float fTemp5 = (((0.0f - (fConst1 * (fTemp4 + (fConst7 * (fTemp0 + (0.0f - (fConst2 * fTemp1))))))) + (0.0f - (fConst1 * float(iRec2[1])))) + (1000.0f * fRec3[1]));
			fVec0[0] = fTemp5;
			fRec3[0] = (fConst3 * fTemp5);
			float fRec4 = (fConst9 * (fTemp5 + fVec0[1]));
			output0[i] = FAUSTFLOAT(fRec4);
			iRec0[1] = iRec0[0];
			fRec1[1] = fRec1[0];
			iRec2[1] = iRec2[0];
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#endif
