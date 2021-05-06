FILENAME = ./examples/timer_sample
FILENAME2 = ./examples/UART_sample
FILENAME3 = ./examples/timer_driver_sample
DEVICE = atmega16m1
DEVICE2 = m16
CLOCK = 4000000UL
BAUD = 115200
PROGRAMMER = usbasp
# might be 'dragon_isp' or `avrispmkII`
PORT = usb

COMPILE = avr-gcc -Wall -Werror -Os -g -std=gnu99 -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) # -lm

TIMER_LIB = ./lib/libs/timer/timer_library
TIMER_DR = ./lib/AVR_drivers/timer/AVR_timer_driver

UART_LIB = ./lib/libs/UART/UART_library
UART_DR = ./lib/AVR_drivers/UART/AVR_UART_driver

ENV_CONST = ./lib/ENV_CONSTANTS.h

# for flashing: 
AVRFLAGS = -B5 -v -c $(PROGRAMMER) -p $(DEVICE) -P $(PORT)


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

$(FILENAME2).o: $(FILENAME2).c
	$(COMPILE) -c $(FILENAME2).c -o $(FILENAME2).o 

$(FILENAME3).o: $(FILENAME3).c
	$(COMPILE) -c $(FILENAME3).c -o $(FILENAME3).o 

compile_driver: $(FILENAME3).o timer_driver.o timer_library.o
	$(COMPILE) -o $(FILENAME3).elf $(FILENAME3).o $(TIMER_DR).o $(TIMER_LIB).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME3).elf $(FILENAME3).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME3).elf

compile: $(FILENAME).o timer_library.o timer_driver.o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o $(TIMER_DR).o $(TIMER_LIB).o 
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

# supporting a different sample file is so sus lmao



compile_uart: $(FILENAME2).o timer_library.o timer_driver.o UART_library.o UART_driver.o
	$(COMPILE) -o $(FILENAME2).elf $(FILENAME2).o $(TIMER_DR).o $(TIMER_LIB).o $(UART_DR).o $(UART_LIB).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME2).elf $(FILENAME2).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME2).elf




upload:
	sudo avrdude $(AVRFLAGS) -U flash:w:$(FILENAME3).hex 




upload_uart:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME2).hex:i



clean: 
	rm -rf *.o *.hex *.a *.elf
	find . -name \*.o -type f -delete 

# do find for all garbage file types?  


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
