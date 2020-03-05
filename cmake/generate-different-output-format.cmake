# cmake script for generating binary and hex format and for flashing

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(NM_OPT -C -n -S)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(NM_OPT -C -l -n -S)
endif()

add_custom_command(OUTPUT ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)
add_custom_command(OUTPUT ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)
add_custom_command(OUTPUT ${PROJECT_NAME}.S
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJDUMP} -dS ${PROJECT_NAME}.elf > ${PROJECT_NAME}.S
)
add_custom_command(OUTPUT ${PROJECT_NAME}.sym
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_NM} ${NM_OPT} ${PROJECT_NAME}.elf > ${PROJECT_NAME}.sym
)

add_custom_target(hex
    DEPENDS ${PROJECT_NAME}.hex
)
add_custom_target(bin ALL
    DEPENDS ${PROJECT_NAME}.bin
)
add_custom_target(assembly ALL
    DEPENDS ${PROJECT_NAME}.S
)
add_custom_target(sym
    DEPENDS ${PROJECT_NAME}.sym
)
