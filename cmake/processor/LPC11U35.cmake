target_sources(${PROJECT_NAME}
        PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/handlers_cm.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/stack.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/startup.cpp
)

target_compile_options(${PROJECT_NAME}
        PRIVATE
                -mthumb
                -mcpu=cortex-m0plus
                -mtune=cortex-m0plus   # https://gcc.gnu.org/onlinedocs/gcc-4.9.4/gcc/ARM-Options.html
                -march=armv6-m         # Check https://de.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M0+
)

#target_compile_definitions(${PROJECT_NAME}
#        PRIVATE
#		# Add your processor specific compile definitions
#)

target_include_directories(${PROJECT_NAME}
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_options(${PROJECT_NAME}
        PRIVATE
                $<$<CXX_COMPILER_ID:Clang>:-T ${CMAKE_SOURCE_DIR}/lib/linker/lpc11u35_clang.ld>
                $<$<CXX_COMPILER_ID:GNU>:-T ${CMAKE_SOURCE_DIR}/lib/linker/lpc11u35_gcc.ld>
)

#target_link_libraries(${PROJECT_NAME}
#        PRIVATE
#		# Add your processor specific libs
#)
