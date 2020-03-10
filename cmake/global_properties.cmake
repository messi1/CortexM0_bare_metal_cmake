set_property(GLOBAL
    PROPERTY COMMON_PRIVATE_COMPILE_OPTIONS
        $<$<CONFIG:Release>:-O0>
        $<$<CONFIG:Debug>:-Og>
        $<$<COMPILE_LANGUAGE:C>:-std=c11>
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions> # Disable exception handling.
        $<$<COMPILE_LANGUAGE:CXX>:-fno-unwind-tables> # it suppresses the generation of static unwind tables
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti> # Disable generation of information about every class with virtual functions for use by the C++ run-time type identification features
        $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit> # will use .fini for static global destructors and atexit() for static destructors in functions
        $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics> # Do not emit the extra code to use the routines specified in the C++ ABI for thread-safe initialization of local statics. You can use this option to reduce code size slightly in code that doesn’t need to be thread-safe.
        $<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual> # Warn when a function declaration hides virtual functions from a base class.
        $<$<CXX_COMPILER_ID:GNU>:-fstrict-volatile-bitfields> # This option should be used if accesses to volatile bit-fields should use a single access of the width of the field’s type, aligned to a natural alignment if possible.
        $<$<CXX_COMPILER_ID:GNU>:-Wlogical-op> # Warn about suspicious uses of logical operators in expressions.
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-override> # Warn about overriding virtual functions that are not marked with the override keyword.
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-types> # Warn about types with virtual methods where code quality would be improved
        $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-methods> # Warn about virtual methods where code quality would be improved if the method were declared with the C++11 final specifier
        $<$<CXX_COMPILER_ID:GNU>:-Wstringop-overflow> # Warn for calls to string manipulation functions such as memcpy and strcpy that are determined to overflow the destination buffer
        -Wuninitialized # Warn if an automatic variable is used without first being initialized
        ${COMPILE_WARNING_AS_ERROR} #-Werror # Make all warnings into errors
        -Wall # This enables all the warnings about constructions that some users consider questionable
        -Wextra # This enables some extra warning flags that are not enabled by ‘-Wall'
        -Wcast-align # Warn whenever a pointer is cast such that the required alignment of the target is increased.
        -Wconversion # Warn for implicit conversions that may alter a value.
        -Wsign-conversion # Warn for implicit conversions that may change the sign of an integer value
        -Wold-style-cast # Warn if an old-style (C-style) cast to a non-void type is used within a C++ program.
        -Wshadow # Warn whenever a local variable or type declaration shadows another variable, parameter, type, class member (in C++), or whenever a built-in function is shadowed
        -Wpedantic # Issue all the warnings demanded by strict ISO C and ISO C++
        -pedantic-errors # Give an error whenever the base standard requires a diagnostic
        -ffunction-sections # Place each function or data item into its own section in the output file if the target supports arbitrary sections.
        -fdata-sections # Place each function or data item into its own section in the output file if the target supports arbitrary sections.
        -fno-threadsafe-statics # Do not emit the extra code to use the routines specified in the C++ ABI for thread-safe initialization of local statics.
        -ffreestanding # directs the compiler to limit this program to only those features available in the freestanding environment.        
        -nodefaultlibs
        -nostdlib
#       -fno-gc
#       -fno-invariants
#       -fno-moduleinfo
#       -fno-string-switch
#       -fno-utf-support #(foreach over utf strings)
#       -fno-boundscheck
#       -fno-switch-error
)

set_property(GLOBAL
        PROPERTY COMMON_PRIVATE_LINK_OPTIONS
        $<$<CXX_COMPILER_ID:CLANG>:-fuse-ld=lld>
        -fno-exceptions
        -nodefaultlibs
        -nostdlib
        $<$<CXX_COMPILER_ID:GNU>:-nolibc>
)
