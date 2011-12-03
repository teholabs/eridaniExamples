#Eridani Makefile
#2011 teho Labs

NAME = blinky

# Defines the part type that this project uses.
PART=PART_LM3S3651

#include the toolchain settings 
include $.../toolchainsettings

#For readablity we repeat the contents of toolchainsettings here:

##start toolchain settings
##COMPORT should be COMx or /dev/ttyUSBx or similar for windows and linux respectivly
#COMPORT = /dev/ttyS3
#SERIALPROG = 0
#WINDOWS = 0

##Use forward slashes for the paths
##DIR_STELLARISWARE is typically C:/Users/USERNAME/Development/StellarisWare or /home/USERNAME/Development/StellarisWare
#DIR_STELLARISWARE = /home/USERNAME/Development/StellarisWare
#DIR_DRIVERLIB = $(DIR_STELLARISWARE)/driverlib
#DIR_USBLIB = $(DIR_STELLARISWARE)/usblib
#DIR_UTILS = $(DIR_STELLARISWARE)/utils

##end toolchain settings

#Toolchain Command Config
ifeq ($(SERIALPROG),1)
	LINKER = bootlink
	ifeq ($(WINDOWS),1)
		FLASHCMD = lmflash -q manual -i serial -p $(COMPORT) -b 115200 -r --offset=0x1000 --xfer-size=32 $(NAME).bin
	else
		FLASHCMD = sflash -p 0x1000 -c $(COMPORT) -b 115200 -s 32 $(NAME).bin
	endif
else
	LINKER = link	
	FLASHCMD = ./do_flash.pl $(NAME).bin
endif


ifeq ($(WINDOWS),1)
	CLEANCMD = del $(NAME).elf $(NAME).dmp *.list *.o
else 
	CLEANCMD = rm -f $(NAME).elf $(NAME).dmp *.list *.o
endif


CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld -v
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
OD	= arm-none-eabi-objdump


MACROS  = -DTARGET_IS_DUSTDEVIL_RA0 -D$(PART)
CFLAGS  =  -I./ -I$(DIR_STELLARISWARE) -std=c99 -fno-common -Os -g -mcpu=cortex-m3 -mthumb 
LFLAGS  = -T$(LINKER).ld -nostartfiles
CPFLAGS = -Obinary
ODFLAGS	= -D

SOURCES = \
	$(NAME).c startup_gcc.c\
	$(DIR_DRIVERLIB)/gcc/libdriver.a\

all: reg

flash: all 
	$(FLASHCMD)

clean: 
	$(CLEANCMD)	

test: $(NAME).elf
	$(CP) $(CPFLAGS) $(NAME).elf $(NAME).bin
	$(OD) $(ODFLAGS) $(NAME).elf > $(NAME).list

reg: $(NAME).elf
	$(CP) $(CPFLAGS) $(NAME).elf $(NAME).bin

$(NAME).elf: $(SOURCES) link.ld 
	$(CC) $(MACROS) $(CFLAGS) $(LFLAGS) -o $(NAME).elf  $(SOURCES)


