/* ------------------------------------------------------------
name: "ff2"
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
	float fConst6;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst19;
	float fConst20;
	float fConst22;
	float fConst23;
	float fConst25;
	float fConst27;
	float fConst28;
	float fConst30;
	float fConst32;
	float fConst34;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec1[2];
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec2[2];
	int iRec3[2];
	int iRec4[2];
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec6[2];
	int iRec7[2];
	int iRec8[2];
	int iRec9[2];
	int iRec10[2];
	float fConst53;
	float fRec11[2];
	int iRec12[2];
	int iRec13[2];
	float fRec14[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "ff2.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "ff2");
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
		m->declare("wdmodels.lib/resVoltage:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/resVoltage:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/resVoltage:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/resistor:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/resistor:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/resistor:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/resistor_Iout:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/resistor_Iout:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/resistor_Iout:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/series:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/series:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/series:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/u_voltage:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/u_voltage:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/u_voltage:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/version", "0.2.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / ((1.35999997e-07f * fConst0) + 0.000196078428f));
		fConst2 = (227272720.0f / fConst0);
		fConst3 = (fConst2 + 69000.0f);
		fConst4 = (18518518.0f / fConst0);
		fConst5 = (fConst4 + 12000.0f);
		fConst6 = (1.0f / fConst5);
		float fConst7 = ((1.0f / fConst3) + fConst6);
		float fConst8 = (fConst7 + 5.70370357e-05f);
		fConst9 = (1.0f / fConst8);
		fConst10 = (fConst9 + 50000.0f);
		fConst11 = (1.0f / fConst10);
		fConst12 = (1282051.25f / fConst0);
		fConst13 = (fConst12 + 1000.0f);
		fConst14 = (1.0f / fConst13);
		float fConst15 = (fConst11 + fConst14);
		float fConst16 = (fConst15 + 0.00066666666f);
		float fConst17 = (1.0f / fConst16);
		float fConst18 = ((fConst1 + fConst17) + 0.00100000005f);
		fConst19 = (1.0f / fConst18);
		fConst20 = (7352941.0f / fConst0);
		float fConst21 = (fConst20 + 5100.0f);
		fConst22 = (3.0f / fConst21);
		fConst23 = (1.0f / fConst15);
		float fConst24 = (fConst23 + 1500.0f);
		fConst25 = (1.0f / fConst24);
		float fConst26 = ((fConst9 + fConst12) + 51000.0f);
		fConst27 = (1500.0f / fConst26);
		fConst28 = (1.0f / (fConst7 + 3.70370362e-05f));
		float fConst29 = (fConst28 + 50000.0f);
		fConst30 = (1.0f / fConst29);
		float fConst31 = (fConst6 + 3.70370362e-05f);
		fConst32 = (1.0f / fConst31);
		float fConst33 = ((fConst2 + fConst32) + 69000.0f);
		fConst34 = (50000.0f / fConst33);
		float fConst35 = (fConst4 + 39000.0f);
		fConst36 = (fConst3 / fConst35);
		fConst37 = (fConst17 + 0.00100000005f);
		fConst38 = (1.0f / fConst21);
		fConst39 = (7352941.0f / (fConst0 * fConst24));
		fConst40 = (fConst2 + 22000.0f);
		fConst41 = (1.0f / fConst40);
		fConst42 = (227272720.0f / (fConst0 * fConst3));
		fConst43 = (1.0f / fConst37);
		fConst44 = (1.0f / (fConst16 * fConst18));
		fConst45 = (1.0f / (fConst16 * fConst26));
		fConst46 = (1.0f / fConst26);
		fConst47 = (fConst10 / fConst29);
		fConst48 = (1.0f / (fConst8 * fConst33));
		fConst49 = (1.0f / fConst33);
		fConst50 = (1.06382977e-05f / fConst3);
		fConst51 = (1.0f / (fConst31 * fConst35));
		fConst52 = (1.0f / fConst35);
		fConst53 = (fConst13 / fConst29);
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
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec3[l3] = 0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iRec4[l4] = 0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec7[l6] = 0;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iRec8[l7] = 0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec9[l8] = 0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iRec10[l9] = 0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec11[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			iRec12[l11] = 0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iRec13[l12] = 0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec14[l13] = 0.0f;
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
		ui_interface->openVerticalBox("ff2");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = 0;
			float fTemp0 = float(iRec0[1]);
			float fTemp1 = float(iRec3[1]);
			float fTemp2 = (0.0f - (fRec2[1] + fTemp1));
			float fTemp3 = float(iRec4[1]);
			float fTemp4 = (0.0f - (fTemp2 + fTemp3));
			float fTemp5 = float(iRec7[1]);
			float fTemp6 = (0.0f - (fRec6[1] + fTemp5));
			float fTemp7 = (fConst5 * float(iRec8[1]));
			float fTemp8 = ((27000.0f * fTemp6) + fTemp7);
			float fTemp9 = (fConst36 * fTemp8);
			float fTemp10 = ((fConst32 * fTemp4) + fTemp9);
			float fTemp11 = (fConst28 * float(iRec9[1]));
			float fTemp12 = ((fConst34 * fTemp10) + fTemp11);
			float fTemp13 = float(iRec10[1]);
			float fTemp14 = (0.0f - ((fConst30 * fTemp12) + fTemp13));
			float fTemp15 = float(iRec12[1]);
			float fTemp16 = (0.0f - (fRec11[1] + fTemp15));
			float fTemp17 = (fConst10 * fTemp16);
			float fTemp18 = ((fConst13 * fTemp14) + fTemp17);
			float fTemp19 = (fConst23 * float(iRec13[1]));
			float fTemp20 = ((fConst27 * fTemp18) + fTemp19);
			float fTemp21 = ((fConst25 * fTemp20) + fRec14[1]);
			float fTemp22 = ((fConst22 * ((fConst20 * fTemp0) + (5100.0f * fRec1[1]))) - fTemp21);
			float fTemp23 = (fConst37 * (0.0f - fTemp21));
			float fTemp24 = (fConst1 * fTemp0);
			fRec1[0] = ((fConst19 * (((0.0f - (fConst1 * fTemp22)) + fTemp23) + (0.0f - fTemp24))) + (fConst38 * ((fConst20 * fRec1[1]) + (0.0f - (fConst39 * fTemp20)))));
			float fTemp25 = ((fConst43 * (((0.0f - (fConst44 * (fTemp24 + ((0.0f - (fConst37 * fTemp22)) + (0.0f - fTemp23))))) + (0.00100000005f * fRec14[1])) + (0.0f - (fConst45 * fTemp18)))) + (fConst25 * ((0.0f - fTemp19) + (fConst23 * fTemp14))));
			float fTemp26 = ((fConst11 * (((0.0f - (fConst9 * (fTemp25 + (fConst46 * ((0.0f - fTemp17) + (fConst47 * fTemp12)))))) + (50000.0f * fTemp13)) + (0.0f - (fConst48 * fTemp10)))) + (fConst30 * ((0.0f - fTemp11) + (fConst28 * fTemp4))));
			float fTemp27 = (fTemp26 + (fConst49 * ((0.0f - fTemp9) + (fConst3 * fTemp2))));
			float fTemp28 = (47000.0f * fTemp3);
			float fTemp29 = (fConst40 * fRec2[1]);
			fRec2[0] = (fConst41 * (((0.0f - (fConst42 * (((0.0f - (fConst40 * fTemp27)) + fTemp28) + (0.0f - fTemp29)))) + (22000.0f * fTemp1)) + (0.0f - (fConst2 * fTemp6))));
			iRec3[0] = 0;
			iRec4[0] = 0;
			float fRec5 = (fConst50 * (fTemp29 + ((0.0f - (47000.0f * fTemp27)) + (0.0f - fTemp28))));
			fRec6[0] = (fConst6 * (((0.0f - (fConst4 * ((fTemp26 + (fConst49 * ((fConst51 * fTemp8) + (0.0f - (fConst32 * fTemp2))))) + (fConst52 * ((0.0f - fTemp7) + (fConst5 * fRec6[1])))))) + (12000.0f * fTemp5)) + (0.0f - (fConst4 * fRec11[1]))));
			iRec7[0] = 0;
			iRec8[0] = 0;
			iRec9[0] = 0;
			iRec10[0] = 0;
			fRec11[0] = (fConst14 * (((0.0f - (fConst12 * (fTemp25 + (fConst46 * ((fConst13 * fTemp16) + (0.0f - (fConst53 * fTemp12))))))) + (1000.0f * fTemp15)) + (0.0f - (fConst12 * float(input1[i])))));
			iRec12[0] = 0;
			iRec13[0] = 0;
			fRec14[0] = 4.5f;
			output0[i] = FAUSTFLOAT(fRec5);
			iRec0[1] = iRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			iRec4[1] = iRec4[0];
			fRec6[1] = fRec6[0];
			iRec7[1] = iRec7[0];
			iRec8[1] = iRec8[0];
			iRec9[1] = iRec9[0];
			iRec10[1] = iRec10[0];
			fRec11[1] = fRec11[0];
			iRec12[1] = iRec12[0];
			iRec13[1] = iRec13[0];
			fRec14[1] = fRec14[0];
		}
	}

};

#endif
