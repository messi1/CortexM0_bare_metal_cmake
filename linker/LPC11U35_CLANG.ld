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
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x10000 /* 64K for LPC11U35 */
    RAM (rwx)  : ORIGIN = 0x10000000, LENGTH = 0x2000  /*  8K for LPC11U3x */
}

/* gcc: extern declaration so that the value appears correctly for the LPC checksum calculation */
ENTRY(__my_startup)

INCLUDE "cortexM0_plus.ld"

/* Calculate the usercode checksum as per the LPC11uxx user manual: UM10462, chapter 20.7. page 375
 *
 * The reserved ARM Cortex-M0 exception vector location 7 (offset 0x0000 001C in the
 * vector table) should contain the 2’s complement of the check-sum of table entries 0
 * through 6. This causes the checksum of the first 8 table entries to be 0. The bootloader
 * code checksums the first 8 locations in sector 0 of the flash. If the result is 0, then
 * execution control is transferred to the user code.
 */

SECTIONS
{
    LPC_CHECKSUM = 0 - ( __initial_stack_pointer
                         + ABSOLUTE(__my_startup)
                         + ABSOLUTE(__nmi_handler)
                         + ABSOLUTE(__hard_fault_handler)
                         + (0) /* No handler registered in the interupt vector table */
                         + (0) /* No handler registered in the interupt vector table */
                         + (0) /* No handler registered in the interupt vector table */
                         );
}
