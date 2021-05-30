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
|---|---|---|---|---|---|---|
|LPF|0.30|199.1|0.59|101.8|0.47|127.5|
|FF2|0.77|77.5|2.17|27.6|2.06|29.2|
|Diode Clipper|2.83|21.2|0.54|110.2|0.60|100.4|
