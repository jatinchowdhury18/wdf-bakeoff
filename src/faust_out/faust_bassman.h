/* ------------------------------------------------------------
name: "bassman"
Code generated with Faust 2.40.14 (https://faust.grame.fr)
Compilation options: -a faustMinimal.h -lang cpp -i -cn Bassman -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Bassman_H__
#define  __Bassman_H__

  
#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __UI_H__
#define __UI_H__

/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef __export__
#define __export__

#define FAUSTVERSION "2.40.14"

// Use FAUST_API for code that is part of the external API but is also compiled in faust and libfaust
// Use LIBFAUST_API for code that is compiled in faust and libfaust

#ifdef _WIN32
    #pragma warning (disable: 4251)
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #elif FAUST_LIB
        #define FAUST_API __declspec(dllexport)
        #define LIBFAUST_API __declspec(dllexport)
    #else
        #define FAUST_API
        #define LIBFAUST_API 
    #endif
#else
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #else
        #define FAUST_API __attribute__((visibility("default")))
        #define LIBFAUST_API __attribute__((visibility("default")))
    #endif
#endif

#endif

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
struct FAUST_API UIReal {
    
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

struct FAUST_API UI : public UIReal<FAUSTFLOAT> {
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __PathBuilder__
#define __PathBuilder__

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <regex>


/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class FAUST_API PathBuilder {

    protected:
    
        std::vector<std::string> fControlsLevel;
        std::vector<std::string> fFullPaths;
        std::map<std::string, std::string> fFull2Short;  // filled by computeShortNames()
    
        /**
         * @brief check if a character is acceptable for an ID
         *
         * @param c
         * @return true is the character is acceptable for an ID
         */
        bool isIDChar(char c) const
        {
            return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'));
        }
    
        /**
         * @brief remove all "/0x00" parts
         *
         * @param src
         * @return modified string
         */
        std::string remove0x00(const std::string& src) const
        {
            return std::regex_replace(src, std::regex("/0x00"), "");
        }
    
        /**
         * @brief replace all non ID char with '_' (one '_' may replace several non ID char)
         *
         * @param src
         * @return modified string
         */
        std::string str2ID(const std::string& src) const
        {
            std::string dst;
            bool need_underscore = false;
            for (char c : src) {
                if (isIDChar(c) || (c == '/')) {
                    if (need_underscore) {
                        dst.push_back('_');
                        need_underscore = false;
                    }
                    dst.push_back(c);
                } else {
                    need_underscore = true;
                }
            }
            return dst;
        }
    
        /**
         * @brief Keep only the last n slash-parts
         *
         * @param src
         * @param n : 1 indicates the last slash-part
         * @return modified string
         */
        std::string cut(const std::string& src, int n) const
        {
            std::string rdst;
            for (int i = int(src.length())-1; i >= 0; i--) {
                char c = src[i];
                if (c != '/') {
                    rdst.push_back(c);
                } else if (n == 1) {
                    std::string dst;
                    for (int j = int(rdst.length())-1; j >= 0; j--) {
                        dst.push_back(rdst[j]);
                    }
                    return dst;
                } else {
                    n--;
                    rdst.push_back(c);
                }
            }
            return src;
        }
    
        void addFullPath(const std::string& label) { fFullPaths.push_back(buildPath(label)); }
    
        /**
         * @brief Compute the mapping between full path and short names
         */
        void computeShortNames()
        {
            std::vector<std::string>           uniquePaths;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2full;  // all full paths transformed but made unique with a prefix
            char num_buffer[16];
            int pnum = 0;
        
            for (const auto& s : fFullPaths) {
                sprintf(num_buffer, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePaths.push_back(u);
                unique2full[u] = s;  // remember the full path associated to a unique path
            }
        
            std::map<std::string, int> uniquePath2level;                // map path to level
            for (const auto& s : uniquePaths) uniquePath2level[s] = 1;   // we init all levels to 1
            bool have_collisions = true;
        
            while (have_collisions) {
                // compute collision list
                std::set<std::string>              collisionSet;
                std::map<std::string, std::string> short2full;
                have_collisions = false;
                for (const auto& it : uniquePath2level) {
                    std::string u = it.first;
                    int n = it.second;
                    std::string shortName = cut(u, n);
                    auto p = short2full.find(shortName);
                    if (p == short2full.end()) {
                        // no collision
                        short2full[shortName] = u;
                    } else {
                        // we have a collision, add the two paths to the collision set
                        have_collisions = true;
                        collisionSet.insert(u);
                        collisionSet.insert(p->second);
                    }
                }
                for (const auto& s : collisionSet) uniquePath2level[s]++;  // increase level of colliding path
            }
        
            for (const auto& it : uniquePath2level) {
                std::string u = it.first;
                int n = it.second;
                std::string shortName = replaceCharList(cut(u, n), {'/'}, '_');
                fFull2Short[unique2full[u]] = shortName;
            }
        }
    
        std::string replaceCharList(const std::string& str, const std::vector<char>& ch1, char ch2)
        {
            auto beg = ch1.begin();
            auto end = ch1.end();
            std::string res = str;
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) res[i] = ch2;
            }
            return res;
        }
     
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        // Return true for the first level of groups
        bool pushLabel(const std::string& label) { fControlsLevel.push_back(label); return fControlsLevel.size() == 1;}
    
        // Return true for the last level of groups
        bool popLabel() { fControlsLevel.pop_back(); return fControlsLevel.size() == 0; }
    
        std::string buildPath(const std::string& label)
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res = res + fControlsLevel[i] + "/";
            }
            res += label;
            return replaceCharList(res, {' ', '#', '*', ',', '?', '[', ']', '{', '}', '(', ')'}, '_');
        }
    
};

