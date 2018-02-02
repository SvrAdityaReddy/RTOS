#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

// wiring pi mapping

#define GPIOPIN14 15
#define GPIOPIN18 1
#define GPIOPIN23 4
#define GPIOPIN24 5
#define GPIOPIN25 6 // Interrupt pin

// global variable to store state of gpio pins

int state_gpiopins[4];

void ISR() {
	state_gpiopins[0]=digitalRead(GPIOPIN14);
	state_gpiopins[1]=digitalRead(GPIOPIN18);
	state_gpiopins[2]=digitalRead(GPIOPIN23);
	state_gpiopins[3]=digitalRead(GPIOPIN24);
	printf("Data on GPIOPIN14 is %d\n",state_gpiopins[0]);
	printf("Data on GPIOPIN18 is %d\n",state_gpiopins[1]);
	printf("Data on GPIOPIN23 is %d\n",state_gpiopins[2]);
	printf("Data on GPIOPIN24 is %d\n",state_gpiopins[3]);
}

int main() {
	wiringPiSetup();
	pinMode (GPIOPIN14, INPUT);
	pinMode (GPIOPIN18, INPUT);
	pinMode (GPIOPIN23, INPUT);
	pinMode (GPIOPIN24, INPUT);
	pinMode (GPIOPIN25, INPUT);
	wiringPiISR (GPIOPIN25, INT_EDGE_RISING, ISR);
	while(1) {
		
	}
	return 0;
}
