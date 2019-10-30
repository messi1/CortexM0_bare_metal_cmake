/* Linker script to configure memory regions.
 * Need modifying for a specific board.
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 */

MEMORY
{
  /* LPC11U35 User Manual Page 17 */
  FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x10000 /* 64K for LPC11U35 */
  RAM (rwx) : ORIGIN = 0x10000000, LENGTH = 0x2000 /* 8K for LPC11U3x */
}

INCLUDE "cortexM0_plus.ld"

