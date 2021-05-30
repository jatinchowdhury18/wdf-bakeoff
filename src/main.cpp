#include "cpp_wdf/diode_clipper.h"
#include "cpp_wdf/ff2.h"
#include "cpp_wdf/lpf2.h"

#include "cpp_poly_wdf/diode_clipper.h"
#include "cpp_poly_wdf/ff2.h"
#include "cpp_poly_wdf/lpf2.h"

#include "faust_ff2.h"
#include "faust_lpf2.h"
#include "faust_dc.h"

#include "test_utils.h"

void help()
{
    std::cout << "WDF Bakeoff tool:" << std::endl;
    std::cout << "Usage: wdf-bakeoff <circuit> [<length_seconds> <sample_rate>]" << std::endl;
    std::cout << std::endl;
    std::cout << "Available circuits: " << std::endl;
    std::cout << "\tlpf2" << std::endl;
    std::cout << "\tdiode_clipper" << std::endl;
    std::cout << "\tff2" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 4)
    {
        help();
        return 1;
    }

    if (std::string(argv[1]) == "--help")
    {
        help();
        return 1;
    }

    std::string circuitType = argv[1];
    double lengthSeconds = 20.0;
    if (argc >= 3)
        lengthSeconds = atoi(argv[2]);

    double sampleRate = 48000.0;
    if (argc == 4)
        sampleRate = atoi(argv[3]);

    std::cout << "Testing Circuit: " << circuitType << std::endl;
    if (circuitType == "lpf2")
    {
        cpp_wdf::LPF2 lpf2((float)sampleRate);

        cpp_poly_wdf::LPF2 lpf2_poly;
        lpf2_poly.reset((float)sampleRate);

        LPF2 lpf2_faust;
        lpf2_faust.init((int)sampleRate);

        compareWDFs(lpf2_faust, lpf2, lpf2_poly, lengthSeconds, sampleRate);
    }
    else if (circuitType == "diode_clipper")
    {
        cpp_wdf::DiodeClipper dc((float)sampleRate);
        
        cpp_poly_wdf::DiodeClipper dc_poly;
        dc_poly.reset((float)sampleRate);

        DC dc_faust;
        dc_faust.init((int)sampleRate);

        compareWDFs(dc_faust, dc, dc_poly, lengthSeconds, sampleRate);
    }
    else if (circuitType == "ff2")
    {
        cpp_wdf::FF2 ff2((float)sampleRate);

        cpp_poly_wdf::FF2 ff2_poly;
        ff2_poly.reset((float)sampleRate);

        FF2 ff2_faust;
        ff2_faust.init((int)sampleRate);

        compareWDFs(ff2_faust, ff2, ff2_poly, lengthSeconds, sampleRate);
    }
    else
    {
        std::cout << "Invalid circuit type!" << std::endl;
        return 1;
    }

    return 0;
}