#endif  // __PathBuilder__
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of unique 'shortname' (built so that they never collide) and zones
 * - a map of complete hierarchical 'paths' and zones for each UI item
 *
 * Simple 'labels', 'shortname' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class FAUST_API MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        // Shortname zone map
        std::map<std::string, FAUSTFLOAT*> fShortnameZoneMap;
    
        // Full path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        void addZoneLabel(const std::string& label, FAUSTFLOAT* zone)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fPathZoneMap[path] = zone;
            fLabelZoneMap[label] = zone;
        }
    
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
            if (popLabel()) {
                // Shortnames can be computed when all fullnames are known
                computeShortNames();
                // Fill 'shortname' map
                for (const auto& it : fFullPaths) {
                    fShortnameZoneMap[fFull2Short[it]] = fPathZoneMap[it];
                }
            }
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // setParamValue/getParamValue
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fShortnameZoneMap.find(path) != fShortnameZoneMap.end()) {
                *fShortnameZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fShortnameZoneMap.find(path) != fShortnameZoneMap.end()) {
                return *fShortnameZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", path.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getFullpathMap() { return fPathZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getShortnameMap() { return fShortnameZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getLabelMap() { return fLabelZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamShortname(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return "";
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamShortname1(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamLabel(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return "";
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamLabel1(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fShortnameZoneMap.find(str) != fShortnameZoneMap.end()) {
                return fShortnameZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
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
/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
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
struct FAUST_API Meta {
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
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

struct FAUST_API UI;
struct FAUST_API Meta;

/**
 * DSP memory manager.
 */

struct FAUST_API dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t count) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param size - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(size_t size, size_t reads, size_t writes) {}
    
    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class FAUST_API dsp {

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

class FAUST_API decorator_dsp : public dsp {

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

class FAUST_API dsp_factory {
    
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

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class FAUST_API ScopedNoDenormals {
    
    private:
    
        intptr_t fpsr;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
           asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            _mm_setcsr(static_cast<uint32_t>(fpsr_aux));
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined ( __SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #else
            #if defined(__SSE__)
            #if defined(__SSE2__)
                intptr_t mask = 0x8040;
            #else
                intptr_t mask = 0x8000;
            #endif
            #else
                intptr_t mask = 0x0000;
            #endif
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals();

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
#define FAUSTCLASS Bassman
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float Bassman_faustpower2_f(float value) {
	return value * value;
}

class Bassman : public dsp {
	
 private:
	
	float fRec0[2];
	int iRec1[2];
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	FAUSTFLOAT fHslider2;
	float fConst3;
	float fConst4;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	int iRec3[2];
	float fConst10;
	float fConst11;
	float fConst12;
	int iRec5[2];
	float fConst13;
	float fRec7[2];
	int iRec8[2];
	int iRec9[2];
	float fRec11[2];
	int iRec12[2];
	float fRec13[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.6");
		m->declare("compile_options", "-a faustMinimal.h -lang cpp -i -cn Bassman -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "bassman.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "bassman");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.2");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.1");
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
		m->declare("wdmodels.lib/version", "0.2.1");
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
		fConst1 = 3.99999998e-08f * fConst0;
		fConst2 = 2e+09f / fConst0;
		fConst3 = 1.60000003e-15f * fConst0;
		fConst4 = 2.8571429e-20f * fConst0;
		float fConst5 = Bassman_faustpower2_f(fConst0);
		fConst6 = 1.60000003e-15f * fConst5;
		fConst7 = 7.14285727e-13f * fConst0;
		fConst8 = fConst1 + fConst1 + 1.78571427e-05f;
		fConst9 = fConst3 + 7.14285727e-13f;
		fConst10 = -7.14285727e-13f - fConst3;
		fConst11 = 1.42857145e-12f * fConst0;
		fConst12 = 2.0f * fConst0;
		fConst13 = 2.8571429e-20f * fConst5;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec1[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec3[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iRec5[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec7[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec8[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec9[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec11[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iRec12[l8] = 0;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec13[l9] = 0.0f;
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
	
	virtual Bassman* clone() {
		return new Bassman();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("bassman");
		ui_interface->addHorizontalSlider("High", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("Low", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("Mid", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = 25000.0f * fSlow0;
		float fSlow2 = fSlow1 + 1.0f;
		float fSlow3 = 0.5f / fSlow2;
		float fSlow4 = 1000000.0f * float(fHslider1);
		float fSlow5 = 25000.0f * (1.0f - fSlow0);
		float fSlow6 = fSlow4 + fSlow5;
		float fSlow7 = fSlow2 * fSlow6;
		float fSlow8 = 1.0f / fSlow7;
		float fSlow9 = 0.0f - fSlow8;
		float fSlow10 = fConst1 * fSlow9 - 1.78571427e-05f / fSlow7 - fConst1 / fSlow7;
		float fSlow11 = float(fHslider2);
		float fSlow12 = 1.0f - fSlow11;
		float fSlow13 = fSlow11 + fSlow12;
		float fSlow14 = 250000.0f * fSlow13;
		float fSlow15 = fConst2 + fSlow14;
		float fSlow16 = fSlow10 / fSlow15;
		float fSlow17 = fConst3 / fSlow15;
		float fSlow18 = 7.14285727e-13f / fSlow15;
		float fSlow19 = fConst1 / fSlow15;
		float fSlow20 = fConst8 / fSlow6;
		float fSlow21 = fConst7 + fConst8 / fSlow15;
		float fSlow22 = (fConst6 + fConst7 + fSlow19 + fSlow20 + fSlow19 + 1.78571427e-05f / fSlow15) / fSlow2 + (fConst7 + fSlow21) / fSlow6 + fConst0 * (fConst4 + fConst9 / fSlow15);
		float fSlow23 = 2.0f * (fSlow2 * (fSlow16 + fConst0 * (0.0f - (1.42857145e-12f / fSlow6 + fSlow17) - fSlow18 - fConst4) / fSlow2)) / fSlow22 + 1.0f;
		float fSlow24 = 2.0f / fSlow22;
		float fSlow25 = fSlow21 / fSlow6;
		float fSlow26 = fConst6 + fSlow20;
		float fSlow27 = fSlow26 / fSlow15;
		float fSlow28 = 7.14285727e-13f / fSlow6;
		float fSlow29 = fSlow28 - fSlow17;
		float fSlow30 = fConst0 * fSlow29;
		float fSlow31 = fConst4 / fSlow2;
		float fSlow32 = fSlow2 * fSlow15;
		float fSlow33 = 1.0f / fSlow32;
		float fSlow34 = fConst0 * fSlow2 * (0.0f - (fSlow31 + 7.14285727e-13f * (fSlow33 - fSlow9 - fSlow8)));
		float fSlow35 = 7.14285727e-13f * fSlow9;
		float fSlow36 = fConst3 / fSlow32;
		float fSlow37 = 7.14285727e-13f / fSlow32;
		float fSlow38 = fSlow35 - fSlow36 - fSlow37 - fSlow31;
		float fSlow39 = fConst0 * fSlow2 * fSlow38;
		float fSlow40 = 0.5f / fSlow6;
		float fSlow41 = 2.0f * (fSlow6 * (fSlow16 + fConst0 * (fConst10 / fSlow2 - fSlow17 - fSlow18 - fConst4) / fSlow6)) / fSlow22 + 1.0f;
		float fSlow42 = 1.0f / fSlow22;
		float fSlow43 = fSlow21 / fSlow2;
		float fSlow44 = fConst7 / fSlow6;
		float fSlow45 = fSlow10 - fSlow44;
		float fSlow46 = (fSlow6 * fSlow45) / fSlow15;
		float fSlow47 = fSlow35 - fConst3 / fSlow7;
		float fSlow48 = fSlow6 * fSlow15;
		float fSlow49 = fConst3 / fSlow48;
		float fSlow50 = fConst4 / fSlow6;
		float fSlow51 = fSlow47 - fSlow49 - fSlow50;
		float fSlow52 = fConst0 * fSlow6 * fSlow51;
		float fSlow53 = 1.0f / fSlow15;
		float fSlow54 = fConst11 * (1.0f / fSlow2 - fSlow53);
		float fSlow55 = 7.14285727e-13f / fSlow48;
		float fSlow56 = 1.0f / fSlow48;
		float fSlow57 = 0.0f - (fSlow55 + fConst3 * (fSlow56 - fSlow9)) - fSlow50;
		float fSlow58 = fConst12 * fSlow6 * fSlow57;
		float fSlow59 = 2.0f * (fSlow10 - fConst7 / fSlow2 - fConst6 / fSlow2 - fSlow44 - fSlow44 - fConst13) / fSlow22 + 1.0f;
		float fSlow60 = fSlow26 / fSlow2;
		float fSlow61 = fConst4 + fSlow28 + fConst9 / fSlow2;
		float fSlow62 = fConst0 * fSlow61;
		float fSlow63 = fConst4 / fSlow15;
		float fSlow64 = fConst0 * fSlow15 * (0.0f - (fSlow63 + 7.14285727e-13f * (fSlow56 + fSlow56 - 0.0f - fSlow33)));
		float fSlow65 = fConst3 / fSlow2 - fSlow28;
		float fSlow66 = fConst0 * fSlow65;
		float fSlow67 = 0.5f / fSlow13;
		float fSlow68 = 250000.0f * fSlow11 / fSlow15;
		float fSlow69 = 250000.0f * fSlow11;
		float fSlow70 = 50000000.0f * (fSlow47 - fSlow37 - fSlow36 - fSlow55 - fSlow49 - fSlow50 - fSlow63) / fSlow22 + 1.0f;
		float fSlow71 = 50000000.0f / fSlow22;
		float fSlow72 = fSlow29 / fSlow2;
		float fSlow73 = fSlow61 / fSlow15;
		float fSlow74 = fSlow63 + 7.14285727e-13f * (fSlow56 + (1.0f / fSlow6 + fSlow53) / fSlow2);
		float fSlow75 = fConst0 * (0.0f - (2.8571429e-20f / fSlow6 + 1.60000003e-15f * (fSlow56 + fSlow33 - fSlow9)));
		float fSlow76 = fSlow65 / fSlow15;
		float fSlow77 = 7.14285727e-13f * (fSlow9 - fSlow33) - fSlow31 - fSlow55;
		float fSlow78 = 50000000.0f * (fConst3 * fSlow9 - 7.14285727e-13f / fSlow7 - fSlow36 - fSlow37 - fSlow31 - fSlow49 - fSlow55 - fSlow50) / fSlow22 + 1.0f;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = float(input0[i0]);
			iRec1[0] = 0;
			float fTemp0 = float(iRec1[1]);
			float fTemp1 = 0.0f - (fRec0[1] + fTemp0);
			float fTemp2 = float(0 - (iRec3[1] + iRec5[1]));
			float fTemp3 = float(0 - (iRec8[1] + iRec9[1]));
			float fTemp4 = 0.0f - (fRec7[1] + fTemp3);
			float fTemp5 = float(iRec12[1]);
			float fRec2 = fSlow3 * (fTemp0 + 0.0f - fSlow1 * (fSlow23 * fTemp1 + fSlow24 * (fSlow25 * fTemp2 + fSlow27 * fTemp4 + fSlow30 * fRec11[1] + fSlow34 * fTemp5 + fSlow39 * fRec13[1])) + 0.0f - fSlow1 * fRec0[1]);
			iRec3[0] = 0;
			float fTemp6 = fSlow41 * fTemp2 + fSlow42 * (2.0f * (fSlow43 * fTemp1 + fSlow46 * fTemp4 + fSlow52 * fRec11[1]) + fSlow54 * fTemp5 + fSlow58 * fRec13[1]);
			float fTemp7 = fSlow5 * float(iRec3[1]);
			float fTemp8 = fSlow4 * float(iRec5[1]);
			float fRec4 = fSlow40 * (0.0f - fSlow4 * fTemp6 + fTemp7 + 0.0f - fTemp8);
			iRec5[0] = 0;
			float fRec6 = fSlow40 * (fTemp8 + 0.0f - fSlow5 * fTemp6 + 0.0f - fTemp7);
			float fTemp9 = fSlow59 * fTemp4 + fSlow24 * (fSlow60 * fTemp1 + fSlow45 * fTemp2 + fSlow62 * fRec11[1] + fSlow64 * fTemp5 + fSlow66 * fRec13[1]);
			float fTemp10 = fSlow14 * fRec7[1];
			float fTemp11 = fConst2 * fTemp3;
			fRec7[0] = fSlow53 * (0.0f - fConst2 * fTemp9 + fTemp10 + 0.0f - fTemp11);
			iRec8[0] = 0;
			iRec9[0] = 0;
			float fRec10 = fSlow67 * (fSlow12 * float(iRec9[1]) + 3.99999999e-06f * (0.0f - fSlow68 * (fTemp11 + 0.0f - fSlow14 * fTemp9 + 0.0f - fTemp10) + 0.0f - fSlow69 * float(iRec8[1])));
			fRec11[0] = fSlow70 * fRec11[1] + fSlow71 * (fSlow72 * fTemp1 + fSlow51 * fTemp2 + fSlow73 * fTemp4 + fSlow74 * fTemp5 + fSlow75 * fRec13[1]);
			iRec12[0] = 0;
			fRec13[0] = fSlow71 * (fSlow38 * fTemp1 + fSlow57 * fTemp2 + fSlow76 * fTemp4 + fSlow75 * fRec11[1] + fSlow77 * fTemp5) + fSlow78 * fRec13[1];
			output0[i0] = FAUSTFLOAT(fRec2 + fRec4 + fRec6 + fRec10);
			fRec0[1] = fRec0[0];
			iRec1[1] = iRec1[0];
			iRec3[1] = iRec3[0];
			iRec5[1] = iRec5[0];
			fRec7[1] = fRec7[0];
			iRec8[1] = iRec8[0];
			iRec9[1] = iRec9[0];
			fRec11[1] = fRec11[0];
			iRec12[1] = iRec12[0];
			fRec13[1] = fRec13[0];
		}
	}

};

// END-FAUSTDSP

#endif
