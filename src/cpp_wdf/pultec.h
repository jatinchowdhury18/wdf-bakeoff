#pragma once

#include <chowdsp_wdf/chowdsp_wdf.h>

namespace cpp_wdf
{

namespace CircuitValues
{

// potentiometers
constexpr float p_HB = 10.0e3f;
constexpr float p_HC = 1.0e3f;
constexpr float p_HBQ = 2.2e3f;
constexpr float p_LB = 100.0e3f;
constexpr float p_LC = 100.0e3f;

// resistors
constexpr float r_a = 570.0f;
constexpr float r_b = 1.0e3f;
constexpr float r_c = 75.0f;
constexpr float r_d = 10.0e3f;

} // namespace CircuitValues

using namespace chowdsp::wdft;

class Pultec
{
    using dtype = float;
    using Res = ResistorT<dtype>;
    using Cap = CapacitorT<dtype>;
    using Ind = InductorT<dtype>;
    using ResVs = ResistiveVoltageSourceT<float>;

    template<typename P1, typename P2>
    using Par = WDFParallelT<dtype, P1, P2>;

    template<typename P1, typename P2>
    using Ser = WDFSeriesT<dtype, P1, P2>;

public:
    Pultec (float fs) :
        c_HBF (10.0e-9f, fs),
        c_HCF (94.0e-9f, fs),
        c_LF_a (47.0e-9f, fs),
        c_LF_b (1.0e-6f, fs),
        l_HBF (65.0e-3f, fs),
        R (Sa, Sb, r_b, r_d, Pe, Sf)
    {
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            vIn.setVoltage (x[i]);
            R.compute();
            y[i] = (voltage<dtype> (r_d) + voltage<dtype> (c_LF_b)) * makeupGain;
        }
    }

    // pots
    Res p_HB_p { CircuitValues::p_HB * 0.5f };
    Res p_HB_m { CircuitValues::p_HB * 0.5f };
    Res p_HBQ { CircuitValues::p_HBQ * 0.5f };
    Res p_LC { CircuitValues::p_LC * 0.5f };
    Res p_HC_p { CircuitValues::p_HC * 0.5f };
    Res p_HC_m0 { CircuitValues::p_HC * 0.5f };
    Res p_HC_m1 { CircuitValues::p_HC * 0.5f };
    Res p_LB { CircuitValues::p_LB * 0.5f };

    // caps and inductors
    Cap c_HBF;
    Cap c_HCF;
    Cap c_LF_a;
    Cap c_LF_b;
    Ind l_HBF;

private:
    const float makeupGain = 20.0f * std::log10 (27.0f);

    // resistors
    Res r_a { CircuitValues::r_a };
    Res r_b { CircuitValues::r_b };
    Res r_c { CircuitValues::r_c };
    Res r_d { CircuitValues::r_d };
    ResVs vIn { 10.0f };

    // port A
    Par<Res, Cap> P1 { p_LC, c_LF_a };
    Ser<Res, decltype(P1)> Sa { p_HC_m0, P1 };

    // port B
    Ser<Cap, Res> S1 { c_HCF, r_c };
    Par<Res, decltype(S1)> P2 { p_HC_m1, S1 };
    Ser<Res, decltype(P2)> Sb { p_HC_p, P2 };

    // port E
    Par<Cap, Res> Pe { c_LF_b, p_LB };

    // port F
    Ser<Ind, Cap> S2 { l_HBF, c_HBF };
    Ser<Res, decltype(S2)> S3 { p_HBQ, S2 };
    Par<Res, decltype(S3)> P3 { p_HB_m, S3 };
    Par<ResVs, Res> P4 { vIn, r_a };
    Ser<Res, decltype(P4)> S4 { p_HB_p, P4 };
    Ser<decltype(S4), decltype(P3)> Sf { S4, P3 };


