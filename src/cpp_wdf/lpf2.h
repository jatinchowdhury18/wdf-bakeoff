#pragma once

#include <wdf_t.h>

namespace cpp_wdf
{

using namespace chowdsp::WDFT;

/**
 * A simple 2nd-order RC lowpass filter
 */ 
class LPF2
{
public:
    LPF2(float sampleRate) : c1 (1.0e-6f, sampleRate),
                             c2 (1.0e-6f, sampleRate)
    {
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            vs.setVoltage (x[i]);

            vs.incident (s1.reflected());
            s1.incident (vs.reflected());

            y[i] = voltage<float>(c1);
        }
    }

private:
    ResistorT<float> r1 { 10.0e3f };
    ResistorT<float> r2 { 10.0e3f };
    CapacitorT<float> c1;
    CapacitorT<float> c2;

    using S1Type = WDFSeriesT<float, CapacitorT<float>, ResistorT<float>>;
    S1Type s1 { c1, r1 };

    using P1Type = WDFParallelT<float, CapacitorT<float>, S1Type>;
    P1Type p1 { c2, s1 };

    using S2Type = WDFSeriesT<float, ResistorT<float>, P1Type>;
    S2Type s2 { r2, p1 };

    IdealVoltageSourceT<float, S2Type> vs { s2 };
};

} // namespace cpp_wdf
