cmake_minimum_required(VERSION 3.13)

project(firmware_${PROCESSOR_CONFIG}_blinky VERSION 0.0.1 LANGUAGES CXX)
add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

include(generate-different-output-format)
include(processor/${PROCESSOR_CONFIG})
get_property(COMMON_COMPILE_OPTIONS
        GLOBAL PROPERTY COMMON_PRIVATE_COMPILE_OPTIONS)
get_property(COMMON_LINK_OPTIONS
        GLOBAL PROPERTY COMMON_PRIVATE_LINK_OPTIONS)

target_compile_features(${PROJECT_NAME}
    PRIVATE
     cxx_std_17
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${COMMON_COMPILE_OPTIONS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        ${COMMON_LINK_OPTIONS}
        $<$<CXX_COMPILER_ID:GNU>:-nostartfiles> # https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
        $<$<CXX_COMPILER_ID:CLANG>:-fuse-ld=lld>
        -nodefaultlibs
        -nostdlib

        -Wl,-Map=${PROJECT_NAME}.map
        -L ${CMAKE_SOURCE_DIR}/linker/
        -T ${CMAKE_SOURCE_DIR}/linker/${PROCESSOR_CONFIG}.ld
        -Wl,--gc-sections
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
       crt0::crt0
       util::util
)
