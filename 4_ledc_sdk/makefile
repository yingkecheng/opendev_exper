CROSS_COMPILE ?= arm-linux-gnueabihf-
NAME		  ?= ledc

GCC			  := $(CROSS_COMPILE)gcc
LD			  := $(CROSS_COMPILE)ld
OBJCOPY		  := $(CROSS_COMPILE)objcopy
OBJDUMP		  := $(CROSS_COMPILE)objdump


OBJS  		  := start.o main.o

$(NAME).bin: $(OBJS)
	$(LD) -Timx6ul.lds -o $(NAME).elf $^
	$(OBJCOPY) -O binary -S $(NAME).elf $@
	$(OBJDUMP) -D -m arm $(NAME).elf > $(NAME).dis

%.o: %.s
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<

%.o: %.c
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o $(NAME).bin $(NAME).elf $(NAME).dis
