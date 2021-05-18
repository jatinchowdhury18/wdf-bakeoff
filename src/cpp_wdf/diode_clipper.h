#pragma once

#include <wdf.h>
#include <wdf_t.h>

namespace cpp_wdf
{

using namespace chowdsp::WDF;

/**
 * An RC diode clipper using an anti-parallel diode pair
 */ 
class DiodeClipper
{
public:
    DiodeClipper(float sampleRate) : C1 (47.0e-9f, sampleRate)
    {
        dp.connectToNode (&P1);
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
    ResistiveVoltageSource<float> Vs;
    Resistor<float> R1 { 4700.0f };
    Capacitor<float> C1;
    
    using S1Type = WDFSeriesT<float, ResistiveVoltageSource<float>, Resistor<float>>;
    S1Type S1 { Vs, R1 }; 

    using P1Type = WDFParallelT<float, S1Type, Capacitor<float>>;
    P1Type P1 { S1, C1 };

    // GZ34 diode pair
    DiodePair<float> dp { 2.52e-9f, 0.02585f };
};

} // namespace cpp_wdf
