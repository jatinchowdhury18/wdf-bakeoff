/* ------------------------------------------------------------
name: "pultec"
Code generated with Faust 2.32.12 (https://faust.grame.fr)
Compilation options: -a faustMinimal.h -lang cpp -es 1 -vec -lv 0 -vs 32 -single -ftz 0 -mcd 16
------------------------------------------------------------ */

#ifndef  __Pultec_H__
#define  __Pultec_H__

  
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
    
    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
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
            for (const auto& it : fPathZoneMap) {
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
#define FAUSTCLASS Pultec
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Pultec : public dsp {
	
 private:
	
	int iRec0_perm[4];
	int iRec1_perm[4];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fConst2;
	FAUSTFLOAT fHslider7;
	float fRec2_perm[4];
	int iRec3_perm[4];
	int iRec4_perm[4];
	float fRec5_perm[4];
	int iRec6_perm[4];
	int iRec7_perm[4];
	int iRec8_perm[4];
	float fRec10_perm[4];
	int iRec11_perm[4];
	int iRec12_perm[4];
	float fRec13_perm[4];
	int iRec14_perm[4];
	int iRec15_perm[4];
	int iRec16_perm[4];
	float fRec17_perm[4];
	float fRec18_perm[4];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-a faustMinimal.h -lang cpp -es 1 -vec -lv 0 -vs 32 -single -ftz 0 -mcd 16");
		m->declare("filename", "pultec.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "pultec");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.2");
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
		m->declare("wdmodels.lib/inductor:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/inductor:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/inductor:license", "MIT-style STK-4.3 license");
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
		m->declare("wdmodels.lib/resistor_Vout:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/resistor_Vout:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/resistor_Vout:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/series:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/series:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/series:license", "MIT-style STK-4.3 license");
		m->declare("wdmodels.lib/u_genericNode:author", "Dirk Roosenburg");
		m->declare("wdmodels.lib/u_genericNode:copyright", "Copyright (C) 2020 by Dirk Roosenburg <dirk.roosenburg.30@gmail.com>");
		m->declare("wdmodels.lib/u_genericNode:license", "MIT-style STK-4.3 license");
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
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (2.0f * fConst0);
		fConst2 = (0.5f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iRec0_perm[l0] = 0;
		}
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			iRec1_perm[l1] = 0;
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec2_perm[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			iRec3_perm[l3] = 0;
		}
		for (int l4 = 0; (l4 < 4); l4 = (l4 + 1)) {
			iRec4_perm[l4] = 0;
		}
		for (int l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			fRec5_perm[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			iRec6_perm[l6] = 0;
		}
		for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) {
			iRec7_perm[l7] = 0;
		}
		for (int l8 = 0; (l8 < 4); l8 = (l8 + 1)) {
			iRec8_perm[l8] = 0;
		}
		for (int l9 = 0; (l9 < 4); l9 = (l9 + 1)) {
			fRec10_perm[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 4); l10 = (l10 + 1)) {
			iRec11_perm[l10] = 0;
		}
		for (int l11 = 0; (l11 < 4); l11 = (l11 + 1)) {
			iRec12_perm[l11] = 0;
		}
		for (int l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			fRec13_perm[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 4); l13 = (l13 + 1)) {
			iRec14_perm[l13] = 0;
		}
		for (int l14 = 0; (l14 < 4); l14 = (l14 + 1)) {
			iRec15_perm[l14] = 0;
		}
		for (int l15 = 0; (l15 < 4); l15 = (l15 + 1)) {
			iRec16_perm[l15] = 0;
		}
		for (int l16 = 0; (l16 < 4); l16 = (l16 + 1)) {
			fRec17_perm[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 4); l17 = (l17 + 1)) {
			fRec18_perm[l17] = 0.0f;
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
	
	virtual Pultec* clone() {
		return new Pultec();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("PULTEC PROGRAM EQUALIZER");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("LOW FREQUENCY");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("KNOBS");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("BOOST", &fHslider3, 0.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("ATTEN", &fHslider1, 0.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "menu{'20 Hz':0;'30 Hz':1;'60 Hz':2;'100 Hz':3}");
		ui_interface->addHorizontalSlider("CPS", &fHslider2, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("BANDWIDTH");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("ADJUST", &fHslider5, 0.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("HIGH FREQUENCY");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("KNOBS");
		ui_interface->declare(&fHslider4, "0", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("BOOST", &fHslider4, 0.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("ATTEN", &fHslider0, 0.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "style", "menu{'3 kHz':0;'4 kHz':1;'5 kHz':2;'6 kHz':3;'10 kHz':4;'12 kHz':5;'16 kHz':6}");
		ui_interface->addHorizontalSlider("CPS", &fHslider6, 0.0f, 0.0f, 6.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("ATTEN SELECT");
		ui_interface->declare(&fHslider7, "style", "menu{'20':0;'10':1;'5':2}");
		ui_interface->addHorizontalSlider("HI-CUT F", &fHslider7, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		int iRec0_tmp[36];
		int* iRec0 = &iRec0_tmp[4];
		int iRec1_tmp[36];
		int* iRec1 = &iRec1_tmp[4];
		float fZec0[32];
		float fSlow0 = (500.0f * std::log10((float(fHslider0) + 1.0f)));
		float fSlow1 = (10.0f * (std::pow(10.0f, (0.0199999996f * float(fHslider1))) + -1.0f));
		float fSlow2 = (fSlow1 + 1.0f);
		float fSlow3 = float(fHslider2);
		int iSlow4 = (fSlow3 >= 2.0f);
		int iSlow5 = (fSlow3 >= 1.0f);
		int iSlow6 = (fSlow3 >= 3.0f);
		float fSlow7 = (iSlow4 ? (iSlow6 ? 1.49999995e-08f : 2.2e-08f) : (iSlow5 ? 4.70000003e-08f : 1.00000001e-07f));
		float fSlow8 = ((1.0f / fSlow2) + (fConst1 * fSlow7));
		float fSlow9 = (1.0f / fSlow8);
		float fSlow10 = (fSlow0 + (fSlow9 + 1.0f));
		float fSlow11 = (1000.0f * (std::pow(10.0f, (0.0199999996f * float(fHslider3))) + -1.0f));
		float fSlow12 = (fSlow11 + 1.0f);
		float fSlow13 = (iSlow4 ? (iSlow6 ? 3.30000006e-07f : 4.70000003e-07f) : (iSlow5 ? 9.99999997e-07f : 2.19999993e-06f));
		float fSlow14 = ((1.0f / fSlow12) + (fConst1 * fSlow13));
		float fSlow15 = (1.0f / fSlow14);
		float fSlow16 = (1000.0f * (std::pow(10.0f, (0.0199999996f * float(fHslider4))) + -1.0f));
		float fSlow17 = (fSlow16 + 1.0f);
		float fSlow18 = (22.0f * (std::pow(10.0f, (0.0199999996f * float(fHslider5))) + -1.0f));
		float fSlow19 = float(fHslider6);
		int iSlow20 = (fSlow19 >= 4.0f);
		int iSlow21 = (fSlow19 >= 2.0f);
		int iSlow22 = (fSlow19 >= 6.0f);
		float fSlow23 = (iSlow20 ? (iSlow22 ? 0.0189999994f : ((fSlow19 >= 5.0f) ? 0.023f : 0.0350000001f)) : (iSlow21 ? ((fSlow19 >= 3.0f) ? 0.0649999976f : 0.0900000036f) : ((fSlow19 >= 1.0f) ? 0.100000001f : 0.174999997f)));
		float fSlow24 = (iSlow20 ? (iSlow22 ? 1.49999995e-08f : 6.80000012e-09f) : (iSlow21 ? 9.99999994e-09f : 1.49999995e-08f));
		float fSlow25 = (fConst2 / fSlow24);
		float fSlow26 = ((fConst1 * fSlow23) + fSlow25);
		float fSlow27 = (fSlow18 + (fSlow26 + 1.0f));
		float fSlow28 = ((1.0f / fSlow17) + (1.0f / fSlow27));
		float fSlow29 = (1.0f / fSlow28);
		float fSlow30 = (fSlow15 + fSlow29);
		float fSlow31 = ((fSlow30 + 100010.828f) - fSlow16);
		float fSlow32 = (1000.0f * fSlow31);
		float fSlow33 = (fSlow0 + 1.0f);
		float fSlow34 = float(fHslider7);
		float fSlow35 = ((fSlow34 >= 2.0f) ? 1.97000006e-07f : ((fSlow34 >= 1.0f) ? 9.40000007e-08f : 4.70000003e-08f));
		float fSlow36 = (fConst2 / fSlow35);
		float fSlow37 = (fSlow36 + 75.0f);
		float fSlow38 = ((1.0f / fSlow33) + (1.0f / fSlow37));
		float fSlow39 = (1.0f / fSlow38);
		float fSlow40 = ((fSlow39 + 1001.0f) - fSlow0);
		float fSlow41 = (fSlow15 + 1000.0f);
		float fSlow42 = (fSlow40 * fSlow41);
		float fSlow43 = (fSlow32 + fSlow42);
		float fSlow44 = ((fSlow29 + 100010.828f) - fSlow16);
		float fSlow45 = (fSlow44 / fSlow14);
		float fSlow46 = (10000.0f * fSlow31);
		float fSlow47 = (fSlow45 + fSlow46);
		float fSlow48 = ((fSlow29 + 110010.828f) - fSlow16);
		float fSlow49 = (1000.0f * fSlow48);
		float fSlow50 = (fSlow40 * (fSlow47 + fSlow49));
		float fSlow51 = (10000.0f * (fSlow15 + fSlow44));
		float fSlow52 = (fSlow15 + 11000.0f);
		float fSlow53 = (fSlow40 * fSlow52);
		float fSlow54 = (fSlow10 * ((fSlow51 + (fSlow53 + fSlow45)) + fSlow32));
		float fSlow55 = (1000.0f * fSlow47);
		float fSlow56 = (fSlow50 + (fSlow54 + fSlow55));
		float fSlow57 = (0.0f - (2.0f * ((fSlow10 * fSlow43) / fSlow56)));
		float fZec1[32];
		float fSlow58 = (fSlow1 + ((fConst2 / fSlow7) + 1.0f));
		float fZec2[32];
		float fZec3[32];
		float fSlow59 = ((fSlow55 + fSlow50) - fSlow54);
		float fZec4[32];
		float fZec5[32];
		float fZec6[32];
		float fSlow60 = (fSlow0 + (fSlow36 + 76.0f));
		float fZec7[32];
		float fZec8[32];
		float fSlow61 = (fSlow46 + (fSlow44 * fSlow41));
		float fZec9[32];
		float fSlow62 = (fSlow45 + (10000.0f * (fSlow40 + fSlow31)));
		float fZec10[32];
		float fZec11[32];
		float fSlow63 = (10000.0f * fSlow40);
		float fSlow64 = (fSlow63 - (1000.0f * fSlow44));
		float fSlow65 = (fSlow11 + ((fConst2 / fSlow13) + 1.0f));
		float fZec12[32];
		float fZec13[32];
		float fZec14[32];
		float fSlow66 = ((fSlow16 + fSlow18) + (fSlow25 + (2.0f * ((fConst0 * fSlow23) + 1.0f))));
		float fZec15[32];
		float fZec16[32];
		float fSlow67 = (fSlow53 + (1000.0f / fSlow14));
		float fSlow68 = (0.0f - (2.0f * ((fSlow10 * fSlow67) / fSlow56)));
		float fRec2_tmp[36];
		float* fRec2 = &fRec2_tmp[4];
		int iRec3_tmp[36];
		int* iRec3 = &iRec3_tmp[4];
		int iRec4_tmp[36];
		int* iRec4 = &iRec4_tmp[4];
		float fSlow69 = (0.0f - (2.0f * ((fSlow40 * (fSlow46 + ((fSlow10 + fSlow44) / fSlow14))) / fSlow56)));
		float fSlow70 = ((fSlow55 + (fSlow10 * ((fSlow32 + (fSlow51 + fSlow45)) - fSlow53))) - fSlow50);
		float fSlow71 = ((0.0f - (2.0f * fSlow10)) / fSlow14);
		float fSlow72 = (fSlow71 + (2000.0f * fSlow44));
		float fSlow73 = (11000.0f * fSlow10);
		float fSlow74 = (fSlow49 + fSlow73);
		float fSlow75 = ((fSlow10 * fSlow52) + 10000000.0f);
		float fSlow76 = (0.0f - (2.0f * ((fSlow40 * fSlow75) / fSlow56)));
		float fSlow77 = (1001.0f - fSlow0);
		float fRec5_tmp[36];
		float* fRec5 = &fRec5_tmp[4];
		int iRec6_tmp[36];
		int* iRec6 = &iRec6_tmp[4];
		int iRec7_tmp[36];
		int* iRec7 = &iRec7_tmp[4];
		int iRec8_tmp[36];
		int* iRec8 = &iRec8_tmp[4];
		float fSlow78 = (0.0f - (20000.0f * (fSlow43 / fSlow56)));
		float fSlow79 = ((10000.0f * fSlow71) + (20000000.0f * fSlow44));
		float fSlow80 = (fSlow0 + fSlow16);
		float fSlow81 = (fSlow10 * (((fSlow29 + (fSlow15 + fSlow39)) + 101011.828f) - fSlow80));
		float fSlow82 = (0.0f - (20000.0f * (((fSlow40 * fSlow44) + fSlow81) / fSlow56)));
		float fSlow83 = (1.0f - (20000.0f * (((fSlow32 + fSlow81) + (fSlow40 * ((fSlow30 + 101010.828f) - fSlow16))) / fSlow56)));
		float fSlow84 = ((fSlow39 + 2001.0f) - fSlow0);
		float fSlow85 = (fSlow39 + fSlow29);
		float fSlow86 = (fSlow10 * ((fSlow85 + 101011.828f) - fSlow80));
		float fSlow87 = ((fSlow44 * fSlow84) + fSlow86);
		float fSlow88 = (0.0f - (20000.0f * (fSlow87 / fSlow56)));
		float fSlow89 = (fSlow42 + ((fSlow0 + (fSlow9 + 1001.0f)) / fSlow14));
		float fSlow90 = (0.0f - (20000.0f * (fSlow89 / fSlow56)));
		float fRec9[32];
		float fSlow91 = (fSlow14 * fSlow56);
		float fSlow92 = (0.0f - (2.0f * ((fSlow86 + (fSlow40 * fSlow48)) / fSlow91)));
		float fSlow93 = (0.0f - (2.0f * (fSlow87 / fSlow91)));
		float fSlow94 = (fSlow73 + (10000.0f * fSlow84));
		float fSlow95 = (1.0f - (2.0f * (((fSlow48 * fSlow84) + (fSlow10 * ((fSlow85 + 112011.828f) - fSlow80))) / fSlow91)));
		float fRec10_tmp[36];
		float* fRec10 = &fRec10_tmp[4];
		int iRec11_tmp[36];
		int* iRec11 = &iRec11_tmp[4];
		int iRec12_tmp[36];
		int* iRec12 = &iRec12_tmp[4];
		float fRec13_tmp[36];
		float* fRec13 = &fRec13_tmp[4];
		int iRec14_tmp[36];
		int* iRec14 = &iRec14_tmp[4];
		int iRec15_tmp[36];
		int* iRec15 = &iRec15_tmp[4];
		int iRec16_tmp[36];
		int* iRec16 = &iRec16_tmp[4];
		float fSlow96 = (0.0f - (2.0f * ((fSlow44 * fSlow67) / fSlow56)));
		float fSlow97 = (0.0f - (2.0f * ((fSlow44 * fSlow75) / fSlow56)));
		float fSlow98 = (0.0f - (2.0f * ((fSlow44 * fSlow89) / fSlow56)));
		float fSlow99 = (fSlow63 - (fSlow10 / fSlow14));
		float fSlow100 = (1.0f - (2.0f * ((fSlow44 * ((1000.0f * (fSlow15 + 10000.0f)) + (fSlow52 * (fSlow10 + fSlow40)))) / fSlow56)));
		float fSlow101 = (100010.828f - fSlow16);
		float fSlow102 = (fSlow18 + 1.0f);
		float fZec17[32];
		float fZec18[32];
		float fZec19[32];
		float fRec17_tmp[36];
		float* fRec17 = &fRec17_tmp[4];
		float fSlow103 = (fSlow24 * fSlow27);
		float fRec18_tmp[36];
		float* fRec18 = &fRec18_tmp[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; (vindex <= (count - 32)); vindex = (vindex + 32)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				iRec0_tmp[j0] = iRec0_perm[j0];
			}
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				iRec1_tmp[j2] = iRec1_perm[j2];
			}
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				iRec3_tmp[j6] = iRec3_perm[j6];
			}
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				iRec4_tmp[j8] = iRec4_perm[j8];
			}
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				iRec6_tmp[j12] = iRec6_perm[j12];
			}
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				iRec7_tmp[j14] = iRec7_perm[j14];
			}
			for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
				iRec8_tmp[j16] = iRec8_perm[j16];
			}
			for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
				fRec10_tmp[j18] = fRec10_perm[j18];
			}
			for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
				iRec11_tmp[j20] = iRec11_perm[j20];
			}
			for (int j22 = 0; (j22 < 4); j22 = (j22 + 1)) {
				iRec12_tmp[j22] = iRec12_perm[j22];
			}
			for (int j24 = 0; (j24 < 4); j24 = (j24 + 1)) {
				fRec13_tmp[j24] = fRec13_perm[j24];
			}
			for (int j26 = 0; (j26 < 4); j26 = (j26 + 1)) {
				iRec14_tmp[j26] = iRec14_perm[j26];
			}
			for (int j28 = 0; (j28 < 4); j28 = (j28 + 1)) {
				iRec15_tmp[j28] = iRec15_perm[j28];
			}
			for (int j30 = 0; (j30 < 4); j30 = (j30 + 1)) {
				iRec16_tmp[j30] = iRec16_perm[j30];
			}
			for (int j32 = 0; (j32 < 4); j32 = (j32 + 1)) {
				fRec17_tmp[j32] = fRec17_perm[j32];
			}
			for (int j34 = 0; (j34 < 4); j34 = (j34 + 1)) {
				fRec18_tmp[j34] = fRec18_perm[j34];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iRec0[i] = 0;
				iRec1[i] = 0;
				fZec0[i] = float(iRec8[(i - 1)]);
				fZec1[i] = (fConst2 * (float(iRec1[(i - 1)]) / fSlow7));
				fZec2[i] = ((fZec1[i] + (fSlow2 * fRec2[(i - 1)])) / fSlow58);
				fZec3[i] = (float((-1 * iRec0[(i - 1)])) - fZec2[i]);
				fZec4[i] = (fSlow37 * float(iRec4[(i - 1)]));
				fZec5[i] = float(iRec6[(i - 1)]);
				fZec6[i] = (0.0f - (fRec5[(i - 1)] + fZec5[i]));
				fZec7[i] = ((fZec4[i] + (fSlow33 * fZec6[i])) / fSlow60);
				fZec8[i] = (float((-1 * iRec3[(i - 1)])) - fZec7[i]);
				fZec9[i] = float(iRec7[(i - 1)]);
				fZec10[i] = (fConst2 * (float(iRec11[(i - 1)]) / fSlow13));
				fZec11[i] = ((fSlow12 * fRec10[(i - 1)]) + fZec10[i]);
				fZec12[i] = (float((-1 * iRec12[(i - 1)])) - ((0.982758641f * fRec13[(i - 1)]) + (0.00172413792f * float((10 * iRec14[(i - 1)])))));
				fZec13[i] = (fSlow27 * float(iRec15[(i - 1)]));
				fZec14[i] = (fRec18[(i - 1)] + (float((-1 * iRec16[(i - 1)])) + fRec17[(i - 1)]));
				fZec15[i] = ((fZec13[i] + (fSlow17 * fZec14[i])) / fSlow66);
				fZec16[i] = (0.0f - (fZec12[i] + fZec15[i]));
				fRec2[i] = (((((0.0f - ((((fZec0[i] * fSlow57) + (((((fZec3[i] * fSlow59) + (2.0f * ((fSlow10 * fZec8[i]) * fSlow61))) + (2.0f * ((fSlow10 * fZec9[i]) * fSlow62))) + (2.0f * (((fSlow10 * fZec11[i]) * fSlow64) / fSlow65))) / fSlow56)) + (fZec16[i] * fSlow68)) / fSlow8)) + (0.0f - (float(iRec0[(i - 1)]) / fSlow8))) + (fSlow33 * fZec2[i])) / fSlow10) + ((fZec1[i] + (0.0f - (fConst2 * (fRec2[(i - 1)] / fSlow7)))) / fSlow58));
				iRec3[i] = 0;
				iRec4[i] = 0;
				fRec5[i] = ((((0.0f - (fConst2 * ((((((0.0f - ((((fZec9[i] * fSlow69) + (((((fZec8[i] * fSlow70) + (2.0f * ((fZec3[i] * fSlow40) * fSlow61))) + ((fSlow40 * fZec0[i]) * fSlow72)) + (2.0f * (((fSlow40 * fZec11[i]) * fSlow74) / fSlow65))) / fSlow56)) + (fZec16[i] * fSlow76)) / fSlow38)) + (0.0f - (float(iRec3[(i - 1)]) / fSlow38))) + (fSlow77 * fZec7[i])) / fSlow40) + ((fZec4[i] + (0.0f - (fSlow37 * fZec6[i]))) / fSlow60)) / fSlow35))) + (75.0f * fRec5[(i - 1)])) + (0.0f - (fConst2 * (fZec5[i] / fSlow35)))) / fSlow37);
				iRec6[i] = 0;
				iRec7[i] = 0;
				iRec8[i] = 0;
				fRec9[i] = (0.5f * ((((((fZec3[i] * fSlow78) + ((fZec8[i] * fSlow79) / fSlow56)) + (fZec9[i] * fSlow82)) + (fZec0[i] * fSlow83)) + ((fZec11[i] * fSlow88) / fSlow65)) + (fZec16[i] * fSlow90)));
				fRec10[i] = ((((fZec9[i] * fSlow92) + (fZec0[i] * fSlow93)) + (2.0f * ((((fZec3[i] * fSlow64) + (fZec8[i] * fSlow74)) + (fZec16[i] * fSlow94)) / fSlow91))) + ((fZec10[i] + ((fZec11[i] * fSlow95) + (0.0f - (fConst2 * (fRec10[(i - 1)] / fSlow13))))) / fSlow65));
				iRec11[i] = 0;
				iRec12[i] = 0;
				fRec13[i] = float(input0[i]);
				iRec14[i] = 0;
				iRec15[i] = 0;
				iRec16[i] = 0;
				fZec17[i] = (((0.0f - (fSlow26 * (((((0.0f - ((((((fZec3[i] * fSlow96) + (fZec8[i] * fSlow97)) + (fZec0[i] * fSlow98)) + (2.0f * ((fSlow44 * ((fZec9[i] * fSlow99) + ((fZec11[i] * fSlow94) / fSlow65))) / fSlow56))) + (fZec16[i] * fSlow100)) / fSlow28)) + (0.0f - (fZec12[i] / fSlow28))) + (fSlow101 * fZec15[i])) / fSlow44) + ((fZec13[i] + (0.0f - (fSlow27 * fZec14[i]))) / fSlow66)))) + (0.0f - (fSlow26 * float(iRec16[(i - 1)])))) + (fSlow102 * (0.0f - (fRec17[(i - 1)] + fRec18[(i - 1)]))));
				fZec18[i] = (fConst2 * (fRec17[(i - 1)] / fSlow24));
				fZec19[i] = (fConst1 * (fSlow23 * fRec18[(i - 1)]));
				fRec17[i] = (0.0f - ((((0.0f - (fConst1 * ((fSlow23 * fZec17[i]) / fSlow27))) + fZec18[i]) + (0.0f - fZec19[i])) / fSlow26));
				fRec18[i] = ((fZec19[i] + ((0.0f - (fConst2 * (fZec17[i] / fSlow103))) + (0.0f - fZec18[i]))) / fSlow26);
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				iRec0_perm[j1] = iRec0_tmp[(vsize + j1)];
			}
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				iRec1_perm[j3] = iRec1_tmp[(vsize + j3)];
			}
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec2_perm[j5] = fRec2_tmp[(vsize + j5)];
			}
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				iRec3_perm[j7] = iRec3_tmp[(vsize + j7)];
			}
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				iRec4_perm[j9] = iRec4_tmp[(vsize + j9)];
			}
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec5_perm[j11] = fRec5_tmp[(vsize + j11)];
			}
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				iRec6_perm[j13] = iRec6_tmp[(vsize + j13)];
			}
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				iRec7_perm[j15] = iRec7_tmp[(vsize + j15)];
			}
			for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
				iRec8_perm[j17] = iRec8_tmp[(vsize + j17)];
			}
			for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
				fRec10_perm[j19] = fRec10_tmp[(vsize + j19)];
			}
			for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
				iRec11_perm[j21] = iRec11_tmp[(vsize + j21)];
			}
			for (int j23 = 0; (j23 < 4); j23 = (j23 + 1)) {
				iRec12_perm[j23] = iRec12_tmp[(vsize + j23)];
			}
			for (int j25 = 0; (j25 < 4); j25 = (j25 + 1)) {
				fRec13_perm[j25] = fRec13_tmp[(vsize + j25)];
			}
			for (int j27 = 0; (j27 < 4); j27 = (j27 + 1)) {
				iRec14_perm[j27] = iRec14_tmp[(vsize + j27)];
			}
			for (int j29 = 0; (j29 < 4); j29 = (j29 + 1)) {
				iRec15_perm[j29] = iRec15_tmp[(vsize + j29)];
			}
			for (int j31 = 0; (j31 < 4); j31 = (j31 + 1)) {
				iRec16_perm[j31] = iRec16_tmp[(vsize + j31)];
			}
			for (int j33 = 0; (j33 < 4); j33 = (j33 + 1)) {
				fRec17_perm[j33] = fRec17_tmp[(vsize + j33)];
			}
			for (int j35 = 0; (j35 < 4); j35 = (j35 + 1)) {
				fRec18_perm[j35] = fRec18_tmp[(vsize + j35)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((200.0f * fRec9[i]));
			}
		}
		/* Remaining frames */
		if ((vindex < count)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = (count - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				iRec0_tmp[j0] = iRec0_perm[j0];
			}
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				iRec1_tmp[j2] = iRec1_perm[j2];
			}
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec2_tmp[j4] = fRec2_perm[j4];
			}
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				iRec3_tmp[j6] = iRec3_perm[j6];
			}
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				iRec4_tmp[j8] = iRec4_perm[j8];
			}
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec5_tmp[j10] = fRec5_perm[j10];
			}
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				iRec6_tmp[j12] = iRec6_perm[j12];
			}
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				iRec7_tmp[j14] = iRec7_perm[j14];
			}
			for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
				iRec8_tmp[j16] = iRec8_perm[j16];
			}
			for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
				fRec10_tmp[j18] = fRec10_perm[j18];
			}
			for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
				iRec11_tmp[j20] = iRec11_perm[j20];
			}
			for (int j22 = 0; (j22 < 4); j22 = (j22 + 1)) {
				iRec12_tmp[j22] = iRec12_perm[j22];
			}
			for (int j24 = 0; (j24 < 4); j24 = (j24 + 1)) {
				fRec13_tmp[j24] = fRec13_perm[j24];
			}
			for (int j26 = 0; (j26 < 4); j26 = (j26 + 1)) {
				iRec14_tmp[j26] = iRec14_perm[j26];
			}
			for (int j28 = 0; (j28 < 4); j28 = (j28 + 1)) {
				iRec15_tmp[j28] = iRec15_perm[j28];
			}
			for (int j30 = 0; (j30 < 4); j30 = (j30 + 1)) {
				iRec16_tmp[j30] = iRec16_perm[j30];
			}
			for (int j32 = 0; (j32 < 4); j32 = (j32 + 1)) {
				fRec17_tmp[j32] = fRec17_perm[j32];
			}
			for (int j34 = 0; (j34 < 4); j34 = (j34 + 1)) {
				fRec18_tmp[j34] = fRec18_perm[j34];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iRec0[i] = 0;
				iRec1[i] = 0;
				fZec0[i] = float(iRec8[(i - 1)]);
				fZec1[i] = (fConst2 * (float(iRec1[(i - 1)]) / fSlow7));
				fZec2[i] = ((fZec1[i] + (fSlow2 * fRec2[(i - 1)])) / fSlow58);
				fZec3[i] = (float((-1 * iRec0[(i - 1)])) - fZec2[i]);
				fZec4[i] = (fSlow37 * float(iRec4[(i - 1)]));
				fZec5[i] = float(iRec6[(i - 1)]);
				fZec6[i] = (0.0f - (fRec5[(i - 1)] + fZec5[i]));
				fZec7[i] = ((fZec4[i] + (fSlow33 * fZec6[i])) / fSlow60);
				fZec8[i] = (float((-1 * iRec3[(i - 1)])) - fZec7[i]);
				fZec9[i] = float(iRec7[(i - 1)]);
				fZec10[i] = (fConst2 * (float(iRec11[(i - 1)]) / fSlow13));
				fZec11[i] = ((fSlow12 * fRec10[(i - 1)]) + fZec10[i]);
				fZec12[i] = (float((-1 * iRec12[(i - 1)])) - ((0.982758641f * fRec13[(i - 1)]) + (0.00172413792f * float((10 * iRec14[(i - 1)])))));
				fZec13[i] = (fSlow27 * float(iRec15[(i - 1)]));
				fZec14[i] = (fRec18[(i - 1)] + (float((-1 * iRec16[(i - 1)])) + fRec17[(i - 1)]));
				fZec15[i] = ((fZec13[i] + (fSlow17 * fZec14[i])) / fSlow66);
				fZec16[i] = (0.0f - (fZec12[i] + fZec15[i]));
				fRec2[i] = (((((0.0f - ((((fZec0[i] * fSlow57) + (((((fZec3[i] * fSlow59) + (2.0f * ((fSlow10 * fZec8[i]) * fSlow61))) + (2.0f * ((fSlow10 * fZec9[i]) * fSlow62))) + (2.0f * (((fSlow10 * fZec11[i]) * fSlow64) / fSlow65))) / fSlow56)) + (fZec16[i] * fSlow68)) / fSlow8)) + (0.0f - (float(iRec0[(i - 1)]) / fSlow8))) + (fSlow33 * fZec2[i])) / fSlow10) + ((fZec1[i] + (0.0f - (fConst2 * (fRec2[(i - 1)] / fSlow7)))) / fSlow58));
				iRec3[i] = 0;
				iRec4[i] = 0;
				fRec5[i] = ((((0.0f - (fConst2 * ((((((0.0f - ((((fZec9[i] * fSlow69) + (((((fZec8[i] * fSlow70) + (2.0f * ((fZec3[i] * fSlow40) * fSlow61))) + ((fSlow40 * fZec0[i]) * fSlow72)) + (2.0f * (((fSlow40 * fZec11[i]) * fSlow74) / fSlow65))) / fSlow56)) + (fZec16[i] * fSlow76)) / fSlow38)) + (0.0f - (float(iRec3[(i - 1)]) / fSlow38))) + (fSlow77 * fZec7[i])) / fSlow40) + ((fZec4[i] + (0.0f - (fSlow37 * fZec6[i]))) / fSlow60)) / fSlow35))) + (75.0f * fRec5[(i - 1)])) + (0.0f - (fConst2 * (fZec5[i] / fSlow35)))) / fSlow37);
				iRec6[i] = 0;
				iRec7[i] = 0;
				iRec8[i] = 0;
				fRec9[i] = (0.5f * ((((((fZec3[i] * fSlow78) + ((fZec8[i] * fSlow79) / fSlow56)) + (fZec9[i] * fSlow82)) + (fZec0[i] * fSlow83)) + ((fZec11[i] * fSlow88) / fSlow65)) + (fZec16[i] * fSlow90)));
				fRec10[i] = ((((fZec9[i] * fSlow92) + (fZec0[i] * fSlow93)) + (2.0f * ((((fZec3[i] * fSlow64) + (fZec8[i] * fSlow74)) + (fZec16[i] * fSlow94)) / fSlow91))) + ((fZec10[i] + ((fZec11[i] * fSlow95) + (0.0f - (fConst2 * (fRec10[(i - 1)] / fSlow13))))) / fSlow65));
				iRec11[i] = 0;
				iRec12[i] = 0;
				fRec13[i] = float(input0[i]);
				iRec14[i] = 0;
				iRec15[i] = 0;
				iRec16[i] = 0;
				fZec17[i] = (((0.0f - (fSlow26 * (((((0.0f - ((((((fZec3[i] * fSlow96) + (fZec8[i] * fSlow97)) + (fZec0[i] * fSlow98)) + (2.0f * ((fSlow44 * ((fZec9[i] * fSlow99) + ((fZec11[i] * fSlow94) / fSlow65))) / fSlow56))) + (fZec16[i] * fSlow100)) / fSlow28)) + (0.0f - (fZec12[i] / fSlow28))) + (fSlow101 * fZec15[i])) / fSlow44) + ((fZec13[i] + (0.0f - (fSlow27 * fZec14[i]))) / fSlow66)))) + (0.0f - (fSlow26 * float(iRec16[(i - 1)])))) + (fSlow102 * (0.0f - (fRec17[(i - 1)] + fRec18[(i - 1)]))));
				fZec18[i] = (fConst2 * (fRec17[(i - 1)] / fSlow24));
				fZec19[i] = (fConst1 * (fSlow23 * fRec18[(i - 1)]));
				fRec17[i] = (0.0f - ((((0.0f - (fConst1 * ((fSlow23 * fZec17[i]) / fSlow27))) + fZec18[i]) + (0.0f - fZec19[i])) / fSlow26));
				fRec18[i] = ((fZec19[i] + ((0.0f - (fConst2 * (fZec17[i] / fSlow103))) + (0.0f - fZec18[i]))) / fSlow26);
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				iRec0_perm[j1] = iRec0_tmp[(vsize + j1)];
			}
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				iRec1_perm[j3] = iRec1_tmp[(vsize + j3)];
			}
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec2_perm[j5] = fRec2_tmp[(vsize + j5)];
			}
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				iRec3_perm[j7] = iRec3_tmp[(vsize + j7)];
			}
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				iRec4_perm[j9] = iRec4_tmp[(vsize + j9)];
			}
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec5_perm[j11] = fRec5_tmp[(vsize + j11)];
			}
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				iRec6_perm[j13] = iRec6_tmp[(vsize + j13)];
			}
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				iRec7_perm[j15] = iRec7_tmp[(vsize + j15)];
			}
			for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
				iRec8_perm[j17] = iRec8_tmp[(vsize + j17)];
			}
			for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
				fRec10_perm[j19] = fRec10_tmp[(vsize + j19)];
			}
			for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
				iRec11_perm[j21] = iRec11_tmp[(vsize + j21)];
			}
			for (int j23 = 0; (j23 < 4); j23 = (j23 + 1)) {
				iRec12_perm[j23] = iRec12_tmp[(vsize + j23)];
			}
			for (int j25 = 0; (j25 < 4); j25 = (j25 + 1)) {
				fRec13_perm[j25] = fRec13_tmp[(vsize + j25)];
			}
			for (int j27 = 0; (j27 < 4); j27 = (j27 + 1)) {
				iRec14_perm[j27] = iRec14_tmp[(vsize + j27)];
			}
			for (int j29 = 0; (j29 < 4); j29 = (j29 + 1)) {
				iRec15_perm[j29] = iRec15_tmp[(vsize + j29)];
			}
			for (int j31 = 0; (j31 < 4); j31 = (j31 + 1)) {
				iRec16_perm[j31] = iRec16_tmp[(vsize + j31)];
			}
			for (int j33 = 0; (j33 < 4); j33 = (j33 + 1)) {
				fRec17_perm[j33] = fRec17_tmp[(vsize + j33)];
			}
			for (int j35 = 0; (j35 < 4); j35 = (j35 + 1)) {
				fRec18_perm[j35] = fRec18_tmp[(vsize + j35)];
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((200.0f * fRec9[i]));
			}
		}
	}

};

// END-FAUSTDSP

#endif
