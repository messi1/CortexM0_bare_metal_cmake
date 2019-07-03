cmake_minimum_required(VERSION 3.13)

add_executable(test_${PROJECT_NAME})

target_sources(${PROJECT_NAME}Test
        PRIVATE
#                ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_compile_options(${PROJECT_NAME}Test
	PRIVATE
)

target_compile_definitions(${PROJECT_NAME}Test
	PRIVATE
)

target_link_options(${PROJECT_NAME}Test
        PRIVATE
)

target_link_libraries(${PROJECT_NAME}Test
        PRIVATE
)

target_include_directories(${PROJECT_NAME}Test
        PRIVATE
)

