CROSS_COMPILE	?= arm-linux-gnueabihf-
TARGET			?= uart

CC				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY			:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump

LIBPATH			:= -lgcc -L /usr/lib/gcc-cross/arm-linux-gnueabihf/11

INCDIRS			:= imx6ul \
				bsp/clk \
			   	bsp/led \
			   	bsp/delay \
			   	bsp/beep \
			   	bsp/gpio \
			   	bsp/key	\
				bsp/exit \
				bsp/int \
				bsp/uart

SRCDIRS			:= project \
				bsp/clk \
				bsp/led \
				bsp/delay \
				bsp/beep \
				bsp/gpio \
				bsp/key \
				bsp/exit \
				bsp/int \
				bsp/uart

INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR		:= $(notdir $(SFILES))
CFILENDIR		:= $(notdir $(CFILES))

SOBJS			:= $(patsubst %, obj/%, $(SFILENDIR:.s=.o))
COBJS			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS			:= $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)

.PHONY: clean

$(TARGET).bin: $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS): obj/%.o: %.s
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

$(COBJS): obj/%.o: %.c
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

clean:
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).dis $(SOBJS) $(COBJS)
