#pragma once

#include <r_type.h>

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

using namespace chowdsp::WDFT;

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
        R (std::tie (Sa, Sb, r_b, r_d, Pe, Sf))
    {
    }

    void compute (int numSamples, float** input, float** output)
    {
        auto* x = input[0];
        auto* y = output[0];
        for (int i = 0; i < numSamples; ++i)
        {
            vIn.setVoltage (x[i]);
            R.incident (0.0f);
            y[i] = (voltage<dtype> (r_d) + voltage<dtype> (c_LF_b)) * makeupGain;
        }
    }

    template <int port_idx>
    constexpr float portImpedance()
    {
        return R.getPort<port_idx>().R;
    }

    void setScatteringMatrix (const float (&mat)[6][6])
    {
        R.setSMatrixData (mat);
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

    RootRtypeAdaptor<float, decltype(Sa),
                            decltype(Sb),
                            Res,
                            Res,
                            decltype(Pe),
                            decltype(Sf)> R;
};

} // namespace cpp_wdf
