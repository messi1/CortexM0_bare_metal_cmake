
namespace crt
{
  void init_ram();
  void init_ctors();
  void init_dtors();
}

// main application
int main_app();

extern "C" void __my_startup()
{
    // Load the stack pointer.
    // The stack pointer is automatically loaded from
    // the base position of the interrupt vector table.
    // So do nothing here.

    // Initialize statics from ROM to RAM.
    // Zero-clear default-initialized static RAM.
    crt::init_ram();

    // Call all static ctor initializations.
    crt::init_ctors();

    // Jump to main (and never return).
//    asm volatile("ldr r3, =main");
//    asm volatile("blx r3");
    main_app();


    // Call all destructors
    crt::init_dtors();

    // Catch an unexpected return from main.
    while(true);
}
