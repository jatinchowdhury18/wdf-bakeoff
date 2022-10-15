#pragma once

#include <chowdsp_wdf/chowdsp_wdf.h>
#include <memory>

namespace cpp_poly_wdf
{

using namespace chowdsp::wdf;

/**
 * An RC diode clipper using an anti-parallel diode pair
 */ 
class DiodeClipper
{
public:
    DiodeClipper() = default;

    void reset(float sampleRate)
    {
        C1.prepare (sampleRate);
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            Vs.setVoltage (x[i]);

            dp.incident (P1.reflected());
            y[i] = C1.voltage();
            P1.incident (dp.reflected());
        }
    }        

private:
    ResistiveVoltageSource<float> Vs { 4700.0f };
    Capacitor<float> C1 { 47.0e-9f };
    
    WDFParallel<float> P1 { &Vs, &C1 };

    // GZ34 diode pair
    DiodePair<float> dp { &P1, 2.52e-9f, 0.02585f };
};

} // namespace cpp_poly_wdf
