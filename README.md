# WDF Bakeoff

Comparing performance between Wave Digital Filters implemented in C++ and Faust.

## Building

First clone the repository and submodules:
```bash
git clone https://github.com/jatinchowdhury18/wdf-bakeoff
cd wdf-bakeoff
git submodule update --init --recursive
```

Next, build with CMake:
```bash
cmake -Bbuild
cmake --build build --config Release
```

Finally, run the tool:
```bash
./build/wdf-bakeoff --help
```

## Results

The table below shows the time taken to process 60 seconds of
audio at 192 kHz sample rate, as well as the "real-time" ratio
(seconds of audio per second of processing time). The `C++`
columns are for the C++ implementation using tempaltes,
while the `C++ poly` measurements are for the C++
implementation with run-time polymorphism.

|Circuit|Faust (time)|Faust (ratio)|C++ (time)|C++ (ratio)|C++ poly (time)|C++ poly (ratio)|
|---    |---         |---          |---       |---        |---            |---             |
|LPF    |0.37        |161.0        |0.50      |120.0      |0.61           |99.0            |
|FF2    |0.86        |69.8         |1.22      |49.1       |2.62           |22.9            |
|Diode Clipper|2.83  |21.2         |0.38      |158.6      |0.36           |164.9           |
