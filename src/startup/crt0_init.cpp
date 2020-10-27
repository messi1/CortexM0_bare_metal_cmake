extern const unsigned int * const _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.s
extern       unsigned int * const _data_begin;     // Start address for the .data section.
extern const unsigned int * const _data_end;       // End address for the .data section.
extern       unsigned int * const _bss_start_;     // Start address for the .bss section.
extern const unsigned int * const _bss_end_;       // End address for the .bss section.

typedef void (*ptr_func_t)();
using function_ptr = void (*)();

extern function_ptr _ctors_end[];
extern function_ptr _ctors_begin[];
extern const function_ptr __init_array_start[];
extern const function_ptr __init_array_end[];
extern const function_ptr __preinit_array_start[];
extern const function_ptr __preinit_array_end[];
extern       function_ptr __fini_array_start[];
extern const function_ptr __fini_array_end[];


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
    const unsigned int *rom_src  = _rom_data_begin;
    unsigned int       *rom_ptr  = _data_begin;
    while( rom_ptr < _data_end )
    {
        *rom_ptr++ = *rom_src++;
    }
}

/** Erase BSS section
 */
void crt::zero_bss()
{
    unsigned int *bss_ptr = _bss_start_;

    while( bss_ptr < _bss_end_ )
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

    size = _ctors_end - _ctors_begin;
    for (int i = 0; i < size; i++)
        _ctors_begin[i]();

    //    array = __init_array_start;
    //    while( array < __init_array_end )
    //    {
    //        (*array)();
    //        array++;
    //    }
}

void crt::init_dtors()
{
//    const int size = __fini_array_end - __fini_array_start;
//    for (int i = 0; i < size; i++)
//        __fini_array_start[i]();

        auto array = __fini_array_start;
        while( array < __fini_array_end )
        {
            (*array)();
            array++;
        }
}
