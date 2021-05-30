#pragma once

#include <wdf.h>
#include <memory>

namespace cpp_poly_wdf
{

using namespace chowdsp::WDF;

/**
 * A simple 2nd-order RC lowpass filter
 */ 
class LPF2
{
public:
    LPF2(float sampleRate)
    {
        c1 = std::make_unique<Capacitor<float>> (1.0e-6, sampleRate);
        c2 = std::make_unique<Capacitor<float>> (1.0e-6, sampleRate);

        s1 = std::make_unique<WDFSeries<float>> (c1.get(), &r1);
        p1 = std::make_unique<WDFParallel<float>> (c2.get(), s1.get());
        s2 = std::make_unique<WDFSeries<float>> (&r2, p1.get());
        i1 = std::make_unique<PolarityInverter<float>> (s2.get());

        vs.connectToNode (i1.get());
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            vs.setVoltage (x[i]);

            vs.incident (i1->reflected());
            i1->incident (vs.reflected());

            y[i] = c1->voltage();
        }
    }

private:
    Resistor<float> r1 { 10.0e3f };
    Resistor<float> r2 { 10.0e3f };
    std::unique_ptr<Capacitor<float>> c1;
    std::unique_ptr<Capacitor<float>> c2;

    std::unique_ptr<WDFSeries<float>> s1;
    std::unique_ptr<WDFParallel<float>> p1;
    std::unique_ptr<WDFSeries<float>> s2;

    std::unique_ptr<PolarityInverter<float>> i1;
    IdealVoltageSource<float> vs;
};

} // namespace cpp_poly_wdf
