#include "cstddef"

#include "util/reg_access_dynamic.h"
#include "util/reg_access_static.h"
#include "util/port_pin.h"

//#include <type_traits>


// application
int main_app()
{
//    util::reg_access_static<unsigned int, unsigned int, 0x48000018, 0x5>::bit_not();
//    util::reg_access_dynamic<unsigned int, unsigned int>::bit_not(0x48000018, 0x5);
//    util::port_pin<std::uint32_t, std::uint32_t, 0x48000018, static_cast<std::uint32_t>(9)>::set_direction_output();

    // configure PIO_7 pin function
    (*(volatile unsigned int *)(0x40044050)) = 0;

    // configure GPIO direction
    (*(volatile unsigned int *)(0x50002000)) |= (1 << 20);

    while(1) {

        // set LED GPIO low
        (*(volatile unsigned int *)(0x50002280)) = (1 << 20);
        for (int i = 0; i < 100000; ++i) __asm__("nop");

        // set LED GPIO high
        (*(volatile unsigned int *)(0x50002200)) = (1 << 20);
        for (int i = 0; i < 100000; ++i) __asm__("nop");

        // Toggle LED (low)
        (*(volatile unsigned int *)(0x50002300)) = (1 << 20);
        for (int i = 0; i < 300000; ++i) __asm__("nop");

        // Toggle LED (high)
        (*(volatile unsigned int *)(0x50002300)) = (1 << 20);
        for (int i = 0; i < 300000; ++i) __asm__("nop");

    }

    return 0;
}
