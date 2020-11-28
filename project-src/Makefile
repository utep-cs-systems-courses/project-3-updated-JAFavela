# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: lastOne.elf

#additional rules for files

lastOne.elf: ${COMMON_OBJECTS} main.o wdt_handler.o buzzer.o p1_interrupt_handler.o switches.o stateMachines.o led.o ../lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -L../lib 

load: lastOne.elf
	msp430loader.sh lastOne.elf
	make clean

clean:
	rm -f *.o *.elf *~ *#

