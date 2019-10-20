typedef void (*ptr_func_t)();

// main application
extern void main_app();

// location of these variables is defined in linker script
extern unsigned long __data_start;
extern unsigned long __data_end;
extern unsigned long __data_load;

extern unsigned long __bss_start;
extern unsigned long __bss_end;

extern unsigned long __heap_start;

extern ptr_func_t __preinit_array_start[];
extern ptr_func_t __preinit_array_end[];

extern ptr_func_t __init_array_start[];
extern ptr_func_t __init_array_end[];

extern ptr_func_t __fini_array_start[];
extern ptr_func_t __fini_array_end[];



/**     
  Loop to copy data from read only memory to RAM. The ranges
  of copy from/to are specified by following symbols evaluated in 
  linker script.
  __etext: End of code section, i.e., begin of data sections to copy from.
  __data_start__/__data_end__: RAM address range that data should be
  copied to. Both must be aligned to 4 bytes boundary.  
*/
void copy_data() {
  extern unsigned long __data_start__[];
  extern unsigned long __data_end__[];
  extern unsigned long __etext[];
  unsigned long *ptr   = __etext;
  unsigned long *start = __data_start__;
  unsigned long *end   = __data_end__;

  while( start < end )
  {
    *start = *ptr;
    start++;
    ptr++;
  }
}


/**
  Loop to zero out BSS section, which uses following symbols
  in linker script:
  __bss_start__: start of BSS section. Must align to 4
  __bss_end__: end of BSS section.     Must align to 4
*/
void zero_bss()
{
  extern unsigned long __bss_start__[];
  extern unsigned long __bss_end__[];
  unsigned long *ptr = __bss_start__;
  unsigned long *end = __bss_end__;

  while( ptr < end )
  {
    *ptr = 0;
    ptr++;
  }
}

/** Fill heap memory
 */
void fill_heap(unsigned fill=0x45455246) {
    unsigned long *dst = &__heap_start;
    unsigned long *msp_reg;

    __asm__("mrs %0, msp\n" : "=r" (msp_reg) );

    while (dst < msp_reg) {
        *dst++ = fill;
    }
}

/** Call constructors for static objects
 */
void static_obj_ctors() {
    auto array = __preinit_array_start;
    while (array < __preinit_array_end) {
        (*array)();
        array++;
    }

    array = __init_array_start;
    while (array < __init_array_end) {
        (*array)();
        array++;
    }
}

/** Call destructors for static objects
 */
void static_obj_dtors() {
    auto array = __fini_array_start;
    while (array < __fini_array_end) {
        (*array)();
        array++;
    }
}


[[ noreturn ]] void Reset_Handler()
{
  copy_data();
  
  zero_bss();

  fill_heap();

  static_obj_ctors();
  // Call main procedure  
  main_app();
  static_obj_dtors();
  
  // finished, do nothing
  while (true);
}
