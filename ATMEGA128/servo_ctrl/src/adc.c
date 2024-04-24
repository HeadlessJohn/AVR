#ifndef __AVR_ATmega128A__
#define __AVR_ATmega128A__
#endif

#include "adc.h"

void ADC_init(){
	ADMUX  |= (0 << REFS1) | (1 << REFS0); // AVCC를 기준전압으로 사용
	ADMUX  |= (0 << ADLAR); // 오른쪽 정렬
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 분주비 128
	// ADCSRA |= (1 << ADSC); // 변환 시작
	ADCSRA |= (1 << ADIE); // ADC 인터럽트 활성화
	ADCSRA |= (1 << ADEN); // ADC 활성화
	// ADCSRA |= (1 << ADFR); // 자동트리거 모드
}

uint16_t read_ADC(uint8_t channel){
	ADMUX = (ADMUX & 0b11111000) | (channel & 0b00000111); // 채널 선택
	ADCSRA |= (1 << ADSC); // 변환 시작
	while(ADCSRA & (1 << ADSC)); // 변환 완료 대기 : ADSC가 0이 되면 완료
	return ADC;
}
// ADMUX
// |  REFS1  |  REFS0  |  ADLAR  |  MUX4  |  MUX3  |  MUX2  |  MUX1  |  MUX0  |
// REFS0~1 기준전압 설정
// ADLAR ADC 결과를 왼쪽 정렬 -> MSB가 ADCH[15]에 저장
// ADMUX 0~3 먹스 선택

// ADCSRA
// |  ADEN  |  ADSC  |  ADFR  |  ADIF  |  ADIE  |  ADPS2  |  ADPS1  |  ADPS0  |
// ADEN ADC 활성화
// ADSC 변환 시작 -> 1로 설정하면 변환 시작, 변환 완료 후 0으로 자동 설정
// ADFR 자동 트리거 모드 -> 1로 설정하면 자동 변환 시작
// ADIF 변환 완료 인터럽트 플래그 -> 변환 완료 시 1로 설정
// ADIE 변환 완료 인터럽트 허용
// ADPS0~2 분주비 설정
// 000   2      16MHz /   2 =      8MHz : T = 125ns
// 001   2      16MHz /   2 =      8MHz : T = 125ns
// 010   4      16MHz /   4 =      4MHz : T = 250ns
// 011   8      16MHz /   8 =      2MHz : T = 500ns
// 100  16      16MHz /  16 =      1MHz : T = 1us
// 101  32      16MHz /  32 =    500kHz : T = 2us
// 110  64      16MHz /  64 =    250kHz : T = 4us
// 111 128      16MHz / 128 =    125kHz : T = 8us