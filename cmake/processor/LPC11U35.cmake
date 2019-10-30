
#target_sources(${PROJECT_NAME}
#        PRIVATE
# Add your processor specific source files
#)

target_compile_options(${PROJECT_NAME}
        PRIVATE
                -mthumb
                -mcpu=cortex-m0
                -mtune=cortex-m0   # https://gcc.gnu.org/onlinedocs/gcc-4.9.4/gcc/ARM-Options.html
                -march=armv6-m     # Check https://de.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M0
)

#target_compile_definitions(${PROJECT_NAME}
#        PRIVATE
#		# Add your processor specific compile definitions
#)

target_include_directories(${PROJECT_NAME}
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
)

target_link_options(${PROJECT_NAME}
        PRIVATE
            -L ${CMAKE_SOURCE_DIR}/lib/linker/
            -T ${CMAKE_SOURCE_DIR}/lib/linker/lpc11u35.ld
)

add_custom_target(Linkerscripts SOURCES
                  lib/linker/lpc11u35.ld
                  lib/linker/cortexM0_plus.ld
)

#target_link_libraries(${PROJECT_NAME}
#        PRIVATE
#		# Add your processor specific libs
#)
