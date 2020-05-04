cmake_minimum_required(VERSION 3.13)

project(crt0 VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(processor/${PROCESSOR_CONFIG})

get_property(COMMON_COMPILE_OPTIONS
        GLOBAL PROPERTY COMMON_PRIVATE_COMPILE_OPTIONS)
get_property(COMMON_LINK_OPTIONS
        GLOBAL PROPERTY COMMON_PRIVATE_LINK_OPTIONS)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/crt0.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/crt0_init.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/int_vect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tiny_new.cpp
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${COMMON_COMPILE_OPTIONS}
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        ${COMMON_LINK_OPTIONS}
)
