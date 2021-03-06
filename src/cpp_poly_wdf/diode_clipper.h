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
    DiodeClipper() = default;

    void reset(float sampleRate)
    {
        C1 = std::make_unique<Capacitor<float>> (47.0e-9f, sampleRate);
        P1 = std::make_unique<WDFParallel<float>> (&Vs, C1.get());

        dp = std::make_unique<DiodePair<float>> (2.52e-9f, 0.02585f, P1.get());
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            Vs.setVoltage (x[i]);

            dp->incident (P1->reflected());
            y[i] = C1->voltage();
            P1->incident (dp->reflected());
        }
    }        

private:
    ResistiveVoltageSource<float> Vs { 4700.0f };
    std::unique_ptr<Capacitor<float>> C1;
    
    std::unique_ptr<WDFParallel<float>> P1;

    // GZ34 diode pair
    std::unique_ptr<DiodePair<float>> dp;
};

} // namespace cpp_poly_wdf
