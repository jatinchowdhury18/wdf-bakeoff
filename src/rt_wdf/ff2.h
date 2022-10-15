#pragma once

#include <rt-wdf/rt-wdf.h>

namespace rt_wdf {
    class FF2 : public wdfTree
    {
    public:
        FF2(double sampleRate)
        {
            subtreeCount = 1;

            Vbias = std::make_unique<wdfTerminatedResVSource>(4.5, 1.0);

            R5 = std::make_unique<wdfTerminatedRes> (5100.0);
            R8 = std::make_unique<wdfTerminatedRes> (1500.0);
            R9 = std::make_unique<wdfTerminatedRes> (1000.0);
            RVTop = std::make_unique<wdfTerminatedRes> (50000.0);
            RVBot = std::make_unique<wdfTerminatedRes> (50000.0);
            R15 = std::make_unique<wdfTerminatedRes> (22000.0);
            R16 = std::make_unique<wdfTerminatedRes> (47000.0);
            R17 = std::make_unique<wdfTerminatedRes> (27000.0);
            R18 = std::make_unique<wdfTerminatedRes> (12000.0);

            C4 = std::make_unique<wdfTerminatedCap> (68e-9, sampleRate);
            C6 = std::make_unique<wdfTerminatedCap> (390e-9, sampleRate);
            C11 = std::make_unique<wdfTerminatedCap> (2.2e-9, sampleRate);
            C12 = std::make_unique<wdfTerminatedCap> (27e-9, sampleRate);

            S1 = std::make_unique<wdfTerminatedSeries> (C12.get(), R18.get());
            P1 = std::make_unique<wdfTerminatedParallel> (S1.get(), R17.get());
            S2 = std::make_unique<wdfTerminatedSeries> (C11.get(), R15.get());
            S3 = std::make_unique<wdfTerminatedSeries> (S2.get(), R16.get());
            P2 = std::make_unique<wdfTerminatedParallel> (S3.get(), P1.get());
            P3 = std::make_unique<wdfTerminatedParallel> (P2.get(), RVBot.get());
            S4 = std::make_unique<wdfTerminatedSeries> (P3.get(), RVTop.get());
            S5 = std::make_unique<wdfTerminatedSeries> (C6.get(), R9.get());
            P4 = std::make_unique<wdfTerminatedParallel> (S4.get(), S5.get());
            P5 = std::make_unique<wdfTerminatedParallel> (P4.get(), R8.get());
            S6 = std::make_unique<wdfTerminatedSeries> (P5.get(), Vbias.get());
            P6 = std::make_unique<wdfTerminatedParallel> (R5.get(), C4.get());
            S7 = std::make_unique<wdfTerminatedSeries> (P6.get(), S6.get());
            I1 = std::make_unique<wdfInverter> (S7.get());

            vs = std::make_unique<wdfIdealVSource> (0.0);

            subtreeEntryNodes    = new wdfTreeNode*[subtreeCount];
            subtreeEntryNodes[0] = I1.get();

            root = std::make_unique<wdfRootSimple> (vs.get());

            initTree();
        }

        ~FF2() override
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
        double getOutputValue() override { return R16->upPort->getPortCurrent(); }
        void setParam (size_t /*paramID*/, double /*paramValue*/) override {}

    private:
        std::unique_ptr<wdfTerminatedResVSource> Vbias;

        std::unique_ptr<wdfTerminatedRes> R5;
        std::unique_ptr<wdfTerminatedRes> R8;
        std::unique_ptr<wdfTerminatedRes> R9;
        std::unique_ptr<wdfTerminatedRes> RVTop;
        std::unique_ptr<wdfTerminatedRes> RVBot;
        std::unique_ptr<wdfTerminatedRes> R15;
        std::unique_ptr<wdfTerminatedRes> R16;
        std::unique_ptr<wdfTerminatedRes> R17;
        std::unique_ptr<wdfTerminatedRes> R18;

        std::unique_ptr<wdfTerminatedCap> C4;
        std::unique_ptr<wdfTerminatedCap> C6;
        std::unique_ptr<wdfTerminatedCap> C11;
        std::unique_ptr<wdfTerminatedCap> C12;

        std::unique_ptr<wdfTerminatedSeries> S1;
        std::unique_ptr<wdfTerminatedSeries> S2;
        std::unique_ptr<wdfTerminatedSeries> S3;
        std::unique_ptr<wdfTerminatedSeries> S4;
        std::unique_ptr<wdfTerminatedSeries> S5;
        std::unique_ptr<wdfTerminatedSeries> S6;
        std::unique_ptr<wdfTerminatedSeries> S7;
        std::unique_ptr<wdfTerminatedParallel> P1;
        std::unique_ptr<wdfTerminatedParallel> P2;
        std::unique_ptr<wdfTerminatedParallel> P3;
        std::unique_ptr<wdfTerminatedParallel> P4;
        std::unique_ptr<wdfTerminatedParallel> P5;
        std::unique_ptr<wdfTerminatedParallel> P6;
        std::unique_ptr<wdfInverter> I1;

        std::unique_ptr<wdfIdealVSource> vs;
    };
}
