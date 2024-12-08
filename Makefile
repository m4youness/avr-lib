#USB_TARGET = /dev/tty.usbmodem11101
USB_TARGET = /dev/tty.usbmodem1101
bin/main.hex: bin/main.elf
	avr-objcopy -O ihex -R .eeprom bin/main.elf bin/main.hex

bin/main.elf: bin/main.o
	avr-gcc -mmcu=atmega328p -o bin/main.elf bin/main.o

bin/main.o: main.c
	avr-gcc -c -mmcu=atmega328p -Os -o bin/main.o main.c

flash: bin/main.hex
	avrdude -p atmega328p -c arduino -P $(USB_TARGET) -b 115200 -U flash:w:bin/main.hex

clean:
	rm -f bin/main.o bin/main.elf bin/main.hex

