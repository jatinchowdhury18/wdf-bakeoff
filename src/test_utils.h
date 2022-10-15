#pragma once

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

std::vector<float> createSignal(int numSamples)
{
    std::vector<float> signal (numSamples, 0.0f);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-1.0f,1.0f);
    
    for(int i = 0; i < numSamples; ++i)
        signal[i] = distribution(generator);

    return signal;
}

template<typename WDFType>
double testWDF(WDFType& wdf, double timeSeconds, double sampleRate)
{
    const auto nSamples = int (timeSeconds * sampleRate);
    auto signal = createSignal(nSamples);

    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double>;

    auto start = clock_t::now();
    auto* data = signal.data();
    wdf.compute(nSamples, &data, &data);
    auto duration = std::chrono::duration_cast<second_t>(clock_t::now() - start).count();

    std::cout << "Processed " << timeSeconds << " seconds of signal in "
              << duration << " seconds" << std::endl;
    std::cout << timeSeconds / duration << "x real-time" << std::endl;
    return duration;
}

template<typename WDFType>
double testWDFCiaramella(WDFType& wdf, double timeSeconds, double sampleRate)
{
    const auto nSamples = int (timeSeconds * sampleRate);
    auto signal = createSignal(nSamples);

    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double>;

    auto start = clock_t::now();
    auto* data = signal.data();
    wdf.process(data, data, nSamples);
    auto duration = std::chrono::duration_cast<second_t>(clock_t::now() - start).count();

    std::cout << "Processed " << timeSeconds << " seconds of signal in "
              << duration << " seconds" << std::endl;
    std::cout << timeSeconds / duration << "x real-time" << std::endl;
    return duration;
}

template<typename FaustWDFType, typename CPPWDFType>
void compareWDFs(FaustWDFType& f_wdf, CPPWDFType& cpp_wdf, double timeSeconds, double sampleRate)
{
    std::cout << "Running Faust WDF..." << std::endl;
    auto f_wdf_dur = testWDF(f_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP WDF..." << std::endl;
    auto cpp_wdf_dur = testWDF(cpp_wdf, timeSeconds, sampleRate);

    if (f_wdf_dur > cpp_wdf_dur)
        std::cout << "CPP WDF is " << f_wdf_dur / cpp_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_wdf_dur / f_wdf_dur << "x faster than C++!" << std::endl;
}

template<typename FaustWDFType, typename CPPWDFType, typename CPPPOLYWDFType>
void compareWDFs(FaustWDFType& f_wdf, CPPWDFType& cpp_wdf, CPPPOLYWDFType& cpp_poly_wdf, double timeSeconds, double sampleRate)
{
    std::cout << "Running Faust WDF..." << std::endl;
    auto f_wdf_dur = testWDF(f_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP WDF..." << std::endl;
    auto cpp_wdf_dur = testWDF(cpp_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP Polymorphic WDF..." << std::endl;
    auto cpp_poly_wdf_dur = testWDF(cpp_poly_wdf, timeSeconds, sampleRate);

    if (f_wdf_dur > cpp_wdf_dur)
        std::cout << "CPP WDF is " << f_wdf_dur / cpp_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_wdf_dur / f_wdf_dur << "x faster than C++!" << std::endl;

    if (f_wdf_dur > cpp_poly_wdf_dur)
        std::cout << "CPP Polymorphic WDF is " << f_wdf_dur / cpp_poly_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_poly_wdf_dur / f_wdf_dur << "x faster than C++ polymorphic!" << std::endl;
}

template<typename FaustWDFType, typename CPPWDFType, typename CPPPOLYWDFType, typename CRMWDFType>
void compareWDFsCRM(FaustWDFType& f_wdf, CPPWDFType& cpp_wdf, CPPPOLYWDFType& cpp_poly_wdf, CRMWDFType& crm_wdf, double timeSeconds, double sampleRate)
{
    std::cout << "Running Faust WDF..." << std::endl;
    auto f_wdf_dur = testWDF(f_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP WDF..." << std::endl;
    auto cpp_wdf_dur = testWDF(cpp_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP Polymorphic WDF..." << std::endl;
    auto cpp_poly_wdf_dur = testWDF(cpp_poly_wdf, timeSeconds, sampleRate);

    std::cout << "Running Ciaramella WDF..." << std::endl;
    auto crm_wdf_dur = testWDFCiaramella(crm_wdf, timeSeconds, sampleRate);

    if (f_wdf_dur > cpp_wdf_dur)
        std::cout << "CPP WDF is " << f_wdf_dur / cpp_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_wdf_dur / f_wdf_dur << "x faster than C++!" << std::endl;

    if (f_wdf_dur > cpp_poly_wdf_dur)
        std::cout << "CPP Polymorphic WDF is " << f_wdf_dur / cpp_poly_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_poly_wdf_dur / f_wdf_dur << "x faster than C++ polymorphic!" << std::endl;
}

template<typename FaustWDFType, typename CPPWDFType, typename CPPPOLYWDFType, typename RTWDFType>
void compareWDFs(FaustWDFType& f_wdf, CPPWDFType& cpp_wdf, CPPPOLYWDFType& cpp_poly_wdf, RTWDFType& rt_wdf, double timeSeconds, double sampleRate)
{
    std::cout << "Running Faust WDF..." << std::endl;
    auto f_wdf_dur = testWDF(f_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP WDF..." << std::endl;
    auto cpp_wdf_dur = testWDF(cpp_wdf, timeSeconds, sampleRate);

    std::cout << "Running CPP Polymorphic WDF..." << std::endl;
    auto cpp_poly_wdf_dur = testWDF(cpp_poly_wdf, timeSeconds, sampleRate);

    std::cout << "Running RT-WDF WDF..." << std::endl;
    auto rt_wdf_dur = testWDF(rt_wdf, timeSeconds, sampleRate);

    if (f_wdf_dur > cpp_wdf_dur)
        std::cout << "CPP WDF is " << f_wdf_dur / cpp_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_wdf_dur / f_wdf_dur << "x faster than C++!" << std::endl;

    if (f_wdf_dur > cpp_poly_wdf_dur)
        std::cout << "CPP Polymorphic WDF is " << f_wdf_dur / cpp_poly_wdf_dur << "x faster than Faust!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_poly_wdf_dur / f_wdf_dur << "x faster than C++ polymorphic!" << std::endl;
}
