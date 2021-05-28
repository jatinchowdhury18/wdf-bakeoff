/* ------------------------------------------------------------
name: "ff2"
Code generated with Faust 2.32.6 (https://faust.grame.fr)
Compilation options: -a faustMinimal.h -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FF2_H__
#define  __FF2_H__

  
#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        std::string buildLabel(std::string label)
        {
            std::replace(label.begin(), label.end(), ' ', '_');
            return label;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        std::string fNullStr = "";
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        const std::string& getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return fNullStr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
    
        const std::string& getParamAddress(FAUSTFLOAT* zone)
        {
            for (auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return fNullStr;
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            }
            if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __meta__
#define __meta__

/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************** END dsp.h **************************/

// Borrowed from: https://github.com/Barabas5532/TubeScreamer/blob/master/faustMinimal.h

// BEGIN-FAUSTDSP


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS FF2
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class FF2 : public dsp {
	
 private:
	
	int iRec0[2];
	int fSampleRate;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst16;
	float fConst18;
	float fConst19;
	float fConst21;
	float fConst22;
	float fConst24;
	float fConst26;
	float fConst28;
	float fConst30;
	float fConst32;
	float fConst34;
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec1[2];
	float fConst39;
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
	float fRec11[2];
	int iRec12[2];
	int iRec13[2];
	float fRec14[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-a faustMinimal.h -lang cpp -es 1 -single -ftz 0");
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
		fConst1 = (1.0f / ((1.35999997e-07f * fConst0) + 0.000196078428f));
		fConst2 = (227272720.0f / fConst0);
		fConst3 = (fConst2 + 69000.0f);
		fConst4 = (18518518.0f / fConst0);
		fConst5 = (fConst4 + 12000.0f);
		fConst6 = (1.0f / fConst5);
		float fConst7 = ((1.0f / fConst3) + fConst6);
		fConst8 = (1.0f / (fConst7 + 5.70370357e-05f));
		fConst9 = (fConst8 + 50000.0f);
		fConst10 = (1.0f / fConst9);
		fConst11 = (1282051.25f / fConst0);
		fConst12 = (fConst11 + 1000.0f);
		fConst13 = (1.0f / fConst12);
		float fConst14 = (fConst10 + fConst13);
		float fConst15 = (fConst14 + 0.00066666666f);
		fConst16 = (1.0f / fConst15);
		float fConst17 = ((fConst1 + fConst16) + 0.00100000005f);
		fConst18 = (1.0f / fConst17);
		fConst19 = (7352941.0f / fConst0);
		float fConst20 = (fConst19 + 5100.0f);
		fConst21 = (1.0f / fConst20);
		fConst22 = (1.0f / fConst14);
		float fConst23 = (fConst22 + 1500.0f);
		fConst24 = (1.0f / fConst23);
		float fConst25 = ((fConst8 + fConst11) + 51000.0f);
		fConst26 = (1500.0f / fConst25);
		float fConst27 = (fConst7 + 3.70370362e-05f);
		fConst28 = (1.0f / fConst27);
		float fConst29 = (fConst28 + 50000.0f);
		fConst30 = (1.0f / fConst29);
		float fConst31 = (fConst6 + 3.70370362e-05f);
		fConst32 = (1.0f / fConst31);
		float fConst33 = ((fConst2 + fConst32) + 69000.0f);
		fConst34 = (50000.0f / fConst33);
		float fConst35 = (fConst4 + 39000.0f);
		fConst36 = (fConst3 / fConst35);
		fConst37 = (fConst16 + 0.00100000005f);
		fConst38 = (fConst37 / fConst20);
		fConst39 = (fConst2 + 22000.0f);
		fConst40 = (1.0f / fConst39);
		fConst41 = (227272720.0f / (fConst0 * fConst3));
		fConst42 = (1.0f / fConst37);
		fConst43 = (1.0f / (fConst15 * fConst17));
		fConst44 = (0.00100000005f / fConst23);
		fConst45 = (1.0f / (fConst14 * fConst25));
		fConst46 = (1.0f / fConst25);
		fConst47 = (50000.0f / fConst29);
		fConst48 = (1.0f / (fConst27 * fConst33));
		fConst49 = (1.0f / fConst33);
		fConst50 = (1.06382977e-05f / fConst3);
		fConst51 = (1.0f / (fConst31 * fConst35));
		fConst52 = (1.0f / fConst35);
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
	
	virtual FF2* clone() {
		return new FF2();
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
		FAUSTFLOAT* output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = 0;
			float fTemp0 = (fConst19 * float(iRec0[1]));
			float fTemp1 = (fTemp0 + (5100.0f * fRec1[1]));
			float fTemp2 = float(iRec3[1]);
			float fTemp3 = (0.0f - (fRec2[1] + fTemp2));
			float fTemp4 = float(iRec4[1]);
			float fTemp5 = (0.0f - (fTemp3 + fTemp4));
			float fTemp6 = (fConst32 * fTemp5);
			float fTemp7 = float(iRec7[1]);
			float fTemp8 = (0.0f - (fRec6[1] + fTemp7));
			float fTemp9 = (fConst5 * float(iRec8[1]));
			float fTemp10 = ((27000.0f * fTemp8) + fTemp9);
			float fTemp11 = (fConst36 * fTemp10);
			float fTemp12 = (fTemp6 + fTemp11);
			float fTemp13 = (fConst28 * float(iRec9[1]));
			float fTemp14 = ((fConst34 * fTemp12) + fTemp13);
			float fTemp15 = float(iRec10[1]);
			float fTemp16 = (0.0f - ((fConst30 * fTemp14) + fTemp15));
			float fTemp17 = (fConst12 * fTemp16);
			float fTemp18 = float(iRec12[1]);
			float fTemp19 = (0.0f - (fRec11[1] + fTemp18));
			float fTemp20 = (fConst9 * fTemp19);
			float fTemp21 = (fTemp17 + fTemp20);
			float fTemp22 = (fConst22 * float(iRec13[1]));
			float fTemp23 = ((fConst26 * fTemp21) + fTemp22);
			float fTemp24 = ((fConst24 * fTemp23) + fRec14[1]);
			float fTemp25 = (((2.0f * float(input0[i])) + (fConst21 * fTemp1)) - fTemp24);
			float fTemp26 = (fConst38 * fTemp1);
			float fTemp27 = (fConst1 * (0.0f - fTemp24));
			fRec1[0] = ((fConst18 * (((0.0f - (fConst1 * fTemp25)) + fTemp26) + (0.0f - fTemp27))) + (fConst21 * (fTemp0 + (0.0f - (fConst19 * fRec1[1])))));
			float fTemp28 = ((fConst42 * (((0.0f - (fConst43 * (fTemp27 + ((0.0f - (fConst37 * fTemp25)) + (0.0f - fTemp26))))) + (fConst44 * fTemp23)) + (0.0f - (fConst16 * fRec14[1])))) + (fConst24 * (fTemp22 + (0.0f - (fConst45 * fTemp21)))));
			float fTemp29 = ((fConst10 * (((0.0f - (fConst8 * (fTemp28 + (fConst46 * (fTemp20 + (0.0f - (fConst9 * fTemp16))))))) + (fConst47 * fTemp14)) + (0.0f - (fConst8 * fTemp15)))) + (fConst30 * (fTemp13 + (0.0f - (fConst48 * fTemp12)))));
			float fTemp30 = (fTemp29 + (fConst49 * (fTemp11 + (0.0f - (fConst3 * fTemp5)))));
			float fTemp31 = (47000.0f * fTemp3);
			float fTemp32 = (fConst39 * fTemp4);
			fRec2[0] = (fConst40 * (((0.0f - (fConst41 * (((0.0f - (fConst39 * fTemp30)) + fTemp31) + (0.0f - fTemp32)))) + (22000.0f * fRec2[1])) + (0.0f - (fConst2 * fTemp2))));
			iRec3[0] = 0;
			iRec4[0] = 0;
			float fRec5 = (fConst50 * (fTemp32 + ((0.0f - (47000.0f * fTemp30)) + (0.0f - fTemp31))));
			fRec6[0] = (fConst6 * (((0.0f - (fConst4 * ((fTemp29 + (fConst49 * (fTemp6 + (0.0f - (fConst51 * fTemp10))))) + (fConst52 * (fTemp9 + (0.0f - (fConst5 * fTemp8))))))) + (12000.0f * fRec6[1])) + (0.0f - (fConst4 * fTemp7))));
			iRec7[0] = 0;
			iRec8[0] = 0;
			iRec9[0] = 0;
			iRec10[0] = 0;
			fRec11[0] = (fConst13 * (((0.0f - (fConst11 * (fTemp28 + (fConst46 * (fTemp17 + (0.0f - (fConst12 * fTemp19))))))) + (1000.0f * fRec11[1])) + (0.0f - (fConst11 * fTemp18))));
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

// END-FAUSTDSP

#endif
