MEMORY
{
    SRAM (RWX) : ORIGIN = 0x20000000, LENGTH = 64K
    FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 256K
}

ENTRY(Reset_Handler)
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .isr_vector : { KEEP(*(.isr_vector)) } > FLASH
    .text :
    {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH
    
    _sidata = LOADADDR(.data);
    
    .data :
    {
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT > FLASH

    .bss : 
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM
}
