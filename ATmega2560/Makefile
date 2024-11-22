# Microcontroller and port configuration
MCU = atmega2560
PORT := $(shell ls /dev/tty.usb* 2>/dev/null | head -n 1)
F_CPU = 16000000UL
BAUD = 115200

# File names
TARGET = main
SRC = $(TARGET).c
OBJ = $(TARGET).o
UART_SRC = UART/uart.c
UART_OBJ = $(UART_SRC:.c=.o)
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
	@echo "Compiling $(SRC)..."
	$(CC) $(CFLAGS) -c $< -o $@
# Compile: Create object file for uart.c
$(UART_OBJ): $(UART_SRC)
	@echo "Compiling $(UART_SRC)..."
	$(CC) $(CFLAGS) -c $< -o $@
# Link: Create ELF file
$(ELF): $(OBJ) $(UART_OBJ)
	@echo "Linking $(OBJ) and $(UART_OBJ) to $@"
	$(CC) $(LDFLAGS) $^ -o $@
# Convert: Create HEX file
$(HEX): $(ELF)
	@echo "Converting $(ELF) to $(HEX)"
	$(OBJCOPY) -O ihex -R .eeprom $< $@
# Upload: Flash HEX file to microcontroller
upload: $(HEX)
	@if [ -z "$(PORT)" ]; then \
		echo "No USB port found! Cannot upload."; \
		exit 1; \
	else \
		echo "Uploading $(HEX) to $(PORT)..."; \
		$(AVRDUDE) -v -p $(MCU) -c wiring -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i; \
	fi
# Check code size
size: $(ELF)
	@echo "Checking code size..."
	$(SIZE) --format=avr --mcu=$(MCU) $<
# Clean up generated files
clean: 
	@echo "Cleaning up...";
	rm -f $(OBJ) $(UART_OBJ) $(ELF) $(HEX)
usb: 
	@if [ -z "$(PORT)" ]; then \
		echo "No USB port found! Cannot upload."; \
		exit 1; \
	else \
		echo "USB port: $(PORT)"; \
	fi
# Phony targets
.PHONY: all upload size clean usb