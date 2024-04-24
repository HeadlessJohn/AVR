
#include <avr/io.h>

#ifndef ADC_H_
#define ADC_H_

void ADC_init();
uint16_t read_ADC(uint8_t channel);


#endif /* ADC_H_ */