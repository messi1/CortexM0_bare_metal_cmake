
namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup() __attribute__((used, noinline));
extern "C" void NMI_Handler() __attribute__((used, noinline));
extern "C" void HardFault_Handler() __attribute__((used, noinline));

void NMI_Handler(){}
void HardFault_Handler(){}

extern "C" /* make the checksum known to the c compiler, value will be calculated by the linker script */
void LPC_checksum(void);

void __my_startup()
{
  // Load the stack pointer.
  // The stack pointer is automatically loaded from
  // the base position of the interrupt vector table.
  // So do nothing here.

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Jump to main (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  // Catch an unexpected return from main.
  for(;;)
  {
  }
}
