/* 
  Reserve some space for the stack. This is used to check if global variables + stack exceed RAM size.
  If -Wl,--gc-sections is used, then also define -Wl,--undefined=arm_stack_area to keep the variable in RAM.
  The name of the variable (here: arm_stack_area) does not matter.

  Heap (=dynamic memory allocation) is not supported
*/
#ifndef __STACK_SIZE
#define __STACK_SIZE 0x100
#endif
unsigned char arm_stack_area[__STACK_SIZE] __attribute__ ((section(".stack"))) __attribute__ ((aligned(8)));


/*=======================================================================*/
/* isr system procedures */

/* make the top of the stack known to the c++ compiler, value will be calculated by the linker script */
void __StackTop(void);
