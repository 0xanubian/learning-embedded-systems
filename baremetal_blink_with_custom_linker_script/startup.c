#include <stdint.h>

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;

int main(void);

void Reset_Handler(void) {
    uint32_t *src = &_sidata, *dst = &_sdata;
    while (dst < &_edata) *dst++ = *src++;
    for (dst = &_sbss; dst < &_ebss; ) *dst++ = 0;
    main();
    while (1);
}

void Default_Handler(void) { while (1); }

__attribute__((section(".isr_vector"), used))
const void *vectors[] = {
    &_estack,          // initial SP
    Reset_Handler,     // reset
    Default_Handler,   // NMI
    Default_Handler,   // HardFault
    // add the rest as you go (see PM0214 / RM0383 vector table)
};
