#include "avr/io.h"
#include "avr/interrupt.h"
#include <stdio.h>
#include "UART.h"
#include "ultra_sonic.h"

#define BAUDRATE 9600

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

ISR(INT4_vect){
	US_ISR_process();
}

int main(void) {
	stdout = &OUTPUT;

	UART0_init(BAUDRATE);
	printf("UART0 : %6d initialized\n", BAUDRATE);

	US_init();
	printf("ECHO : PE4, TRIG : PD1\n");
	printf("Ultra sonic sensor initialized\n");
	
	while(1){
		printf("Distance : %4d mm\n", US_measure_distance());
		_delay_ms(50);
	}	

	return 0;
}


