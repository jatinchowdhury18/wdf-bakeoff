#pragma once

#include <chowdsp_wdf/chowdsp_wdf.h>

namespace cpp_wdf
{

/**
 * Feed-forward network two from the Klon Centaur overdrive pedal.
 * For more information, see: https://www.electrosmash.com/klon-centaur-analysis
 */
class FF2
{
public:
    FF2(float sampleRate)
        : S1 (12000.0f, 27.0e-9f, sampleRate),
          S2 (22000.0f, 2.2e-9f, sampleRate),
          S5 (1000.0f, 390.0e-9f, sampleRate),
          P6 (5100.0f, 68.0e-9f, sampleRate)
    {
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
            y[i] = chowdsp::wdft::current<float> (R16);
        }
    }

private:
    using Capacitor = chowdsp::wdft::CapacitorT<float>;
    using Resistor = chowdsp::wdft::ResistorT<float>;
    using ResVs = chowdsp::wdft::ResistiveVoltageSourceT<float>;

    ResVs Vbias;
    Resistor R8 { 1500.0 };
    Resistor RVTop { 50000.0 };
    Resistor RVBot { 50000.0 };
    Resistor R16 { 47000.0 };
    Resistor R17 { 27000.0 };

    chowdsp::wdft::ResistorCapacitorSeriesT<float> S1;

    using P1Type = chowdsp::wdft::WDFParallelT<float, decltype (S1), Resistor>;
    P1Type P1 { S1, R17 };

    chowdsp::wdft::ResistorCapacitorSeriesT<float> S2;

    using S3Type = chowdsp::wdft::WDFSeriesT<float, decltype (S2), Resistor>;
    S3Type S3 { S2, R16 };

    using P2Type = chowdsp::wdft::WDFParallelT<float, S3Type, P1Type>;
    P2Type P2 { S3, P1 };

    using P3Type = chowdsp::wdft::WDFParallelT<float, P2Type, Resistor>;
    P3Type P3 { P2, RVBot };

    using S4Type = chowdsp::wdft::WDFSeriesT<float, P3Type, Resistor>;
    S4Type S4 { P3, RVTop };

    chowdsp::wdft::ResistorCapacitorSeriesT<float> S5;

    using P4Type = chowdsp::wdft::WDFParallelT<float, S4Type, decltype (S5)>;
    P4Type P4 { S4, S5 };

    using P5Type = chowdsp::wdft::WDFParallelT<float, P4Type, Resistor>;
    P5Type P5 { P4, R8 };

    using S6Type = chowdsp::wdft::WDFSeriesT<float, P5Type, ResVs>;
    S6Type S6 { P5, Vbias };

    chowdsp::wdft::ResistorCapacitorParallelT<float> P6;

    using S7Type = chowdsp::wdft::WDFSeriesT<float, decltype (P6), S6Type>;
    S7Type S7 { P6, S6 };

    using I1Type = chowdsp::wdft::PolarityInverterT<float, S7Type>;
    I1Type I1 { S7 };

    chowdsp::wdft::IdealVoltageSourceT<float, I1Type> Vin { I1 };
};

} // namespace cpp_wdf
