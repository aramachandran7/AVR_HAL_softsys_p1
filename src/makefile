FILENAME = ./examples/timer_sample
FILENAME2 = ./examples/UART_sample

DEVICE = atmega16m1
CLOCK = 4000000UL
BAUD = 115200
PROGRAMMER = arduino
PORT = /dev/cu.usbserial

COMPILE = avr-gcc -Wall -Werror -Os -g -std=gnu99 -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) # -lm

TIMER_LIB = ./lib/libs/timer/timer_library
TIMER_DR = ./lib/AVR_drivers/timer/AVR_timer_driver

UART_LIB = ./lib/libs/UART/UART_library
UART_DR = ./lib/AVR_drivers/UART/AVR_UART_driver

ENV_CONST = ./lib/ENV_CONSTANTS.h


timer_driver.o: $(TIMER_DR).c $(TIMER_DR).h $(ENV_CONST)
	$(COMPILE) -c $(TIMER_DR).c -o $(TIMER_DR).o

timer_library.o: $(TIMER_LIB).c $(TIMER_LIB).h $(ENV_CONST)
	$(COMPILE) -c $(TIMER_LIB).c -o $(TIMER_LIB).o


UART_driver.o: $(UART_DR).c $(UART_DR).h $(ENV_CONST)
	$(COMPILE) -c $(UART_DR).c -o $(UART_DR).o


UART_library.o: $(UART_LIB).c $(UART_LIB).h $(ENV_CONST)
	$(COMPILE) -c $(UART_LIB).c -o $(UART_LIB).o


$(FILENAME).o: $(FILENAME).c # $(FILENAME).h
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o 


compile: $(FILENAME).o timer_library.o timer_driver.o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o $(TIMER_DR).o $(TIMER_LIB).o 
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

# supporting a different sample file is so sus lmao

$(FILENAME2).o: $(FILENAME2).c
	$(COMPILE) -c $(FILENAME2).c -o $(FILENAME2).o 

compile_uart: $(FILENAME2).o timer_library.o timer_driver.o UART_library.o UART_driver.o
	$(COMPILE) -o $(FILENAME2).elf $(FILENAME2).o $(TIMER_DR).o $(TIMER_LIB).o $(UART_DR).o $(UART_LIB).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME2).elf $(FILENAME2).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME2).elf




upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i


upload_uart:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME2).hex:i



clean: 
	rm -rf *.o *.hex *.a *.elf


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