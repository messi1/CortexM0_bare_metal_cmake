cmake_minimum_required(VERSION 3.13)

include(cmake/check_for_variables.cmake)

project(firmware_${PROCESSOR_CONFIG} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(global_properties)

option(PROTOTHREAD_CPP "Include the protothread library" OFF)
if(PROTOTHREAD_CPP)
    include(protothread_cpp)
    set(PROTOTHREAD_DEP "protothread_cpp::protothread_cpp")
endif(PROTOTHREAD_CPP)

option(WARNING_AS_ERRORS "Treat any warning as compile time error" ON)
if(WARNING_AS_ERRORS)
  set(COMPILE_WARNING_AS_ERROR "-Werror")
endif(WARNING_AS_ERRORS)

add_subdirectory(src/startup)
add_subdirectory(src/blinky)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
