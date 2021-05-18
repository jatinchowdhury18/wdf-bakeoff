#pragma once

#include <wdf.h>
#include <wdf_t.h>

namespace cpp_wdf
{

using namespace chowdsp::WDF;

class LPF2
{
public:
    LPF2(float sampleRate) : c1 (1.0e-6, sampleRate),
                             c2 (1.0e-6, sampleRate)
    {
        vs.connectToNode (&i1);
    }

    void process (float* data, int numSamples)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            vs.setVoltage (data[i]);

            vs.incident (i1.reflected());
            i1.incident (vs.reflected());

            data[i] = c1.voltage();
        }
    }

private:
    Resistor<float> r1 { 10.0e3f };
    Resistor<float> r2 { 10.0e3f };
    Capacitor<float> c1;
    Capacitor<float> c2;

    using S1Type = WDFSeriesT<float, Capacitor<float>, Resistor<float>>;
    S1Type s1 { c1, r1 };

    using P1Type = WDFParallelT<float, Capacitor<float>, S1Type>;
    P1Type p1 { c2, s1 };

    using S2Type = WDFSeriesT<float, Resistor<float>, P1Type>;
    S2Type s2 { r2, p1 };

    PolarityInverterT<float, S2Type> i1 { s2 };
    IdealVoltageSource<float> vs;
};

} // namespace cpp_wdf
