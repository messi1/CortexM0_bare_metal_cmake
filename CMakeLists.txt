cmake_minimum_required(VERSION 3.13)

include(cmake/check_for_variables.cmake)

project(firmware_${PROCESSOR_CONFIG} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/processor)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/crt0.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/crt0_init_ram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/crt1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/int_vect.cpp
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
        -ffunction-sections
        -fno-threadsafe-statics
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

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-nostartfiles> # https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
        -nodefaultlibs
        -nostdlib
        -Wl,-Map=firmware_${PROCESSOR_CONFIG}.map
)

target_link_options(${PROJECT_NAME}
        PRIVATE
            -L ${CMAKE_SOURCE_DIR}/lib/linker/
            -T ${CMAKE_SOURCE_DIR}/lib/linker/lpc11u35.ld
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
       
)

#add_subdirectory(src/startup)

include(${PROCESSOR_CONFIG})

include(cmake/generate-binary-file.cmake)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
