/*
Blinky turns PD0 on and off
B. A. Bryce/teho Labs 2010
*/

#include "inc/lm3s3651.h"

#define blinkTime 200000

// Function prototypes
void myDelay(unsigned long delay);

int main(void)
{

    // Enable GIPO Port D
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOD;
	
	myDelay(1);

    // Enable the GPIO pin for the LED (PD0).  Set the direction as output, and
    // enable the GPIO pin for digital function.

    GPIO_PORTD_DIR_R |= 0x01;
    GPIO_PORTD_DEN_R |= 0x01;


    while(1)
    {
		myDelay(blinkTime); //Wait ~ blinkTime cycles
		
        GPIO_PORTD_DATA_R |= 0x01;// PD0 on
		
		myDelay(blinkTime);//Wait ~ blinkTime cycles
		
        GPIO_PORTD_DATA_R &= ~(0x01);// PD0 off

    }
}

//Waste cycle delay function
void myDelay(unsigned long delay)
{ 
	while(delay)
	{ 
		delay--;
		__asm__ __volatile__("mov r0,r0");
	}
}