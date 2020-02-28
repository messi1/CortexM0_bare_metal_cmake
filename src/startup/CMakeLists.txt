cmake_minimum_required(VERSION 3.13)

project(crt0 VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/processor)
include(${PROCESSOR_CONFIG})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/crt0.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/crt0_init_ram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/crt1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/int_vect.cpp
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Release>:-Os -flto>
        $<$<CONFIG:Debug>:-Og>
        $<$<COMPILE_LANGUAGE:C>:-std=c11>
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
        $<$<COMPILE_LANGUAGE:CXX>:-fms-extensions>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
        $<$<CXX_COMPILER_ID:GNU>:-fstrict-volatile-bitfields>
        $<$<CXX_COMPILER_ID:GNU>:-Wlogical-op>
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-override>
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-types>
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-methods>
        -fno-unwind-tables
        -ffunction-sections
        -fdata-sections 
        -fno-threadsafe-statics
        -ffreestanding
        -Werror
        -Wall
        -Wextra
        -Wcast-align
        -Wconversion
        -Wsign-conversion
        -Wold-style-cast
        -Wshadow
        -pedantic
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-nostartfiles> # https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
        $<$<CXX_COMPILER_ID:CLANG>:-fuse-ld=lld>
        -nodefaultlibs
        -nostdlib
        -Wl,-Map=firmware_${PROCESSOR_CONFIG}.map
        -L ${CMAKE_SOURCE_DIR}/lib/linker/
        -T ${CMAKE_SOURCE_DIR}/lib/linker/${PROCESSOR_CONFIG}.ld
        -flto
        -ffunction-sections
        -fdata-sections 
        -Wl,--gc-sections
)



