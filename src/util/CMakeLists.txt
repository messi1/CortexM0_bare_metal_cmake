cmake_minimum_required(VERSION 3.13)

project(util VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
    INTERFACE
     cxx_std_17
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src/
)

target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/communication_base.h
        ${CMAKE_CURRENT_SOURCE_DIR}/communication_buffer_depth_one_byte.h
        ${CMAKE_CURRENT_SOURCE_DIR}/noncopyable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/port_pin.h
        ${CMAKE_CURRENT_SOURCE_DIR}/spi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/spi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/reg_access_dynamic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/reg_access_static.h
)

#source_group()
