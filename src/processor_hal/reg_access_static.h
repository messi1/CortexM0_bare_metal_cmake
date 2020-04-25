#pragma once

namespace register
{
  template<typename register_address, typename register_value,
           const register_address address, const register_value value = static_cast<register_value>(0)>

  struct access_static final
  {
    static register_value
                reg_get() { return *reinterpret_cast<volatile register_value*>(address); }

    static void reg_set() { *reinterpret_cast<volatile register_value*>(address)  = value; }
    static void reg_and() { *reinterpret_cast<volatile register_value*>(address) &= value; }
    static void reg_or () { *reinterpret_cast<volatile register_value*>(address) |= value; }
    static void reg_not() { *reinterpret_cast<volatile register_value*>(address) &= register_value(~value); }
    template<const register_value mask_value>
    static void reg_msk() { *reinterpret_cast<volatile register_value*>(address) = register_value(register_value(reg_get() &
                                    register_value(~mask_value)) | register_value(value & mask_value)); }

    static void bit_set() { *reinterpret_cast<volatile register_value*>(address) |= static_cast<register_value>(1ULL << value); }
    static void bit_clr() { *reinterpret_cast<volatile register_value*>(address) &= static_cast<register_value>(~static_cast<register_value>(1ULL << value)); }
    static void bit_not() { *reinterpret_cast<volatile register_value*>(address) ^= static_cast<register_value>(1ULL << value); }
    static bool bit_get() { return (static_cast<volatile register_value>(reg_get() & static_cast<register_value>(1ULL << value)) != static_cast<register_value>(0U)); }
  };
}

