/*
 * we first need to enable the clock for our desired port. In my case I am 
 * using port B pin 13 so i need to enable its clock signal
 *
 * RCC base is at 0x40023800
 * RCC AHB1 peripheral clock enable register (RCC_AHB1ENR) is at offset 0x30
 * and the bit for port B is at bit 1 (0 port clock is disabled, 1 its enabled)
 *
 * GPIOB base is at 0x40020400
 * GPIOx_MODER is at offset 0x00
 * GPIOx_BSSR is at offset 0x18
 *
 *
 * GPIO MODER sets the fundamental operation mode of each GPIO pin. It uses 2
 * bits per pin (so 16 pins per port). And bits (01) is GPO mode.
 *
 * GPIO BSRR is Bit Set/Reset Register. it is used to set and reset output pin
 * state. Bit Allocation: A 32-bit register split into two 16-bit halves:
 * Lower 16 bits (0–15): Writing a 1 to bit k sets corresponding pin k to HIGH (1).
 * Writing a 0 has no effect.
 * Higher 16 bits (16–31): Writing a 1 to bit k + 16 resets/clears corresponding 
 * pin k to LOW (0). Writing a 0 has no effect.
 */

#include <stdint.h>

#define RCC_AHB1ENR     (volatile uint32_t *)(0x40023800 + 0x30)
#define GPIOB_MODER     (volatile uint32_t *)(0x40020400)
#define GPIOB_BSRR      (volatile uint32_t *)(0x40020400 + 0x18)

void delay() {
    for (int volatile i = 0; i < 500000; i++);
}

int main() {
    // enables the clock signal for port B
    *RCC_AHB1ENR |= (1u << 1);
    
    // set moder to output mode
    *GPIOB_MODER &= ~(3u << 26);    // first clear it
    *GPIOB_MODER |= (1u << 26);     // then set it

    while (1) {
        // not set and reset the port's output to make the led blink
        *GPIOB_BSRR = (1u << (13 + 16));   // resets the pin: LED on
        delay();
        *GPIOB_BSRR = (1u << 13);          // sets the pin: LED off
        delay();
    }
}
