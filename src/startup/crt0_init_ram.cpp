#include <cstddef>
#include <cstdint>

extern "C"
{
  extern std::uintptr_t _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;     // Start address for the .data section.
  extern std::uintptr_t _data_end;       // End address for the .data section.
  extern std::uintptr_t _bss_start_;      // Start address for the .bss section.
  extern std::uintptr_t _bss_end_;        // End address for the .bss section.
}

namespace crt
{
  void init_ram();
  void copy_data();
  void zero_bss();
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
