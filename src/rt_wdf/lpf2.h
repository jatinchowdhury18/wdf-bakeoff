#pragma once

#include <rt-wdf/rt-wdf.h>

namespace rt_wdf {
class LPF2 : public wdfTree
{
public:
    LPF2(double sampleRate)
    {
        subtreeCount = 1;

        r1 = std::make_unique<wdfTerminatedRes> (10.0e3);
        r2 = std::make_unique<wdfTerminatedRes> (10.0e3);
        c1 = std::make_unique<wdfTerminatedCap> (1.0e-6, sampleRate);
        c2 = std::make_unique<wdfTerminatedCap> (1.0e-6, sampleRate);

        s1 = std::make_unique<wdfTerminatedSeries> (c1.get(), r1.get());
        p1 = std::make_unique<wdfTerminatedParallel> (c2.get(), s1.get());
        s2 = std::make_unique<wdfTerminatedSeries> (r2.get(), p1.get());

        vs = std::make_unique<wdfIdealVSource> (0.0);

        subtreeEntryNodes    = new wdfTreeNode*[subtreeCount];
        subtreeEntryNodes[0] = s2.get();

        root = std::make_unique<wdfRootSimple> (vs.get());

        initTree();
    }

    ~LPF2() override
    {
        delete[] subtreeEntryNodes;
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            setInputValue ((double) x[i]);
            cycleWave();
            y[i] = (float) getOutputValue();
        }
    }

    const char* getTreeIdentifier() override { return "lpf2"; }
    int setRootMatrData (matData* /*rootMats*/, double* /*Rp*/) override { return 0; }
    void setInputValue (double signalIn) override { vs->Vs = signalIn; }
    double getOutputValue() override { return c1->upPort->getPortVoltage(); }
    void setParam (size_t /*paramID*/, double /*paramValue*/) override {}

private:
    std::unique_ptr<wdfTerminatedRes> r1;
    std::unique_ptr<wdfTerminatedRes> r2;
    std::unique_ptr<wdfTerminatedCap> c1;
    std::unique_ptr<wdfTerminatedCap> c2;

    std::unique_ptr<wdfTerminatedSeries> s1;
    std::unique_ptr<wdfTerminatedParallel> p1;
    std::unique_ptr<wdfTerminatedSeries> s2;

    std::unique_ptr<wdfIdealVSource> vs;
};
}