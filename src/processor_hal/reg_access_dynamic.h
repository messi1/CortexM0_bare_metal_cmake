#pragma once

namespace register
{
  template<typename register_address, typename register_value>


  struct access_dynamic final
  {
    static register_value
                reg_get(const register_address address) { return *reinterpret_cast<volatile register_value*>(address); }

    static void reg_set(const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address)  = value; }
    static void reg_and(const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address) &= value; }
    static void reg_or (const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address) |= value; }
    static void reg_not(const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address) &= register_value(~value); }
    static void reg_msk(const register_address address, const register_value value,
                        const register_value mask_value)                                 { *reinterpret_cast<volatile register_value*>(address) = register_value(register_value(reg_get(address) & register_value(~mask_value)) | register_value(value & mask_value)); }

    static void bit_set(const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address) |= static_cast<register_value>(1UL << value); }
    static void bit_clr(const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address) &= static_cast<register_value>(~static_cast<register_value>(1UL << value)); }
    static void bit_not(const register_address address, const register_value value) { *reinterpret_cast<volatile register_value*>(address) ^= static_cast<register_value>(1UL << value); }
    static bool bit_get(const register_address address, const register_value value) { return (static_cast<volatile register_value>(reg_get(address) & static_cast<register_value>(1UL << value)) != static_cast<register_value>(0U)); }
  };
}
