# Microcontroller and port configuration
MCU = atmega2560
PORT := $(shell ls /dev/tty.usb* 2>/dev/null | head -n 1)
F_CPU = 16000000UL
BAUD = 115200

# File names
TARGET = main
SRC = $(TARGET).c
OBJ = $(TARGET).o
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# AVR tools
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

# Compilation Flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
LDFLAGS = -mmcu=$(MCU)

#Build all: Compile, link, convert to HEX and upload
all: $(HEX) upload
# Compile: Create object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@
# Link: Create ELF file
$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) $< -o $@
# Convert: Create HEX file
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@
# Upload: Flash HEX file to microcontroller
upload: $(HEX)
	@if [ -z "$(PORT)" ]; then \
		echo "No USB port found! Cannot upload."; \
		exit 1; \
	else \
		$(AVRDUDE) -D -v -p $(MCU) -c wiring -P $(PORT) -b $(BAUD) -U flash:w:$<:i; \
	fi
# Check code size
size: $(ELF)
	$(SIZE) --format=avr --mcu=$(MCU) $<
# Clean up generated files
clean: 
	rm -f $(OBJ) $(ELF) $(HEX)
usb: 
	@if [ -z "$(PORT)" ]; then \
		echo "No USB port found! Cannot upload."; \
		exit 1; \
	else \
		echo "USB port: $(PORT)"; \
	fi
# Phony targets
.PHONY: all upload size clean