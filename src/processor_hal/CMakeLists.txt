cmake_minimum_required(VERSION 3.13)

project(processor_hal VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src/processor_hal/port_pin.h
)
