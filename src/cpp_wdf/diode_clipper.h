#pragma once

#include <wdf_t.h>

namespace cpp_wdf
{

using namespace chowdsp::WDFT;

/**
 * An RC diode clipper using an anti-parallel diode pair
 */ 
class DiodeClipper
{
public:
    DiodeClipper(float sampleRate) : C1 (47.0e-9f, sampleRate)
    {
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            Vs.setVoltage (x[i]);

            dp.incident (P1.reflected());
            y[i] = voltage<float> (C1);
            P1.incident (dp.reflected());
        }
    }        

private:
    ResistiveVoltageSourceT<float> Vs { 4700.0f };
    CapacitorT<float> C1; 

    using P1Type = WDFParallelT<float, ResistiveVoltageSourceT<float>, CapacitorT<float>>;
    P1Type P1 { Vs, C1 };

    // GZ34 diode pair
    DiodePairT<float, P1Type> dp { 2.52e-9f, 0.02585f, P1 };
};

} // namespace cpp_wdf
