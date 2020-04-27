#include "cstddef"

#include "util/reg_access_dynamic.h"
#include "util/reg_access_static.h"
#include "util/port_pin.h"

//#include <type_traits>


// application
int main_app()
{
    util::reg_access_static<unsigned int, unsigned int, 0x48000018, 0x5>::bit_not();
    util::reg_access_dynamic<unsigned int, unsigned int>::bit_not(0x48000018, 0x5);
    util::port_pin<std::uint32_t, std::uint32_t, 0x48000018, static_cast<std::uint32_t>(9)>::set_direction_output();
    return 0;
}
