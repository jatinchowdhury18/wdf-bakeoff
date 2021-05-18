#include "cpp_wdf/diode_clipper.h"
#include "cpp_wdf/ff2.h"
#include "cpp_wdf/lpf2.h"

#include "faust_lpf2.h"

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

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 4)
    {
        help();
        return 1;
    }

    if(std::string(argv[1]) == "--help")
    {
        help();
        return 1;
    }

    std::string circuitType = argv[1];
    double lengthSeconds = 20.0;
    if(argc >= 3)
        lengthSeconds = atoi(argv[2]);

    double sampleRate = 48000.0;
    if(argc == 4)
        sampleRate = atoi(argv[3]);

    std::cout << "Testing Circuit: " << circuitType << std::endl;
    if(circuitType == "lpf2")
    {
        cpp_wdf::LPF2 lpf2 ((float) sampleRate);

        LPF2 lpf2_faust;
        lpf2_faust.init((int) sampleRate);

        compareWDFs(lpf2_faust, lpf2, lengthSeconds, sampleRate);
    }
    else if(circuitType == "diode_clipper")
    {
        cpp_wdf::DiodeClipper dc ((float) sampleRate);
        compareWDFs(dc, dc, lengthSeconds, sampleRate);
    }
    else if(circuitType == "ff2")
    {
        cpp_wdf::FF2 ff2 ((float) sampleRate);
        compareWDFs(ff2, ff2, lengthSeconds, sampleRate);
    }
    else
    {
        std::cout << "Invalid circuit type!" << std::endl;
        return 1;
    }

    return 0;
}
