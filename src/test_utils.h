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
    // wdf.process(signal.data(), nSamples);
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
        std::cout << "CPP WDF is " << f_wdf_dur / cpp_wdf_dur << "x faster!" << std::endl;
    else
        std::cout << "Faust WDF is " << cpp_wdf_dur / f_wdf_dur << "x faster!" << std::endl;
}
