#pragma once

namespace util
{
  template<typename reg_addr_type, typename reg_value_type>


  struct reg_access_dynamic final
  {
    static reg_value_type
                reg_get(const reg_addr_type address) { return *reinterpret_cast<volatile reg_value_type*>(address); }

    static void reg_set(const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address)  = value; }
    static void reg_and(const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) &= value; }
    static void reg_or (const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) |= value; }
    static void reg_not(const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) &= reg_value_type(~value); }
    static void reg_msk(const reg_addr_type address, const reg_value_type value, const reg_value_type mask_value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) = reg_value_type(reg_value_type(reg_get(address) & reg_value_type(~mask_value)) | reg_value_type(value & mask_value)); }

    static void bit_set(const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) |= static_cast<reg_value_type>(1UL << value); }
    static void bit_clr(const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) &= static_cast<reg_value_type>(~static_cast<reg_value_type>(1UL << value)); }
    static void bit_not(const reg_addr_type address, const reg_value_type value)
                        { *reinterpret_cast<volatile reg_value_type*>(address) ^= static_cast<reg_value_type>(1UL << value); }
    static bool bit_get(const reg_addr_type address, const reg_value_type value)
                        { return (static_cast<volatile reg_value_type>(reg_get(address) &
                          static_cast<reg_value_type>(1UL << value)) != static_cast<reg_value_type>(0U)); }
  };
}
