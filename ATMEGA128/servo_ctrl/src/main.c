

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "UART.h"
#include "sg90.h"
#include "adc.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	stdout = &OUTPUT;

	UART0_init(250000);
	printf("Start ADC Test\n");

	ADC_init();
	printf("ADC Init Complete\n");

	sg90_init();
	printf("SG90 Init Complete\n");

	// LED PORT 설정
	DDRA = 0xFF;
	PORTA = 0x00;

	uint16_t adc_val[8] = {
		0,
	};
	uint16_t deg = 90;

	while (1)
	{
		adc_val[0] = read_ADC(0);
		adc_val[1] = read_ADC(1);
		adc_val[2] = read_ADC(2);
		// adc_val[3] = read_ADC(3);
		// adc_val[4] = read_ADC(4);
		// adc_val[5] = read_ADC(5);
		// adc_val[6] = read_ADC(6);
		// adc_val[7] = read_ADC(7);

		printf("ADC %d: %d\t ADC %d: %d\t ADC %d: %d\n", 0, adc_val[0], 1, adc_val[1], 2, adc_val[2]);

		if (adc_val[1] < 127)
			PORTA = 0b00000001;
		else if (adc_val[1] < 255)
			PORTA = 0b00000010;
		else if (adc_val[1] < 383)
			PORTA = 0b00000100;
		else if (adc_val[1] < 511)
			PORTA = 0b00001000;
		else if (adc_val[1] < 639)
			PORTA = 0b00010000;
		else if (adc_val[1] < 767)
			PORTA = 0b00100000;
		else if (adc_val[1] < 895)
			PORTA = 0b01000000;
		else
			PORTA = 0b10000000;

		deg = (uint16_t)(adc_val[0] / 5.688);
		set_deg(deg);

		_delay_ms(10);
	}
	return 0;
}
