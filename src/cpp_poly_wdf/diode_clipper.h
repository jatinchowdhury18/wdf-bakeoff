#pragma once

#include <wdf.h>
#include <memory>

namespace cpp_poly_wdf
{

using namespace chowdsp::WDF;

/**
 * An RC diode clipper using an anti-parallel diode pair
 */ 
class DiodeClipper
{
public:
    DiodeClipper(float sampleRate)
    {
        C1 = std::make_unique<Capacitor<float>> (47.0e-9f, sampleRate);
        P1 = std::make_unique<WDFParallel<float>> (&Vs, C1.get());

        dp.connectToNode (P1.get());
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            Vs.setVoltage (x[i]);

            dp.incident (P1->reflected());
            y[i] = C1->voltage();
            P1->incident (dp.reflected());
        }
    }        

private:
    ResistiveVoltageSource<float> Vs { 4700.0f };
    std::unique_ptr<Capacitor<float>> C1;
    
    std::unique_ptr<WDFParallel<float>> P1;

    // GZ34 diode pair
    DiodePair<float> dp { 2.52e-9f, 0.02585f };
};

} // namespace cpp_poly_wdf
