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
    using RCSeries = chowdsp::wdf::ResistorCapacitorSeries<float>;
    using RCParallel = chowdsp::wdf::ResistorCapacitorParallel<float>;
    using ResVs = chowdsp::wdf::ResistiveVoltageSource<float>;
    using IdealVs = chowdsp::wdf::IdealVoltageSource<float>;
    using Series = chowdsp::wdf::WDFSeries<float>;
    using Parallel = chowdsp::wdf::WDFParallel<float>;
    using Inverter = chowdsp::wdf::PolarityInverter<float>;
public:
    FF2() = default;

    void reset(float sampleRate)
    {
        S1.prepare (sampleRate);
        S2.prepare (sampleRate);
        S5.prepare (sampleRate);
        P6.prepare (sampleRate);

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

    Resistor R8 { 1500.0 };
    Resistor RVTop { 50000.0 };
    Resistor RVBot { 50000.0 };
    Resistor R16 { 47000.0 };
    Resistor R17 { 27000.0 };

    RCSeries S1 { 12000.0f, 27.0e-9f };
    Parallel P1 { &S1, &R17 };
    RCSeries S2 { 22000.0f, 2.2e-9f };
    Series S3 { &S2, &R16 };

    Parallel P2 { &S3, &P1 };
    Parallel P3 { &P2, &RVBot};
    Series S4 { &P3, &RVTop };

    RCSeries S5 { 1000.0f, 390.0e-9f };
    Parallel P4 { &S4, &S5 };
    Parallel P5 { &P4, &R8 };

    Series S6 { &P5, &Vbias };
    RCParallel P6 { 5100.0f, 68.0e-9f };
    Series S7 { &P6, &S6 };
    Inverter I1 { &S7 };

    IdealVs Vin { &I1 };
};

} // namespace cpp_poly_wdf
