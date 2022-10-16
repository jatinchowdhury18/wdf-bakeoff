#pragma once

#include <rt-wdf/rt-wdf.h>

namespace rt_wdf {
    class Bassman : public wdfTree
    {
    public:
        Bassman(double sampleRate)
        {
            subtreeCount = 6;

            Res1p = std::make_unique<wdfTerminatedRes> (125.0e3);
            Res1m = std::make_unique<wdfTerminatedRes> (125.0e3);
            Res2 = std::make_unique<wdfTerminatedRes> (500.0e3);
            Res3p = std::make_unique<wdfTerminatedRes> (12.0e3);
            Res3m = std::make_unique<wdfTerminatedRes> (13.0e3);
            Res4 = std::make_unique<wdfTerminatedRes> (56.0e3);

            Cap1 = std::make_unique<wdfTerminatedCap> (250.0e-12, sampleRate);
            Cap2 = std::make_unique<wdfTerminatedCap> (20.0e-9, sampleRate);
            Cap3 = std::make_unique<wdfTerminatedCap> (20.0e-9, sampleRate);

            Vres = std::make_unique<wdfTerminatedResVSource> (0.0, 1.0);

            // Port A
            S1 = std::make_unique<wdfTerminatedSeries> (Vres.get(), Res3m.get());

            // Port B
            S3 = std::make_unique<wdfTerminatedSeries> (Res2.get(), Res3p.get());

            // Port C
            S4 = std::make_unique<wdfTerminatedSeries> (Res1p.get(), Res1m.get());
            S2 = std::make_unique<wdfTerminatedSeries> (Cap1.get(), S4.get());

            subtreeEntryNodes    = new wdfTreeNode*[subtreeCount];
            subtreeEntryNodes[0] = S1.get();
            subtreeEntryNodes[1] = S3.get();
            subtreeEntryNodes[2] = S2.get();
            subtreeEntryNodes[3] = Cap2.get();
            subtreeEntryNodes[4] = Res4.get();
            subtreeEntryNodes[5] = Cap3.get();

            root = std::make_unique<wdfRootRtype> (subtreeCount);
            Rp = new double[subtreeCount]();

            initTree();
        }

        ~Bassman() override
        {
            delete[] subtreeEntryNodes;
            delete[] Rp;
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

        const char* getTreeIdentifier() override { return "bassman"; }
        void setInputValue (double signalIn) override { Vres->Vs = signalIn; }
        double getOutputValue() override { return Res1m->upPort->getPortVoltage() + S2->upPort->getPortVoltage() + Res3m->upPort->getPortVoltage(); }
        void setParam (size_t /*paramID*/, double /*paramValue*/) override {}

        int setRootMatrData (matData* rootMats, double* Rp) override
        {
            const auto Ra = Rp[0];
            const auto Rb = Rp[1];
            const auto Rc = Rp[2];
            const auto Rd = Rp[3];
            const auto Re = Rp[4];
            const auto Rf = Rp[5];
            const auto Ga = 1.0 / Ra;
            const auto Gb = 1.0 / Rb;
            const auto Gc = 1.0 / Rc;
            const auto Gd = 1.0 / Rd;
            const auto Ge = 1.0 / Re;
            const auto Gf = 1.0 / Rf;

            // clang-format off
            double arr[6][6] = { { 2 * Ra * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Ra * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gb * Gd * Ge) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (Ga * Gb * Gd * Ge - Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (-Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (-Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                 { 2 * Rb * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gb * Gd * Ge) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Rb * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (-Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (Ga * Gb * Gd * Ge - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (-Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                 { 2 * Rc * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Ga * Gc * Gd * Ge - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Rc * (Ga * Gc * Gd * Ge + Ga * Gc * Gd * Gf + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (-Ga * Gc * Gd * Ge - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (Ga * Gc * Gd * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                 { 2 * Rd * (Ga * Gb * Gd * Ge - Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (-Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (Ga * Gc * Gd * Ge + Ga * Gc * Gd * Gf + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (-Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Ga * Gc * Gd * Ge - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Ge - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Rd * (Ga * Gb * Gd * Ge + Ga * Gc * Gd * Ge + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (-Ga * Gb * Gd * Gf - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                 { 2 * Re * (-Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (Ga * Gb * Gd * Ge - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (-Ga * Gc * Gd * Ge - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (Ga * Gb * Gd * Ge + Ga * Gc * Gd * Ge + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (-Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Gd * Ge - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Re * (-Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                 { 2 * Rf * (-Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (Ga * Gc * Gd * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Gd * Gf - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Gd * Gf - Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1 } };
            // clang-format on

            for ( unsigned int ii = 0; ii < 6; ++ii )
                for ( unsigned int jj = 0; jj < 6; ++jj )
                    rootMats->Smat.at(ii, jj) = arr[ii][jj];

            return 0;
        }

    private:
        std::unique_ptr<wdfTerminatedRes> Res1p;
        std::unique_ptr<wdfTerminatedRes> Res1m;
        std::unique_ptr<wdfTerminatedRes> Res2;
        std::unique_ptr<wdfTerminatedRes> Res3p;
        std::unique_ptr<wdfTerminatedRes> Res3m;
        std::unique_ptr<wdfTerminatedRes> Res4;

        std::unique_ptr<wdfTerminatedCap> Cap1;
        std::unique_ptr<wdfTerminatedCap> Cap2;
        std::unique_ptr<wdfTerminatedCap> Cap3;

        std::unique_ptr<wdfTerminatedResVSource> Vres;

        std::unique_ptr<wdfTerminatedSeries> S1;
        std::unique_ptr<wdfTerminatedSeries> S2;
        std::unique_ptr<wdfTerminatedSeries> S3;
        std::unique_ptr<wdfTerminatedSeries> S4;
    };
}
