cmake_minimum_required(VERSION 3.13)
include(ExternalProject)

set(protothread_cpp "https://github.com/benhoyt/protothreads-cpp")
message(STATUS "Repository for protothread_cpp: ${protothread_cpp}")

ExternalProject_add(external-protothread_cpp
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/protothread_cpp"
    GIT_REPOSITORY ${protothread_cpp}
    GIT_SHALLOW FALSE
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    BUILD_IN_SOURCE 1

    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/include
    INSTALL_COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/protothread_cpp/src/external-protothread_cpp/Protothread.h ${CMAKE_CURRENT_BINARY_DIR}/include
)

add_library(protothread_cpp::protothread_cpp INTERFACE IMPORTED)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
set_target_properties(protothread_cpp::protothread_cpp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/include)

add_dependencies(protothread_cpp::protothread_cpp external-protothread_cpp)
