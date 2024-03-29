cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project (wdf-bakeoff)

add_executable(wdf-bakeoff
    src/main.cpp

    src/ciaramella_out/crm_lpf2.cpp
)

# link with chowdsp_wdf
add_subdirectory(modules/chowdsp_wdf)
add_subdirectory(modules/xsimd)
target_link_libraries(wdf-bakeoff
    PRIVATE
        chowdsp_wdf
        xsimd
)

# link with RT-WDF
find_package(Armadillo REQUIRED)
target_link_libraries(wdf-bakeoff PRIVATE ${ARMADILLO_LIBRARIES})
target_include_directories(wdf-bakeoff
    PRIVATE
        ${ARMADILLO_INCLUDE_DIRS}
        modules/rt-wdf_lib/Libs
)
target_sources(wdf-bakeoff
    PRIVATE
        modules/rt-wdf_lib/Libs/rt-wdf/rt-wdf.cpp
        modules/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlModels.cpp
        modules/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlSolvers.cpp
)

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
    # COMMAND faust -i -a faustMinimal.h -t 0 pultec.dsp -o ${FAUST_OUT_DIR}/faust_pultec.h --class-name Pultec
    # COMMAND faust -i -a faustMinimal.h -t 0 baxandall.dsp -o ${FAUST_OUT_DIR}/faust_baxandall.h --class-name Baxandall
    # COMMAND faust -i -a faustMinimal.h -t 0 bassman.dsp -o ${FAUST_OUT_DIR}/faust_bassman.h --class-name Bassman
    VERBATIM
)

add_dependencies(wdf-bakeoff FaustOutputs)
target_include_directories(wdf-bakeoff PRIVATE ${FAUST_OUT_DIR})
