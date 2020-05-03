/* Linker script to configure memory regions.
 * Need modifying for a specific board.
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 */

MEMORY
{
    FLASH(rx) : ORIGIN = 0x10001000, LENGTH = 0x10000 /* 64K for XMC-1100 */
    RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 0x4000  /* 16K for XMC-1100 */
}

stack_size = DEFINED(stack_size) ? stack_size : 1024;
no_init_size = 4;

INCLUDE "cortexM0_plus.ld"

