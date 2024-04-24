

#ifndef ULTRA_SONIC_H
#define ULTRA_SONIC_H

#define ECHO_PIN  	PE4  // INT4
#define ECHO_DDR  	DDRE
#define ECHO_PORT 	PORTE
#define ECHO_PINR 	PINE

#define TRIG_PIN  	PD1
#define TRIG_DDR  	DDRD
#define TRIG_PORT 	PORTD
#define TRUE 		1
#define FALSE		0

#define SET_BIT(PORT, PIN) 		PORT |=  (1 << PIN)
#define CLEAR_BIT(PORT, PIN) 	PORT &= ~(1 << PIN)
#define TOGGLE_BIT(PORT, PIN) 	PORT ^=  (1 << PIN)

#include <avr/io.h>
#include "util/delay.h"

void US_ISR_process();
void US_trigger();
void US_init();
uint16_t US_measure_distance();


#endif