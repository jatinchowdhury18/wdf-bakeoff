#pragma once

#include <chowdsp_wdf/chowdsp_wdf.h>

namespace cpp_poly_wdf
{
using namespace chowdsp;

/** Fender Bassman tonestack circuit */
template <typename FloatType>
class BassmanTonestack
{
public:
    BassmanTonestack() : R ({ &S1, &S3, &S2, &Cap2, &Res4, &Cap3 })
    {
        R.impedanceCalculator = [] (auto& R) {
            const auto Ra = R.getPortImpedance (0);
            const auto Rb = R.getPortImpedance (1);
            const auto Rc = R.getPortImpedance (2);
            const auto Rd = R.getPortImpedance (3);
            const auto Re = R.getPortImpedance (4);
            const auto Rf = R.getPortImpedance (5);
            const auto Ga = (FloatType) 1 / Ra;
            const auto Gb = (FloatType) 1 / Rb;
            const auto Gc = (FloatType) 1 / Rc;
            const auto Gd = (FloatType) 1 / Rd;
            const auto Ge = (FloatType) 1 / Re;
            const auto Gf = (FloatType) 1 / Rf;

            // clang-format off
            // This scattering matrix was derived using the R-Solver python script (https://github.com/jatinchowdhury18/R-Solver),
            // with netlist input: netlists/bassman.txt
            R.setSMatrixData ({ { 2 * Ra * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Ra * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gb * Gd * Ge) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (Ga * Gb * Gd * Ge - Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (-Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Ra * (-Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                { 2 * Rb * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gb * Gd * Ge) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Rb * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (-Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (Ga * Gb * Gd * Ge - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rb * (-Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                { 2 * Rc * (Ga * Gb * Gc * Gd + Ga * Gb * Gc * Ge + Ga * Gb * Gc * Gf + Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (-Ga * Gb * Gc * Gd - Ga * Gb * Gc * Ge - Ga * Gb * Gc * Gf - Ga * Gc * Gd * Ge - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Rc * (Ga * Gc * Gd * Ge + Ga * Gc * Gd * Gf + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (-Ga * Gc * Gd * Ge - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rc * (Ga * Gc * Gd * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                { 2 * Rd * (Ga * Gb * Gd * Ge - Ga * Gc * Gd * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (-Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (Ga * Gc * Gd * Ge + Ga * Gc * Gd * Gf + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (-Ga * Gb * Gd * Ge - Ga * Gb * Gd * Gf - Ga * Gc * Gd * Ge - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Ge - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Rd * (Ga * Gb * Gd * Ge + Ga * Gc * Gd * Ge + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rd * (-Ga * Gb * Gd * Gf - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                { 2 * Re * (-Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (Ga * Gb * Gd * Ge - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (-Ga * Gc * Gd * Ge - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (Ga * Gb * Gd * Ge + Ga * Gc * Gd * Ge + Gb * Gc * Gd * Ge + Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Re * (-Ga * Gb * Gd * Ge - Ga * Gb * Ge * Gf - Ga * Gc * Gd * Ge - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Gd * Ge - Gb * Gc * Ge * Gf - Gc * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1, 2 * Re * (-Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) },
                                { 2 * Rf * (-Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (Ga * Gc * Gd * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Gd * Gf - Ga * Gc * Gd * Gf - Gb * Gc * Gd * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Ge * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf), 2 * Rf * (-Ga * Gb * Gd * Gf - Ga * Gb * Ge * Gf - Ga * Gc * Gd * Gf - Ga * Gc * Ge * Gf - Ga * Gd * Ge * Gf - Gb * Gc * Gd * Gf - Gb * Gc * Ge * Gf - Gb * Gd * Ge * Gf) / (Ga * Gb * Gd + Ga * Gb * Ge + Ga * Gb * Gf + Ga * Gc * Gd + Ga * Gc * Ge + Ga * Gc * Gf + Ga * Gd * Ge + Ga * Gd * Gf + Gb * Gc * Gd + Gb * Gc * Ge + Gb * Gc * Gf + Gb * Gd * Ge + Gb * Ge * Gf + Gc * Gd * Gf + Gc * Ge * Gf + Gd * Ge * Gf) + 1 } });
            // clang-format on
        };
    }

    void prepare (double sampleRate)
    {
        Cap1.prepare ((FloatType) sampleRate);
        Cap2.prepare ((FloatType) sampleRate);
        Cap3.prepare ((FloatType) sampleRate);
    }

    void compute (int numSamples, FloatType** input, FloatType** output) {
        auto *x = input[0];
        auto *y = output[0];
        for (int i = 0; i < numSamples; ++i) {
            Vres.setVoltage(x[i]);
            R.compute();

            y[i] = wdft::voltage<FloatType>(Res1m) + wdft::voltage<FloatType>(S2) + wdft::voltage<FloatType>(Res3m);
        }
    }

    void setParams (FloatType highPot, FloatType lowPot, FloatType midPot)
    {
        {
            using DeferImpedance = chowdsp::wdft::ScopedDeferImpedancePropagation<decltype (S1), decltype (S3), decltype (S4)>;
            DeferImpedance deferImpedance { S1, S3, S4 };

            Res1m.setResistanceValue (highPot * R1);
            Res1p.setResistanceValue (((FloatType) 1 - highPot) * R1);

            Res2.setResistanceValue (((FloatType) 1 - lowPot) * R2);

            Res3m.setResistanceValue (midPot * R3);
            Res3p.setResistanceValue (((FloatType) 1 - midPot) * R3);
        }

        S2.propagateImpedanceChange();
    }

private:
    wdf::Capacitor<FloatType> Cap1 { 250e-12 };
    wdf::Capacitor<FloatType> Cap2 { 20e-9 }; // Port D
    wdf::Capacitor<FloatType> Cap3 { 20e-9 }; // Port F

    wdf::Resistor<FloatType> Res1p { 1.0 };
    wdf::Resistor<FloatType> Res1m { 1.0 };
    wdf::Resistor<FloatType> Res2 { 1.0 };
    wdf::Resistor<FloatType> Res3p { 1.0 };
    wdf::Resistor<FloatType> Res3m { 1.0 };
    wdf::Resistor<FloatType> Res4 { 56e3 }; // Port E

    wdf::ResistiveVoltageSource<FloatType> Vres { 1.0 };

    // Port A
    wdf::WDFSeries<FloatType> S1 { &Vres, &Res3m };

    // Port B
    wdf::WDFSeries<FloatType> S3 { &Res2, &Res3p };

    // Port C
    wdf::WDFSeries<FloatType> S4 { &Res1p, &Res1m };
    wdf::WDFSeries<FloatType> S2 { &Cap1, &S4 };

    static constexpr double R1 = 250e3;
    static constexpr double R2 = 1e6;
    static constexpr double R3 = 25e3;

    wdf::RootRtypeAdaptor<FloatType> R;
};
}
