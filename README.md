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
