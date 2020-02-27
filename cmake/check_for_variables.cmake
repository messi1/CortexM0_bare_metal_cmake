############################################################################
# The following variables must be set to be able to cross compile:
# PROCESSOR_CONFIG either to LPC11U35 or ATSAMD21G18
# CROSS_COMPILE_PATH to the main directory of either arm-gcc or clang
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


if( (NOT DEFINED CROSS_COMPILER_PATH OR "${CROSS_COMPILER_PATH}" STREQUAL "") AND
    (NOT DEFINED ENV{CROSS_COMPILER_PATH} OR "$ENV{CROSS_COMPILER_PATH}" STREQUAL "") )
    message(FATAL_ERROR
        "Please pass the CROSS_COMPILER_PATH variable either via \ncmake -DCROSS_COMPILER_PATH=<path>\n"
        "or\n"
        "via environement variable CROSS_COMPILER_PATH ")
else()
    if( NOT DEFINED CROSS_COMPILER_PATH)
        set(CROSS_COMPILER_PATH $ENV{CROSS_COMPILER_PATH})
    endif()

    if(EXISTS ${CROSS_COMPILER_PATH}/bin/clang++)
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain/clang-arm-toolchain.cmake)
    elseif(EXISTS ${CROSS_COMPILER_PATH}/bin/arm-none-eabi-c++)
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain/gcc-arm-toolchain.cmake)
    else()
        message("The compiler path does neither contain /bin/clang++ nor does it contain bin/arm-none-eabi-c++")
    endif()
endif()


