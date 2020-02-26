############################################################################
# The following variables must be set to be able to cross compile:
# PROCESSOR_CONFIG either to LPC11U35 or ATSAMD21G18
# CROSS_COMPILE_PATH to the main directory of either arm-gcc or clang
# COMPILER_CONFIG to either GCC or CLANG to load the correct toolchain file
#############################################################################

if( NOT DEFINED PROCESSOR_CONFIG OR "${PROCESSOR_CONFIG}" STREQUAL "" )
    if( NOT DEFINED ENV{PROCESSOR_CONFIG} OR "$ENV{PROCESSOR_CONFIG}" STREQUAL "" )
        message(FATAL_ERROR
            "Please pass the PROCESSOR_CONFIG variable either via \ncmake -DPROCESSOR_CONFIG=(LPC11U35/ATSAMD21G18)\n"
            "or\n"
            "via environement variable PROCESSOR_CONFIG ")
    else()
        set(PROCESSOR_CONFIG $ENV{PROCESSOR_CONFIG})
    endif()
endif()


if( NOT DEFINED CROSS_COMPILER_PATH OR "${CROSS_COMPILER_PATH}" STREQUAL "" )
    if( NOT DEFINED ENV{CROSS_COMPILER_PATH} OR "$ENV{CROSS_COMPILER_PATH}" STREQUAL "" )
        message(FATAL_ERROR
            "Please pass the CROSS_COMPILER_PATH variable either via \ncmake -DCROSS_COMPILER_PATH=<path>\n"
            "or\n"
            "via environement variable CROSS_COMPILER_PATH ")
    else()
        set(CROSS_COMPILER_PATH $ENV{CROSS_COMPILER_PATH})
    endif()
endif()


if( NOT DEFINED CMAKE_TOOLCHAIN_FILE OR "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    if( "$ENV{COMPILER_CONFIG}" STREQUAL "GCC" OR "${COMPILER_CONFIG}" STREQUAL "GCC")
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain/gcc-arm-toolchain.cmake)
    elseif( "$ENV{COMPILER_CONFIG}" STREQUAL "CLANG" OR "${COMPILER_CONFIG}" STREQUAL "CLANG")
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain/clang-arm-toolchain.cmake)
    else()
        message(FATAL_ERROR
            "Please pass the COMPILER_CONFIG variable either via \n-DCOMPILER_CONFIG=(GCC/CLANG)\n"
            "or\n"
            "via environement variable COMPILER_CONFIG ")
    endif()
endif()
