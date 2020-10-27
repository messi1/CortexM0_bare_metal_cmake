#pragma once

namespace util
{
  template<typename reg_addr_type, typename reg_value_type,
           const reg_addr_type address, const reg_value_type value = static_cast<reg_value_type>(0)>

  struct reg_access_static final
  {
    static reg_value_type
                reg_get() { return *reinterpret_cast<volatile reg_value_type*>(address); }

    static void reg_set() { *reinterpret_cast<volatile reg_value_type*>(address)  = value; }
    static void reg_and() { *reinterpret_cast<volatile reg_value_type*>(address) &= value; }
    static void reg_or () { *reinterpret_cast<volatile reg_value_type*>(address) |= value; }
    static void reg_not() { *reinterpret_cast<volatile reg_value_type*>(address) &= reg_value_type(~value); }
    template<const reg_value_type mask_value>
    static void reg_msk() { *reinterpret_cast<volatile reg_value_type*>(address) = reg_value_type(reg_value_type(reg_get() &
                                    reg_value_type(~mask_value)) | reg_value_type(value & mask_value)); }

    static void bit_set() { *reinterpret_cast<volatile reg_value_type*>(address) |= static_cast<reg_value_type>(1ULL << value); }
    static void bit_clr() { *reinterpret_cast<volatile reg_value_type*>(address) &= static_cast<reg_value_type>(~static_cast<reg_value_type>(1ULL << value)); }
    static void bit_not() { *reinterpret_cast<volatile reg_value_type*>(address) ^= static_cast<reg_value_type>(1ULL << value); }
    static bool bit_get() {
        return (static_cast<volatile reg_value_type>(reg_get() & static_cast<reg_value_type>(1ULL << value)) != static_cast<reg_value_type>(0U));
    }
  };
}

