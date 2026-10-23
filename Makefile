CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
SIZE = arm-none-eabi-size
OBJCOPY = arm-none-eabi-objcopy

JLINK = jlink

RM = rm -rf

TARGET = flash
DIR_BUILD = Build

MCU = -mcpu=cortex-m0 -mthumb -mfloat-abi=soft
CFLAGS = -c $(MCU) -std=gnu11 -DSTM32F072xB -Wall -O0 -g3 -ffunction-sections -fdata-sections
LDFLAGS = $(MCU) -TDrivers/Device/linker/STM32F072.ld --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections

INCLUDES =	-IDrivers/Device/cmsis/Inc \
			-IDrivers/Inc

OBJS += $(DIR_BUILD)/main.o
OBJS += $(DIR_BUILD)/startup.o
OBJS += $(DIR_BUILD)/syscalls.o

DRIVERS += $(DIR_BUILD)/driver_gpio.o
DRIVERS += $(DIR_BUILD)/driver_systick.o
DRIVERS += $(DIR_BUILD)/driver_uart.o

PREREQ = $(DIR_BUILD)/

all: $(PREREQ) $(DIR_BUILD)/$(TARGET).elf

$(PREREQ):
	mkdir $(PREREQ)

$(DIR_BUILD)/%.o: App/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o App/Src/$(*).c

$(DIR_BUILD)/%.o: Drivers/Device/startup/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o Drivers/Device/startup/$(*).c

$(DIR_BUILD)/%.o: Drivers/Device/system/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o Drivers/Device/system/$(*).c

$(DIR_BUILD)/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o Drivers/Src/$(*).c

$(DIR_BUILD)/$(TARGET).elf: $(OBJS) $(DRIVERS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(DIR_BUILD)/$(TARGET).elf $(DIR_BUILD)/$(TARGET).bin
	$(SIZE) $(DIR_BUILD)/$(TARGET).elf

flash:
	@$(JLINK) -CommanderScript flash.jlink >/dev/null 2>&1 && echo "Flash Finished"

clean:
	$(RM) $(DIR_BUILD)

.PHONY: clean flash