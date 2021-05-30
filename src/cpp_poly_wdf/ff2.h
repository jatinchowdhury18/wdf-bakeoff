#pragma once

#include <wdf.h>
#include <memory>

namespace cpp_poly_wdf
{

/**
 * Feed-forward network two from the Klon Centaur overdrive pedal.
 * For more information, see: https://www.electrosmash.com/klon-centaur-analysis
 */ 
class FF2
{
    using Capacitor = chowdsp::WDF::Capacitor<float>;
    using Resistor = chowdsp::WDF::Resistor<float>;
    using ResVs = chowdsp::WDF::ResistiveVoltageSource<float>;
    using IdealVs = chowdsp::WDF::IdealVoltageSource<float>;
    using Series = chowdsp::WDF::WDFSeries<float>;
    using Parallel = chowdsp::WDF::WDFParallel<float>;
    using Inverter = chowdsp::WDF::PolarityInverter<float>;
public:
    FF2() = default;

    void reset(float sampleRate)
    {
        C4 = std::make_unique<Capacitor> (68e-9, sampleRate);
        C6 = std::make_unique<Capacitor> (390e-9, sampleRate);
        C11 = std::make_unique<Capacitor> (2.2e-9, sampleRate);
        C12 = std::make_unique<Capacitor> (27e-9, sampleRate);

        S1 = std::make_unique<Series> (C12.get(), &R18);
        P1 = std::make_unique<Parallel> (S1.get(), &R17);
        S2 = std::make_unique<Series> (C11.get(), &R15);
        S3 = std::make_unique<Series> (S2.get(), &R16);

        P2 = std::make_unique<Parallel> (S3.get(), P1.get());
        P3 = std::make_unique<Parallel> (P2.get(), &RVBot);
        S4 = std::make_unique<Series> (P3.get(), &RVTop);

        S5 = std::make_unique<Series> (C6.get(), &R9);
        P4 = std::make_unique<Parallel> (S4.get(), S5.get());
        P5 = std::make_unique<Parallel> (P4.get(), &R8);

        S6 = std::make_unique<Series> (P5.get(), &Vbias);
        P6 = std::make_unique<Parallel> (&R5, C4.get());
        S7 = std::make_unique<Series> (P6.get(), S6.get());
        I1 = std::make_unique<Inverter> (S7.get());

        Vbias.setVoltage (4.5f);
        Vin.connectToNode (I1.get());
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            Vin.setVoltage (x[i]);

            Vin.incident (I1->reflected());
            I1->incident (Vin.reflected());
            y[i] = R16.current();
        }
    }

private:
    IdealVs Vin;
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

    std::unique_ptr<Capacitor> C4;
    std::unique_ptr<Capacitor> C6;
    std::unique_ptr<Capacitor> C11;
    std::unique_ptr<Capacitor> C12;

    std::unique_ptr<Series> S1;
    std::unique_ptr<Parallel> P1;
    std::unique_ptr<Series> S2;
    std::unique_ptr<Series> S3;

    std::unique_ptr<Parallel> P2;
    std::unique_ptr<Parallel> P3;
    std::unique_ptr<Series> S4;

    std::unique_ptr<Series> S5;
    std::unique_ptr<Parallel> P4;
    std::unique_ptr<Parallel> P5;

    std::unique_ptr<Series> S6;
    std::unique_ptr<Parallel> P6;
    std::unique_ptr<Series> S7;
    std::unique_ptr<Inverter> I1;
};

} // namespace cpp_poly_wdf
