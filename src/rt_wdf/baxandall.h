#pragma once

#include <rt-wdf/rt-wdf.h>

namespace rt_wdf {
    class wdfTerminatedRtype_Baxandall : public wdfTerminatedRtype
    {

    public:
        //----------------------------------------------------------------------
        wdfTerminatedRtype_Baxandall ( wdfTreeNode* left,
                                 wdfTreeNode *right ) : wdfTerminatedRtype( {left, right} ) {

        }

        //----------------------------------------------------------------------
        double calculateUpRes( double T )
        {
            const double Rleft  = downPorts[0]->Rp;
            const double Rright = downPorts[1]->Rp;
            const double Rup    = Rleft + Rright;
            return ( Rup );
        }

        //----------------------------------------------------------------------
        void calculateScatterCoeffs( )
        {
            const double Ru = upPort->Rp;
            const double Rl = downPorts[0]->Rp;
            const double Rr = downPorts[1]->Rp;

            const double yu = 1.0;
            const double yl = 2.0 * Rl / ( Ru + Rl + Rr );
            const double yr = 1.0 - yl;

            S->at(0,0) = 1-yu;
            S->at(0,1) =  -yu;
            S->at(0,2) =  -yu;

            S->at(1,0) =  -yl;
            S->at(1,1) = 1-yl;
            S->at(1,2) =  -yl;

            S->at(2,0) =  -yr;
            S->at(2,1) =  -yr;
            S->at(2,2) = 1-yr;


            for( wdfPort* downPort : downPorts ) {
                downPort->connectedNode->calculateScatterCoeffs( );
            }
        }
    };

    class Baxandall : public wdfTree
    {
    public:
        Baxandall(double sampleRate)
        {
            subtreeCount = 6;

            // Port A
            Pt_plus = std::make_unique<wdfTerminatedRes> (50.0e3);
            Resd = std::make_unique<wdfTerminatedRes> (10.0e3);
            P4 = std::make_unique<wdfTerminatedParallel> (Pt_plus.get(), Resd.get());
            Cd = std::make_unique<wdfTerminatedCap> (6.4e-9, sampleRate);
            S4 = std::make_unique<wdfTerminatedSeries> (Cd.get(), P4.get());

            // Port B
            Pt_minus = std::make_unique<wdfTerminatedRes> (50.0e3);
            Rese = std::make_unique<wdfTerminatedRes> (1.0e3);
            P5 = std::make_unique<wdfTerminatedParallel> (Pt_minus.get(), Rese.get());
            Ce = std::make_unique<wdfTerminatedCap> (64.0e-9, sampleRate);
            S5 = std::make_unique<wdfTerminatedSeries> (Ce.get(), P5.get());
            Rl = std::make_unique<wdfTerminatedRes> (1.0e6);
            P1 = std::make_unique<wdfTerminatedParallel> (Rl.get(), S5.get());

            // Port C
            Resc = std::make_unique<wdfTerminatedRes> (10.0e3);

            // Port D
            Pb_minus = std::make_unique<wdfTerminatedRes> (50.0e3);
            Cc = std::make_unique<wdfTerminatedCap> (220.0e-9, sampleRate);
            P3 = std::make_unique<wdfTerminatedParallel> (Pb_minus.get(), Cc.get());
            Resb = std::make_unique<wdfTerminatedRes> (1.0e3);
            S3 = std::make_unique<wdfTerminatedSeries> (Resb.get(), P3.get());

            // Port E
            Pb_plus = std::make_unique<wdfTerminatedRes> (50.0e3);
            Cb = std::make_unique<wdfTerminatedCap> (22.0e-9, sampleRate);
            P2 = std::make_unique<wdfTerminatedParallel> (Pb_plus.get(), Cb.get());
            Resa = std::make_unique<wdfTerminatedRes> (10.0e3);
            S2 = std::make_unique<wdfTerminatedSeries> (Resa.get(), P2.get());

            // Port F
            Vin = std::make_unique<wdfTerminatedResVSource> (0.0, 1.0);
            Ca = std::make_unique<wdfTerminatedCap> (1.0e-6, sampleRate);
            S1 = std::make_unique<wdfTerminatedSeries> (Vin.get(), Ca.get());

            subtreeEntryNodes    = new wdfTreeNode*[subtreeCount];
            subtreeEntryNodes[0] = S4.get();
            subtreeEntryNodes[1] = P1.get();
            subtreeEntryNodes[2] = Resc.get();
            subtreeEntryNodes[3] = S3.get();
            subtreeEntryNodes[4] = S2.get();
            subtreeEntryNodes[5] = S1.get();

            root = std::make_unique<wdfRootRtype> (subtreeCount);
            Rp = new double[subtreeCount]();

            initTree();
        }

        ~Baxandall() override
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

        const char* getTreeIdentifier() override { return "baxandall"; }
        void setInputValue (double signalIn) override { Vin->Vs = signalIn; }
        double getOutputValue() override { return Rl->upPort->getPortVoltage(); }
        void setParam (size_t /*paramID*/, double /*paramValue*/) override {}

