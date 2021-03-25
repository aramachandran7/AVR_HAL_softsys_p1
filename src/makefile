
FILENAME = ./examples/timer_sample
DEVICE = atmega16m1
CLOCK = 4000000UL
BAUD = 115200
PROGRAMMER = arduino
PORT = /dev/cu.usbserial

COMPILE = avr-gcc -Wall -Werror -Os -g -std=gnu99 -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) # -lm

TIMER_LIB = ./lib/libs/timer/timer_library
TIMER_DR = ./lib/AVR_drivers/timer/AVR_timer_driver
ENV_CONST = ./lib/ENV_CONSTANTS.h

timer_driver.o: $(TIMER_DR).c $(TIMER_DR).h $(ENV_CONST)
	$(COMPILE) -c $(TIMER_DR).c $(ENV_CONST) -o $(TIMER_DR).o
	
timer_library.o: $(TIMER_LIB).c $(TIMER_LIB).h $(ENV_CONST)
	$(COMPILE) -c $(TIMER_LIB).c $(ENV_CONST) -o $(TIMER_DR).o


compile: timer_library.o timer_driver.o
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o 
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --muc=$(DEVICE) $(FILENAME).elf


upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean: 
	rm $(TIMER_DR).o
	rm $(TIMER_LIB).o
	rm $(FILENAME).o 
	rm $(FILENAME).elf
	rm $(FILENAME).hex 


# help:
# 	@echo 'Help details:'
# 	@echo 'hex: compile hex file'
# 	@echo 'flash: install hex file'
# 	@echo 'program: compile hex and install'


# hex:
# 	avr-gcc -Os -g -DF_CPU=4000000UL -mmcu=atmega16m1 -std=gnu99 -Wall- Werror -lm -o  led_flash.c
# 	avr-gcc -DF_CPU=8000000 -mmcu=attiny85 -o led_flash.elf led_flash.o
# 	avr-objcopy -O ihex led_flash.elf led_flash.hex
# 	rm led_flash.o
# 	rm led_flash.elf



default: compile 