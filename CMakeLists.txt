cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project (wdf-bakeoff)

add_executable(wdf-bakeoff
    src/main.cpp
)

target_include_directories(wdf-bakeoff
    PUBLIC
        modules/chowdsp_utils/DSP/WDF
)