        int setRootMatrData (matData* rootMats, double* Rp) override
        {
            const auto Ra = Rp[0];
            const auto Rb = Rp[1];
            const auto Rc = Rp[2];
            const auto Rd = Rp[3];
            const auto Re = Rp[4];
            const auto Rf = Rp[5];

            // clang-format off
            double arr[6][6] = { { -2 * ((Rb + Rc) * Rd + (Rb + Rc + Rd) * Re + (Rb + Rc + Rd) * Rf) * Ra / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) + 1, -2 * (Rc * Rd + (Rc + Rd) * Re + Rc * Rf) * Ra / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), 2 * (Rb * Rd + Rb * Re + (Rb + Rd) * Rf) * Ra / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Rb * Re - Rc * Rf) * Ra / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), 2 * (Rb * Rd + (Rb + Rc + Rd) * Rf) * Ra / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Rc * Rd + (Rb + Rc + Rd) * Re) * Ra / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) },
                                 { -2 * (Rc * Rd + (Rc + Rd) * Re + Rc * Rf) * Rb / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * ((Ra + Rc) * Rd + (Ra + Rc + Rd) * Re + (Ra + Rc + Re) * Rf) * Rb / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) + 1, -2 * (Ra * Rd + Ra * Re + (Ra + Re) * Rf) * Rb / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), 2 * (Ra * Re + (Ra + Rc + Re) * Rf) * Rb / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rd - Rc * Rf) * Rb / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * ((Ra + Rc) * Rd + (Rc + Rd) * Re) * Rb / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) },
                                 { 2 * (Rb * Rd + Rb * Re + (Rb + Rd) * Rf) * Rc / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rd + Ra * Re + (Ra + Re) * Rf) * Rc / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * ((Ra + Rb) * Rd + (Ra + Rb) * Re + (Ra + Rb + Rd + Re) * Rf) * Rc / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) + 1, 2 * ((Ra + Rb) * Re + (Ra + Re) * Rf) * Rc / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * ((Ra + Rb) * Rd + (Rb + Rd) * Rf) * Rc / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rd - Rb * Re) * Rc / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) },
                                 { -2 * (Rb * Re - Rc * Rf) * Rd / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), 2 * (Ra * Re + (Ra + Rc + Re) * Rf) * Rd / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), 2 * ((Ra + Rb) * Re + (Ra + Re) * Rf) * Rd / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Re + (Ra + Rc + Re) * Rf) * Rd / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) + 1, -2 * (Ra * Rb + (Ra + Rb) * Rc + Rc * Rf) * Rd / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + Rb * Re) * Rd / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) },
                                 { 2 * (Rb * Rd + (Rb + Rc + Rd) * Rf) * Re / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rd - Rc * Rf) * Re / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * ((Ra + Rb) * Rd + (Rb + Rd) * Rf) * Re / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + Rc * Rf) * Re / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd + (Rb + Rc + Rd) * Rf) * Re / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) + 1, -2 * (Ra * Rb + (Ra + Rb) * Rc + Ra * Rd) * Re / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) },
                                 { -2 * (Rc * Rd + (Rb + Rc + Rd) * Re) * Rf / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * ((Ra + Rc) * Rd + (Rc + Rd) * Re) * Rf / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rd - Rb * Re) * Rf / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + Rb * Re) * Rf / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + Ra * Rd) * Rf / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf), -2 * (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf / ((Ra * Rb + (Ra + Rb) * Rc) * Rd + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rb) * Rd) * Re + (Ra * Rb + (Ra + Rb) * Rc + (Ra + Rc) * Rd + (Rb + Rc + Rd) * Re) * Rf) + 1 } };
            // clang-format on

            for ( unsigned int ii = 0; ii < 6; ++ii )
                for ( unsigned int jj = 0; jj < 6; ++jj )
                    rootMats->Smat.at(ii, jj) = arr[ii][jj];

            return 0;
        }

    private:
        std::unique_ptr<wdfTerminatedRes> Pt_plus;
        std::unique_ptr<wdfTerminatedRes> Resd;
        std::unique_ptr<wdfTerminatedRes> Pt_minus;
        std::unique_ptr<wdfTerminatedRes> Rese;
        std::unique_ptr<wdfTerminatedRes> Rl;
        std::unique_ptr<wdfTerminatedRes> Resc;
        std::unique_ptr<wdfTerminatedRes> Pb_minus;
        std::unique_ptr<wdfTerminatedRes> Resb;
        std::unique_ptr<wdfTerminatedRes> Pb_plus;
        std::unique_ptr<wdfTerminatedRes> Resa;

        std::unique_ptr<wdfTerminatedCap> Cd;
        std::unique_ptr<wdfTerminatedCap> Ce;
        std::unique_ptr<wdfTerminatedCap> Cc;
        std::unique_ptr<wdfTerminatedCap> Cb;
        std::unique_ptr<wdfTerminatedCap> Ca;

        std::unique_ptr<wdfTerminatedResVSource> Vin;

        std::unique_ptr<wdfTerminatedSeries> S4;
        std::unique_ptr<wdfTerminatedSeries> S5;
        std::unique_ptr<wdfTerminatedSeries> S3;
        std::unique_ptr<wdfTerminatedSeries> S2;
        std::unique_ptr<wdfTerminatedSeries> S1;

        std::unique_ptr<wdfTerminatedParallel> P4;
        std::unique_ptr<wdfTerminatedParallel> P5;
        std::unique_ptr<wdfTerminatedParallel> P1;
        std::unique_ptr<wdfTerminatedParallel> P3;
        std::unique_ptr<wdfTerminatedParallel> P2;
    };
}
