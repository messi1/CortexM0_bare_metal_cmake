/*gcc attribute:
used:
This attribute, attached to a function, means that code must be emitted for the function even
if it appears that the function is not referenced. This is useful, for example,
when the function is referenced only in inline assembly.
When applied to a member function of a C++ class template,
the attribute also means that the function is instantiated if the class itself is instantiated.

noinline
This function attribute prevents a function from being considered for inlining.
If the function does not have side effects, there are optimizations other than inlining that cause
function calls to be optimized away, although the function call is live.

weak
The weak attribute causes the declaration to be emitted as a weak symbol rather than a global.
This is primarily useful in defining library functions that can be overridden in user code,
though it can also be used with non-function declarations.
Weak symbols are supported for ELF targets, and also for a.out targets when using the GNU assembler and linker.

interrupt
Many GCC back ends support attributes to indicate that a function is an interrupt handler,
which tells the compiler to generate function entry and exit sequences that differ
from those from regular functions.
The exact syntax and behavior are target-specific; refer to the following subsections for detail
*/


extern "C"
{
    void __initial_stack_pointer(); // Symbol defined in the linker script
    void __my_startup() __attribute__((interrupt));
    void __vector_unused_irq() __attribute__((weak, interrupt));
    void __nmi_handler() __attribute__((interrupt));
    void __hard_fault_handler() __attribute__((interrupt));
    void __svc_handler() __attribute__((weak, interrupt));
    void __pend_sv_handler() __attribute__((weak, interrupt));
    void __sys_tick_handler() __attribute__((weak, interrupt));
    void __wdt_handler() __attribute__((weak, interrupt));

    /* "__nmi_handler" is used in the ld script to calculate the checksum for LPC11Uxx */
    void __nmi_handler()
    {
      for (;;) {
        asm volatile("nop");
      }
    }

    /* "__hard_fault_handler" is used in the ld script to calculate the checksum for LPC11Uxx */
    void __hard_fault_handler()
    {
      for (;;) {
        asm volatile("nop");
      }
    }
}

namespace
{
    typedef void (*isr_type)();
    typedef void (*isr_handler_t)();
    typedef void (*ptr_func_t)();
} // namespace

#ifdef LPC11UXX
/* make the checksum known to the c compiler, value will be calculated by the linker script */
extern "C" void LPC_CHECKSUM(void);
#endif

extern "C" const ptr_func_t __isr_vectors[]
    __attribute__((section(".isr_vector"), used)) = {
        __initial_stack_pointer, // 0x0000, initial stack pointer,
        __my_startup,            // 0x0004, reset,
        __nmi_handler,           // 0x0008, nmi exception,
        __hard_fault_handler,    // 0x000C, hard fault exception,
        __vector_unused_irq,     // 0x0010, memory management exception,
        __vector_unused_irq,     // 0x0014, bus fault exception,
        __vector_unused_irq,     // 0x0018, usage fault exception,
#ifdef LPC11UXX
        LPC_CHECKSUM, // LPC processors need a checksum here, otherwise the bootloader wont start.
#else
        __vector_unused_irq, // 0x001C, reserved,
#endif
        __vector_unused_irq, // 0x0020, reserved,
        __vector_unused_irq, // 0x0024, reserved,
        __vector_unused_irq, // 0x0028, reserved,
        __svc_handler,       // 0x002C, svc handler,
        __vector_unused_irq, // 0x0030, reserved,
        __vector_unused_irq, // 0x0034, reserved,
        __pend_sv_handler,   // 0x0038, pending svc,
        __sys_tick_handler,  // 0x003C, system tick handler,
        __vector_unused_irq, // 0x0040, GPIO port 0, pin 0 irq handler,
        __vector_unused_irq, // 0x0044, GPIO port 0, pin 1 irq handler,
        __vector_unused_irq, // 0x0048, GPIO port 0, pin 2 irq handler,
        __vector_unused_irq, // 0x004C, GPIO port 0, pin 3 irq handler,
        __vector_unused_irq, // 0x0050, GPIO port 0, pin 4 irq handler,
        __vector_unused_irq, // 0x0054, GPIO port 0, pin 5 irq handler,
        __vector_unused_irq, // 0x0058, GPIO port 0, pin 6 irq handler,
        __vector_unused_irq, // 0x005C, GPIO port 0, pin 7 irq handler,
        __vector_unused_irq, // 0x0060, GPIO port 0, pin 8 irq handler,
        __vector_unused_irq, // 0x0064, GPIO port 0, pin 9 irq handler,
        __vector_unused_irq, // 0x0068, GPIO port 0, pin 10 irq handler,
        __vector_unused_irq, // 0x006C, GPIO port 0, pin 11 irq handler,
        __vector_unused_irq, // 0x0070, GPIO port 1, pin 0 irq handler,
        __vector_unused_irq, // 0x0074, C_CAN irq handler,
        __vector_unused_irq, // 0x0078, SSP1 irq handler,
        __vector_unused_irq, // 0x007C, I2C irq handler,
        __vector_unused_irq, // 0x0080, 16-bit Timer0 irq handler,
        __vector_unused_irq, // 0x0084, 16-bit Timer1 irq handler,
        __vector_unused_irq, // 0x0088, 32-bit Timer0 irq handler,
        __vector_unused_irq, // 0x008C, 32-bit Timer1 irq handler,
        __vector_unused_irq, // 0x0090, SSP0 irq handler,
        __vector_unused_irq, // 0x0094, UART irq handler,
        __vector_unused_irq, // 0x0098, reserved,
        __vector_unused_irq, // 0x009C, reserved,
        __vector_unused_irq, // 0x00A0, A/D Converter irq handler,
        __wdt_handler,       // 0x00A4, Watchdog timer irq handler,
        __vector_unused_irq, // 0x00A8, Brown Out Detect(BOD) irq handler,
        __vector_unused_irq, // 0x00AC, reserved,
        __vector_unused_irq, // 0x00B0, External Interrupt 3 irq handler,
        __vector_unused_irq, // 0x00B4, External Interrupt 2 irq handler,
        __vector_unused_irq, // 0x00B8, External Interrupt 1 irq handler,
        __vector_unused_irq  // 0x00BC, External Interrupt 0 irq handler,
};
