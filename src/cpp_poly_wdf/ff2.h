#pragma once

#include <chowdsp_wdf/chowdsp_wdf.h>
#include <memory>

namespace cpp_poly_wdf
{

/**
 * Feed-forward network two from the Klon Centaur overdrive pedal.
 * For more information, see: https://www.electrosmash.com/klon-centaur-analysis
 */ 
class FF2
{
    using Capacitor = chowdsp::wdf::Capacitor<float>;
    using Resistor = chowdsp::wdf::Resistor<float>;
    using ResVs = chowdsp::wdf::ResistiveVoltageSource<float>;
    using IdealVs = chowdsp::wdf::IdealVoltageSource<float>;
    using Series = chowdsp::wdf::WDFSeries<float>;
    using Parallel = chowdsp::wdf::WDFParallel<float>;
    using Inverter = chowdsp::wdf::PolarityInverter<float>;
public:
    FF2() = default;

    void reset(float sampleRate)
    {
        C4.prepare (sampleRate);
        C6.prepare (sampleRate);
        C11.prepare (sampleRate);
        C12.prepare (sampleRate);

        Vbias.setVoltage (4.5f);
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            Vin.setVoltage (x[i]);

            Vin.incident (I1.reflected());
            I1.incident (Vin.reflected());
            y[i] = R16.current();
        }
    }

private:
    ResVs Vbias;

    Resistor R5 { 5100.0 };
    Resistor R8 { 1500.0 };
    Resistor R9 { 1000.0 };
    Resistor RVTop { 50000.0 };
    Resistor RVBot { 50000.0 };
    Resistor R15 { 22000.0 };
    Resistor R16 { 47000.0 };
    Resistor R17 { 27000.0 };
    Resistor R18 { 12000.0 };

    Capacitor C4 { 68e-9f };
    Capacitor C6 { 390e-9f };
    Capacitor C11 { 2.2e-9f };
    Capacitor C12 { 27e-9f };

    Series S1 { &C12, &R18 };
    Parallel P1 { &S1, &R17 };
    Series S2 { &C11, &R15 };
    Series S3 { &S2, &R16 };

    Parallel P2 { &S3, &P1 };
    Parallel P3 { &P2, &RVBot};
    Series S4 { &P3, &RVTop };

    Series S5 { &C6, &R9};
    Parallel P4 { &S4, &S5 };
    Parallel P5 { &P4, &R8 };

    Series S6 { &P5, &Vbias };
    Parallel P6 { &R5, &C4 };
    Series S7 { &P6, &S6 };
    Inverter I1 { &S7 };

    IdealVs Vin { &I1 };
};

} // namespace cpp_poly_wdf
