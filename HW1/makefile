
# 
# Build the GPIO toggle app.
#

CC   = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
CFLAGS  = --specs=nosys.specs
DEPS    = hw1.h
#EXE    = hw1.elf


all: 
	$(CC) $(CFLAGS) -g -c hw1.c -o hw1.o
	$(CC) $(CFLAGS) hw1.o -o hw1.elf
	$(OBJDUMP) -S hw1.elf > hw1_dmp.txt

clean:
	rm -rf  hw1*.o hw1.elf hw1_dmp.txt
