extern "C"
{
    void __hard_fault_handler() __attribute__((interrupt));
    void __nmi_handler() __attribute__((used, noinline));
}

//void __nmi_handler()
//{
//    while (true);
//}

/////* "__hard_fault_handler" is used in the ld script to calculate the checksum for
//// * LPC11Uxx */
void __hard_fault_handler()
{
  while (true);
}

