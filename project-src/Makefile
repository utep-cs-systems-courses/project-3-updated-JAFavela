# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR              = msp430-elf-ar

OBJECTS         = p2switches.o

libp2sw.a: $(OBJECTS)
	$(AR) crs $@ $^

$(OBJECTS): p2switches.h

all: lastOne.elf

#additional rules for files

lastOne.elf: ${COMMON_OBJECTS} main.o wdt_handler.o buzzer.o dimled_assy.o ledSwitch_assy.o p2switches.o stateMachines.o libp2sw.a led.o ../lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -L../lib 

load: lastOne.elf
	msp430loader.sh lastOne.elf
	make clean

clean:
	rm -f *.o *.elf *~ *# *.a

