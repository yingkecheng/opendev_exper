led.bin: led.s
	arm-linux-gnuabihf-gcc -g -c led.s -o led.o
	arm-linux-gnuabihf-ld -Ttext 0x87800000 led.o -o led.elf
	arm-linux-gnuabihf-objcopy -O binary -S -g led.elf led.bin
	arm-linux-gnuabihf-objdump -D led.elf > led.dis

clean:
	rm -rf *.o led.bin led.elf led.dis
