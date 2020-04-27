#pragma once
#include <cstdint>
#include "reg_access_static.h"

namespace util
{
  template<typename reg_addr_type, typename reg_value_type,
           const reg_addr_type port, const reg_value_type bit_pos>
  class port_pin
  {
  public:

    static void set_direction_output()
    {
      util::reg_access_static<reg_addr_type, reg_value_type, m_dir_reg, bit_pos>::bit_set();
    }

    static void set_direction_input()
    {
      util::reg_access_static<reg_addr_type, reg_value_type, m_dir_reg, bit_pos>::bit_clr();
    }

    static void set_pin_high()
    {
      // Set the port output value to high.
      util::reg_access_static<reg_addr_type, reg_value_type, m_data_reg, out_val_high>::reg_set();
    }

    static void set_pin_low()
    {
      // Set the port output value to low.
      util::reg_access_static<reg_addr_type, reg_value_type, m_data_reg, out_val_low>::reg_set();
    }

    static bool read_input_value()
    {
      // Read the port input value.
      return static_cast<bool>(
        (util::reg_access_static<reg_addr_type, reg_value_type, m_data_reg>::reg_get() >> bit_pos) & 1);
    }

    static void toggle_pin()
    {
      // Toggle the port output value.
      util::reg_access_static<reg_addr_type, reg_value_type, m_data_reg, bit_pos>::bit_not();
    }

  private:
    static constexpr std::uint32_t m_data_reg = port + (UINT32_C(4) * (1 << bit_pos));
    static constexpr std::uint32_t m_dir_reg = port + UINT32_C(0x8000);

    static constexpr std::uint32_t out_val_high = 1UL << bit_pos;
    static constexpr std::uint32_t out_val_low = 0UL << bit_pos;
  };
}
