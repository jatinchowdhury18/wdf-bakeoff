#pragma once

#include <chowdsp_wdf/chowdsp_wdf.h>
#include <memory>

namespace cpp_poly_wdf
{

using namespace chowdsp::wdf;

/**
 * A simple 2nd-order RC lowpass filter
 */ 
class LPF2
{
public:
    LPF2() = default;

    void reset(float sampleRate)
    {
        c1.prepare (sampleRate);
        c2.prepare (sampleRate);
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            vs.setVoltage (x[i]);

            vs.incident (i1.reflected());
            i1.incident (vs.reflected());

            y[i] = c1.voltage();
        }
    }

private:
    Resistor<float> r1 { 10.0e3f };
    Resistor<float> r2 { 10.0e3f };
    Capacitor<float> c1 { 1.0e6f};
    Capacitor<float> c2 { 1.0e-6f };

    WDFSeries<float> s1 { &c1, &r1 };
    WDFParallel<float> p1 { &c2, &s1 };
    WDFSeries<float> s2 { &r2, &p1 };

    PolarityInverter<float> i1 { &s2 };
    IdealVoltageSource<float> vs { &i1 };
};

} // namespace cpp_poly_wdf
