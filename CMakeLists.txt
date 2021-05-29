cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project (wdf-bakeoff)

add_executable(wdf-bakeoff
    src/main.cpp
)

# include WDF library
target_include_directories(wdf-bakeoff PUBLIC modules/chowdsp_utils/DSP/WDF)

# compile Faust code!
add_custom_target(FaustOutputs)
set(FAUST_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/faust_out)
file(MAKE_DIRECTORY ${FAUST_OUT_DIR})

add_custom_command(
    TARGET FaustOutputs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/faust_wdf
    # COMMAND faust -i -a faustMinimal.h lpf2.dsp -o ${FAUST_OUT_DIR}/faust_lpf2.h --class-name LPF2
    # COMMAND faust -i -a faustMinimal.h  diode_clipper.dsp -o ${FAUST_OUT_DIR}/faust_dc.h --class-name DC 
    # COMMAND faust -i -a faustMinimal.h -t 0 ff2.dsp -o ${FAUST_OUT_DIR}/faust_ff2.h --class-name FF2
    VERBATIM
)

add_dependencies(wdf-bakeoff FaustOutputs)
target_include_directories(wdf-bakeoff PUBLIC ${FAUST_OUT_DIR})
