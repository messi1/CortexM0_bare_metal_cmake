extern void __StackTop();
extern void Reset_Handler();


/* make the checksum known to the c compiler, value will be calculated by the linker script */
void LPC_checksum(void);

/*=======================================================================*/
/* isr vector */
/* see page 445 of the LPC11U3x user manual */ 
/* see also enum LPC11UXX_IRQn in isr/cmsis_11uxx.h */

typedef void (*isr_handler_t)();
typedef void (*ptr_func_t)();

// Undefined handler is pointing to this function, this stop MCU.
// This function name must by not mangled, so must be C,
// because alias("..") is working only with C code
extern "C" void __stop() { while (true); }

// Handlers for Cortex-M core.
// These handler are with attribute 'weak' and can be overwritten
// by non-weak function, default is __stop() function
//__attribute__((weak, alias("__stop"))) void Reset_Handler();
__attribute__((weak, alias("__stop"))) void NMI_Handler();
__attribute__((weak, alias("__stop"))) void HardFault_Handler();
__attribute__((weak, alias("__stop"))) void MEMMANAGE_handler();
__attribute__((weak, alias("__stop"))) void BUSFAULT_handler();
__attribute__((weak, alias("__stop"))) void USAGEFAULT_handler();
__attribute__((weak, alias("__stop"))) void SVCALL_handler();
__attribute__((weak, alias("__stop"))) void DEBUGMONITOR_handler();
__attribute__((weak, alias("__stop"))) void PENDSV_handler();
__attribute__((weak, alias("__stop"))) void SysTick_Handler();

// Dummy handler (for unused vectors)
__attribute__((weak, alias("__stop"))) void DUMMY_handler();

//__attribute__ ((section(".isr_vector"))) isr_handler_t __isr_vectors[]  __attribute__ ((aligned(4)))= 
__attribute__((section(".isr_vector"), used)) ptr_func_t __isr_vectors[] = {
  __StackTop,			/* 0x00: Top of Stack, calculated by the linker script */
  Reset_Handler,		/* 0x04: Reset Handler, DO NOT CHANGE THE ISR NAME (used for LPC_checksum calculation) */
  NMI_Handler,			/* 0x08: NMI Handler, DO NOT CHANGE THE ISR NAME (used for LPC_checksum calculation) */
  HardFault_Handler,            /* 0x0c: Hard Fault Handler, DO NOT CHANGE THE ISR NAME (used for LPC_checksum calculation) */
  0,				/* 0x10: Reserved, must be 0 */
  0,				/* 0x14: Reserved, must be 0 */
  0,				/* 0x18: Reserved, must be 0 */
  LPC_checksum,			/* 0x1c: Checksum, calculated by the linker script or the flash utility */
  0,                            /* Reserved */
  0,                            /* Reserved */
  0,                            /* Reserved */
  SVCALL_handler,               /* SVCall Handler */
  0,                            /* Reserved */
  0,                            /* Reserved */
  PENDSV_handler,               /* PendSV Handler */
  SysTick_Handler,         	/* SysTick Handler */            
  
  0,                                /* PIN_INT0_IRQn                 = 0,		 Pin Interrupt 0 */
  0,                                /* PIN_INT1_IRQn                 = 1,		 Pin Interrupt 1 */
  0,                                /* PIN_INT2_IRQn                 = 2,		 Pin Interrupt 2 */
  0,                                /* PIN_INT3_IRQn                 = 3,		 Pin Interrupt 3 */
  0,                                /* PIN_INT4_IRQn                 = 4,		 Pin Interrupt 4 */
  0,                                /* PIN_INT5_IRQn                 = 5,		 Pin Interrupt 5 */
  0,                                /* PIN_INT6_IRQn                 = 6,		 Pin Interrupt 6 */
  0,                                /* PIN_INT7_IRQn                 = 7,		Pin Interrupt 7 */
  0,                                /* GINT0_IRQn                     = 8,		GPIO GROUP 0 interrupt */
  0,                                /* GINT1_IRQn                    = 9,			GPIO GROUP 1 interrupt */
  0,                                /* Reserved10_IRQn               = 10,		Reserved Interrupt */
  0,                                /* Reserved11_IRQn               = 11, */
  0,                                /* Reserved12_IRQn               = 12, */
  0,                                /* Reserved13_IRQn               = 13, */
  0,                                /* SSP1_IRQn                     = 14,		SSP1 Interrupt */
  0,                                /* I2C0_IRQn                     = 15,		 	I2C Interrupt */
  0,                                /* TIMER_16_0_IRQn               = 16,		 16-bit Timer0 Interrupt                          */
  0,                                /* TIMER_16_1_IRQn               = 17,		 16-bit Timer1 Interrupt                          */
  0,                                /* TIMER_32_0_IRQn               = 18,		 32-bit Timer0 Interrupt                          */
  0,                                /* TIMER_32_1_IRQn               = 19,		 32-bit Timer1 Interrupt                          */
  0,                                /* SSP0_IRQn                     = 20,		 SSP0 Interrupt                                   */
  0,                                /* UART0_IRQn                    = 21,		 UART Interrupt                                   */
  0,                                /* USB0_IRQn                     = 22,		 USB IRQ interrupt                                */
  0,                                /* USB0_FIQ_IRQn                 = 23,		 USB FIQ interrupt                                */
  0,                                /* ADC_IRQn                      = 24,		 A/D Converter Interrupt                          */
  0,                                /* WDT_IRQn                      = 25,		 Watchdog timer Interrupt                         */
  0,                                /* BOD_IRQn                      = 26,		 Brown Out Detect(BOD) Interrupt                  */
  0,                                /* FMC_IRQn                      = 27,		 Flash Memory Controller Interrupt                */
  0,                                /* RESERVED28_IRQn               = 28, */
  0,                                /* RESERVED29_IRQn               = 29, */
  0,                                /* USB_WAKEUP_IRQn               = 30,		 USB wake-up interrupt Interrupt                  */
  0                                /* IOH_IRQn                      = 31,		 I/O Handler IRQ (Only for LPC11U37)              */
};

