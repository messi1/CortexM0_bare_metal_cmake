#include <cstddef>
#include <cstdint>

extern std::uintptr_t _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
extern std::uintptr_t _data_begin;     // Start address for the .data section.
extern std::uintptr_t _data_end;       // End address for the .data section.
extern std::uintptr_t _bss_start_;      // Start address for the .bss section.
extern std::uintptr_t _bss_end_;        // End address for the .bss section.

struct ctor_type {
    using function_ptr = auto (*)() -> void;
};

//  extern ctor_type::function_type _ctors_end[];
//  extern ctor_type::function_type _ctors_begin[];
extern ctor_type::function_ptr __init_array_start[];
extern ctor_type::function_ptr __init_array_end[];
extern ctor_type::function_ptr __preinit_array_start[];
extern ctor_type::function_ptr __preinit_array_end[];
extern ctor_type::function_ptr __fini_array_start[];
extern ctor_type::function_ptr __fini_array_end[];

namespace crt
{
  void init_ram();
  void copy_data();
  void zero_bss();
  void init_ctors();
  void init_dtors();
}

void crt::copy_data()
{
    const std::uintptr_t *data_end = &_data_end;
    const std::uintptr_t *rom_src  = &_rom_data_begin;
    std::uintptr_t       *rom_ptr  = &_data_begin;
    while( rom_ptr < data_end )
    {
        *rom_ptr++ = *rom_src++;
    }
}

/** Erase BSS section
 */
void crt::zero_bss()
{
    const std::uintptr_t *bss_end = &_bss_end_;
    std::uintptr_t       *bss_ptr = &_bss_start_;

    while( bss_ptr < bss_end )
    {
        *bss_ptr++ = 0;
    }
}

void crt::init_ram()
{
    copy_data();

    zero_bss();

//  std::copy(static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)),
//            static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)) + size_data,
//            static_cast<      memory_aligned_type*>(static_cast<      void*>(&_data_begin)));

//  // Clear the bss segment.
//  // Note that the bss segment is aligned by 4.
//  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
//            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
//            static_cast<memory_aligned_type>(0U));
}

void crt::init_ctors() {
    //    auto array = _ctors_begin;
    //    while( array < _ctors_end )
    //    {
    //        (*array)();
    //        array++;
    //    }

    int size = __preinit_array_end - __preinit_array_start;
    for (int i = 0; i < size; i++)
    __preinit_array_start[i]();

    size = __init_array_end - __init_array_start;
    for (int i = 0; i < size; i++)
    __init_array_start[i]();

    //    array = __init_array_start;
    //    while( array < __init_array_end )
    //    {
    //        (*array)();
    //        array++;
    //    }
}

void crt::init_dtors()
{
    int size = __fini_array_end - __fini_array_start;
    for (int i = 0; i < size; i++)
    __fini_array_start[i]();

    //    auto array = __fini_array_start;
    //    while( array < __fini_array_end )
    //    {
    //        (*array)();
    //        array++;
    //    }
}
