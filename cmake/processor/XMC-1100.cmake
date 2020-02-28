
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
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

add_custom_target(Linkerscripts SOURCES
                  ${CMAKE_SOURCE_DIR}/lib/linker/XMC-1100.ld
                  ${CMAKE_SOURCE_DIR}/lib/linker/cortexM0_plus.ld
)

#target_link_libraries(${PROJECT_NAME}
#        PRIVATE
#		# Add your processor specific libs
#)
