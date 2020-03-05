cmake_minimum_required(VERSION 3.13)

include(cmake/check_for_variables.cmake)

project(firmware_${PROCESSOR_CONFIG} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(PROTOTHREAD_CPP "Include the protothread library" OFF)
if(PROTOTHREAD_CPP)
    include(protothread_cpp)
    set(PROTOTHREAD_DEP "protothread_cpp::protothread_cpp")
endif(PROTOTHREAD_CPP)

option(WARNING_AS_ERRORS "Treat any warning as compile time error" ON)
if(WARNING_AS_ERRORS)
  set(COMPILE_WARNING_AS_ERROR "-Werror")
endif(WARNING_AS_ERRORS)

include(global_properties)

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${COMMON_PRIVATE_COMPILE_OPTIONS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/main.cpp
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
        -Wl,--gc-sections
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
       crt0::crt0
       ${PROTOTHREAD_DEP}
)

add_subdirectory(src/startup)
include(processor/${PROCESSOR_CONFIG})
include(generate-binary-file)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
