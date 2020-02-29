cmake_minimum_required(VERSION 3.13)

include(cmake/check_for_variables.cmake)

project(firmware_${PROCESSOR_CONFIG} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/processor)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Release>:-Os -flto>
        $<$<CONFIG:Debug>:-Og>
        $<$<COMPILE_LANGUAGE:C>:-std=c11>
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions> # Disable exception handling.
        $<$<COMPILE_LANGUAGE:CXX>:-fno-unwind-tables> # it suppresses the generation of static unwind tables
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti> # Disable generation of information about every class with virtual functions for use by the C++ run-time type identification features
        $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit> # will use .fini for static global destructors and atexit() for static destructors in functions
        $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics> # Do not emit the extra code to use the routines specified in the C++ ABI for thread-safe initialization of local statics. You can use this option to reduce code size slightly in code that doesn’t need to be thread-safe.
        $<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual> # Warn when a function declaration hides virtual functions from a base class.
        $<$<CXX_COMPILER_ID:GNU>:-fstrict-volatile-bitfields> # This option should be used if accesses to volatile bit-fields should use a single access of the width of the field’s type, aligned to a natural alignment if possible.
        $<$<CXX_COMPILER_ID:GNU>:-Wlogical-op> # Warn about suspicious uses of logical operators in expressions.
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-override> # Warn about overriding virtual functions that are not marked with the override keyword.
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-types> # Warn about types with virtual methods where code quality would be improved
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-methods> # Warn about virtual methods where code quality would be improved if the method were declared with the C++11 final specifier
        $<$<CXX_COMPILER_ID:GNU>:-Wstringop-overflow> # Warn for calls to string manipulation functions such as memcpy and strcpy that are determined to overflow the destination buffer
        -Wuninitialized # Warn if an automatic variable is used without first being initialized
        -Werror # Make all warnings into errors.s
        -Wall # This enables all the warnings about constructions that some users consider questionable
        -Wextra # This enables some extra warning flags that are not enabled by ‘-Wall'
        -Wcast-align # Warn whenever a pointer is cast such that the required alignment of the target is increased.
        -Wconversion # Warn for implicit conversions that may alter a value.
        -Wsign-conversion # Warn for implicit conversions that may change the sign of an integer value
        -Wold-style-cast # Warn if an old-style (C-style) cast to a non-void type is used within a C++ program.
        -Wshadow # Warn whenever a local variable or type declaration shadows another variable, parameter, type, class member (in C++), or whenever a built-in function is shadowed
        -Wpedantic # Issue all the warnings demanded by strict ISO C and ISO C++
        -pedantic-errors # Give an error whenever the base standard requires a diagnostic
        -ffunction-sections # Place each function or data item into its own section in the output file if the target supports arbitrary sections.
        -fdata-sections # Place each function or data item into its own section in the output file if the target supports arbitrary sections.
        -fno-threadsafe-statics # Do not emit the extra code to use the routines specified in the C++ ABI for thread-safe initialization of local statics.
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
        $<$<CXX_COMPILER_ID:CLANG>:-fuse-ld=lld>
        -nodefaultlibs
        -nostdlib
        -Wl,-Map=firmware_${PROCESSOR_CONFIG}.map
        -L ${CMAKE_SOURCE_DIR}/lib/linker/
        -T ${CMAKE_SOURCE_DIR}/lib/linker/${PROCESSOR_CONFIG}.ld
        -flto
        -Wl,--gc-sections
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
       crt0::crt0
)

add_subdirectory(src/startup)

include(cmake/generate-binary-file.cmake)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
