CFLAGS  = -mcpu=cortex-m4 -mthumb -O0 -g -Wall -ffreestanding
LDFLAGS = -T linker_script.ld -nostartfiles -nostdlib -Wl,-Map=blink.map

blink.elf: main.c startup.c
	arm-none-eabi-gcc $(CFLAGS) $^ $(LDFLAGS) -o $@

flash: blink.elf
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
	  -c "program blink.elf verify reset exit"
