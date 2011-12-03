#******************************************************************************
# This makefile was modified to work on Eridani an LM3S3651 based board
# The author imposes no change in the licence from TI below
# The software remains AS IS with no Warranty
#
# Makefile - Rules for building the USB device serial example.
#
# Copyright (c) 2009-2010 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 6594 of the EK-LM3S9B92 Firmware Package.
#
#******************************************************************************


#Program name
NAME = usb_dev_serial

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

os:=${shell uname -s}

CYGWIN = 0
ifneq ($(findstring CYGWIN, ${os}), )
	CYGWIN = 1
endif

ifeq ($(SERIALPROG),1)
	LINKER = bootlink.ld
	ifeq ($(WINDOWS),1)
		FLASHCMD = lmflash -q manual -i serial -p $(COMPORT) -b 115200 -r --offset=0x1000 --xfer-size=32 $(NAME).bin
	else
		FLASHCMD = sflash -p 0x1000 -c $(COMPORT) -b 115200 -s 32 $(NAME).bin
	endif
else
	LINKER = link.ld

	ifeq ($(WINDOWS),1)
		FLASHCMD = perl ./do_flash.pl $(NAME).bin
	else 
		FLASHCMD = ./do_flash.pl $(NAME).bin
	endif

endif


ifeq ($(WINDOWS),1)	
	ifeq ($(CYGWIN),1)
		CLEANCMD = rm -rf ${COMPILER} ${wildcard *~}
		COPYCMD = cp ./${COMPILER}/$(NAME).bin ./
	else
		CLEANCMD = del /s /q ${COMPILER} ${wildcard *~}
		COPYCMD = copy ./${COMPILER}/$(NAME).bin ./
	endif	
else 
	CLEANCMD = rm -rf ${COMPILER} ${wildcard *~}
	COPYCMD = cp ./${COMPILER}/$(NAME).bin ./
endif


#
# The base directory for StellarisWare.
#
ROOT=$(DIR_STELLARISWARE)

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=$(DIR_UTILS)

#
# Where to find header files that do not live in the source directory.
#
IPATH=$(DIR_STELLARISWARE)

#
# The default rule, which causes the USB device serial example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/usb_dev_serial.axf

#
# The rule to clean out all the build products.
#
clean:
	$(CLEANCMD)
#
# Build and flash
#
flash: all 
	$(COPYCMD)
	$(FLASHCMD)
#
#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir ${COMPILER}

#
# Rules for building the USB device serial example.
#
${COMPILER}/usb_dev_serial.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/usb_dev_serial.axf: ${COMPILER}/usb_dev_serial.o
${COMPILER}/usb_dev_serial.axf: ${COMPILER}/usb_serial_structs.o
${COMPILER}/usb_dev_serial.axf: ${ROOT}/usblib/${COMPILER}/libusb.a
${COMPILER}/usb_dev_serial.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/usb_dev_serial.axf: $(LINKER)
SCATTERgcc_usb_dev_serial=$(LINKER)
ENTRY_usb_dev_serial=ResetISR
CFLAGSgcc=-DTARGET_IS_DUSTDEVIL_RA0 -D$(PART)

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
