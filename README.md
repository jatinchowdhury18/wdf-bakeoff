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

The table below shows the time taken to process 100 seconds of
audio at 192 kHz sample rate, as well as the "real-time" ratio
(seconds of audio per second of processing time). The `C++`
columns are for the C++ implementation using tempaltes,
while the `C++ poly` measurements are for the C++
implementation with run-time polymorphism.

|Circuit|Faust (time)|Faust (ratio)|C++ (time)|C++ (ratio)|C++ poly (time)|C++ poly (ratio)|
|---    |---         |---          |---       |---        |---            |---             |
|LPF    |0.47        |211.5        |0.21      |470.7      |0.81           |123.3           |
|FF2    |1.05        |94.9         |1.56      |64.3       |3.07           |32.6            |
|Diode Clipper|3.60  |27.8         |0.47      |214.2      |0.62           |160.7           |
