#include "cstddef"

#include "util/reg_access_dynamic.h"
#include "util/reg_access_static.h"
#include "util/port_pin.h"

//#include <type_traits>

//#define CODE_IN_C 1
// application
int main_app()
{
//    util::reg_access_static<unsigned int, unsigned int, 0x48000018, 0x5>::bit_not();
//    util::reg_access_dynamic<unsigned int, unsigned int>::bit_not(0x48000018, 0x5);
//    util::port_pin<std::uint32_t, std::uint32_t, 0x48000018, static_cast<std::uint32_t>(9)>::set_direction_output();

#ifdef CODE_IN_C
    // configure PIO_7 pin function
    (*(volatile unsigned int *)(0x40044050)) = 0;

    // configure GPIO direction
    (*(volatile unsigned int *)(0x50002000)) |= (1 << 20);
#else
    // configure PIO_7 pin function
    util::reg_access_static<unsigned int, unsigned int, 0x4004'4050, 0x0>::reg_set();

    // configure GPIO direction
    //util::reg_access_static<unsigned int, unsigned int, 0x5000'2000, (1 << 20)>::reg_or();
    util::port_pin<unsigned int, unsigned int, 0x5000'2000, (1 << 20)>::set_direction_output();
#endif

    while(1) {
#ifdef CODE_IN_C
        // set LED GPIO low
        (*(volatile unsigned int *)(0x5000'2280)) = (1 << 20);
        for (int i = 0; i < 100000; ++i) __asm__("nop");

        // set LED GPIO high
        (*(volatile unsigned int *)(0x5000'2200)) = (1 << 20);
        for (int i = 0; i < 100000; ++i) __asm__("nop");

        // Toggle LED (low)
        (*(volatile unsigned int *)(0x5000'2300)) = (1 << 20);
        for (int i = 0; i < 300000; ++i) __asm__("nop");

        // Toggle LED (high)
        (*(volatile unsigned int *)(0x5000'2300)) = (1 << 20);
        for (int i = 0; i < 300000; ++i) __asm__("nop");
#else


        // set LED GPIO low
        util::reg_access_static<unsigned int, unsigned int, 0x5000'2280, (1 << 20)>::reg_set();
        for (int i = 0; i < 100000; ++i) __asm__("nop");

        // set LED GPIO high
        util::reg_access_static<unsigned int, unsigned int, 0x5000'2200, (1 << 20)>::reg_set();
        for (int i = 0; i < 100000; ++i) __asm__("nop");

        // Toggle LED (low)
        util::reg_access_static<unsigned int, unsigned int, 0x5000'2300, (1 << 20)>::reg_set();
        for (int i = 0; i < 300000; ++i) __asm__("nop");

        // Toggle LED (high)
        util::reg_access_static<unsigned int, unsigned int, 0x5000'2300, (1 << 20)>::reg_set();
        for (int i = 0; i < 300000; ++i) __asm__("nop");
#endif
    }

    return 0;
}
