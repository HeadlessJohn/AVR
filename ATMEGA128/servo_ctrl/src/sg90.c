#ifndef __AVR_ATmega128A__
#define __AVR_ATmega128A__
#endif

#include "sg90.h"


const uint16_t deg_0_offset = 1100;
const uint16_t r_lmt = 820;  // clockwise
const uint16_t l_lmt = 5000; // counter clockwise
const uint8_t deg = 22;

void sg90_init(){
	DDRB |= (1 << PB5); // OC1A as output
    TCCR1A |= (1<<COM1A1) | (0<<COM1A0); // Clear OC1A on compare match set at bottom
    TCCR1A |= (1<<WGM11) | (0<<WGM10); // Fast PWM, TOP=ICR1
    TCCR1B |= (1<<WGM13) | (1<<WGM12); // Fast PWM, TOP=ICR1
    TCCR1B |= (0<<CS12) | (1<<CS11) | (0<<CS10);
    // 000 = No clock source (Timer/Counter stopped).
    // 001 = clk/1 (No prescaling)
    // 010 = clk/8 (From prescaler)
    // 011 = clk/64 (From prescaler)
    // 100 = clk/256 (From prescaler)
    // 101 = clk/1024 (From prescaler)
    // 110 = External clock source on T1 pin. Clock on falling edge.
    // 111 = External clock source on T1 pin. Clock on rising edge.
	
    ICR1 = 39999; // 50Hz
	// 16MHz / 8(prescaler) = 2MHz
	// 2MHz / 40000(top) = 50Hz
	// ICRn / top = duty ratio
}

void set_deg(uint8_t target_deg){
	if(target_deg > 180) target_deg = 180;
	OCR1A = deg_0_offset + (target_deg*deg);
}