    struct ImpedanceCalc
    {
        template <typename RType>
        static void calcImpedance (RType& R)
        {
            const auto [Ra, Rb, Rc, Rd, Re, Rf] = R.getPortImpedances();

            float mat[6][6];
            mat[0][0] = ((-Ra)*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf))
                                                                                                                                                                 + Rc*(Re*Rf   + Rd*(Re + Rf)) +   Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[0][1] = (2*Ra*((Rc + Re)*Rf + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[0][2] = (2*Ra*(Rb*Rd + Re*Rf + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[0][3] = (-1)*((2*Ra*(Rb*(Rc + Re) + Rc*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[0][4] = (2*Ra*(Rb*Rd - Rc*Rf))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[0][5] = (-1)*((2*Ra*(Rc*Re + Rb*(Rc + Rd + Re)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[1][0] = (2*Rb*((Rc + Re)*Rf + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[1][1] = (Ra*(Rd*Re - Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) - Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf))
                                                                                                                                                              + Rc*(Re*Rf + Rd*(Re + Rf)) +   Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[1][2] = (-1)*((2*Rb*(Ra*Re + Re*Rf + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[1][3] = (-2*Ra*Rb*Re + 2*Rb*Rc*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[1][4] = (2*Rb*(Ra*(Rc + Rd) + Rc*(Rd + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[1][5] = (-1)*((2*Rb*(Rc*Rd + Ra*(Rc + Rd + Re)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[2][0] = (2*Rc*(Rb*Rd + Re*Rf + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[2][1] = (-1)*((2*Rc*(Ra*Re + Re*Rf + Rd*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[2][2] = 1 - (2*Rc*(Rd*Re + Rd*Rf + Re*Rf + Rb*(Rd + Rf) + Ra*(Rb + Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[2][3] = (-1)*((2*Rc*(Rb*Rf + Ra*(Rb + Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[2][4] = (-1)*((2*Rc*(Ra*(Rb + Rf) + Rb*(Rd + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[2][5] = (2*Rc*(Rb*Rd - Ra*Re))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[3][0] = (-1)*((2*Rd*(Rb*(Rc + Re) + Rc*(Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[3][1] = (-2*Ra*Rd*Re + 2*Rc*Rd*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[3][2] = (-1)*((2*Rd*(Rb*Rf + Ra*(Rb + Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[3][3] = 1 - (2*Rd*(Rc*(Re + Rf) + Ra*(Rb + Re + Rf) + Rb*(Rc + Re + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[3][4] = (-1)*((2*Rd*((Rb + Rc)*Rf + Ra*(Rb + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[3][5] = (-1)*((2*Rd*((Ra + Rc)*Re + Rb*(Rc + Re)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[4][0] = (2*Re*(Rb*Rd - Rc*Rf))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[4][1] = (2*Re*(Ra*(Rc + Rd) + Rc*(Rd + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[4][2] = (-1)*((2*Re*(Ra*(Rb + Rf) + Rb*(Rd + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[4][3] = (-1)*((2*Re*((Rb + Rc)*Rf + Ra*(Rb + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[4][4] = 1 - (2*Re*((Rb + Rc)*(Rd + Rf) + Ra*(Rb + Rc + Rd + Rf)))/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[4][5] = (2*((Rb + Rc)*Rd + Ra*(Rc + Rd))*Re)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[5][0] = (-1)*((2*(Rc*Re + Rb*(Rc + Rd + Re))*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[5][1] = (-1)*((2*(Rc*Rd + Ra*(Rc + Rd + Re))*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[5][2] = (2*(Rb*Rd - Ra*Re)*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[5][3] = (-1)*((2*((Ra + Rc)*Re + Rb*(Rc + Re))*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf))));
            mat[5][4] = (2*((Rb + Rc)*Rd + Ra*(Rc + Rd))*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));
            mat[5][5] = 1 - (2*(Rc*(Rd + Re) + Ra*(Rc + Rd + Re) + Rb*(Rc + Rd + Re))*Rf)/(Ra*(Rd*Re + Rb*(Rc + Rd + Re) + Rd*Rf + Re*Rf + Rc*(Re + Rf)) + Rc*(Re*Rf + Rd*(Re + Rf)) + Rb*(Re*Rf + Rc*(Rd + Rf) + Rd*(Re + Rf)));

            R.setSMatrixData (mat);
        }
    };
    RootRtypeAdaptor<float, ImpedanceCalc,
                            decltype(Sa),
                            decltype(Sb),
                            Res,
                            Res,
                            decltype(Pe),
                            decltype(Sf)> R;
};

} // namespace cpp_wdf
