#include "ultra_sonic.h"


volatile uint16_t US_TCNT = 0;
uint8_t US_ready_flag = 0;

//flag  0000000000000000001000
//tcnt1       0           n
//          상승엣지      하강엣지
//           int          int
//            |  duration |
// ___________-------------__________
void US_ISR_process(){ // ECHO 핀을 통해 인터럽트 발생시 호출
	if (ECHO_PINR & (1<< ECHO_PIN)) // ECHO 핀이 high가 되면
	{
		TCNT1 = 0;			// 타이머 카운터 초기화
		US_ready_flag = 0;  // 플래그 초기화
	}
	else  // ECHO 핀이 low가 되면
	{
		US_TCNT = TCNT1;    // 측정된 시간 저장
		US_ready_flag = 1;  // 플래그 설정
	}
	
}

void US_trigger(){
	SET_BIT(TRIG_PORT, TRIG_PIN);   // Trig 핀 high
	_delay_us(10); 		            //10us 동안 high 유지
	CLEAR_BIT(TRIG_PORT, TRIG_PIN); // Trig 핀 low
}

void US_init(){
	ECHO_DDR  &= ~(1 << ECHO_PIN); // ECHO 핀 입력으로 설정
	TRIG_DDR  |=  (1 << TRIG_PIN); // TRIG 핀 출력으로 설정
	TRIG_PORT &= ~(1 << TRIG_PIN); // Trig 핀 low

	EICRB |= (0 << ISC41) | (1 << ISC40); // logical change detect
	EIMSK |= (1 << INT4);                 // INT4 활성화
	SREG  |= (1 << SREG_I);               // 전역 인터럽트 활성화

	// 16bit 타이머1 설정 ,  1us당 TCNT1 2증가
	TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10); // 8분주
	TCCR1B |= (0 << WGM13)| (0 << WGM12)| (0 << WGM11) | (0 << WGM10); // normal mode

	// 초음파센서 시간 측정을 위해 1us 타이머가 필요함
	// CSn2   CSn1   CSn0   분주비
	//   0      0      0      stop
	//   0      0      1      1
	//   0      1      0      8 -> 0.5us
	//   0      1      1      64
	//   1      0      0      256
	//   1      0      1      1024
	//   1      1      0      외부 클럭(T1 핀) falling
	//   1      1      1      외부 클럭(T1 핀) rising
}

uint16_t US_measure_distance(){
	US_trigger();
	while(!US_ready_flag); // flag 가 1이 될때까지 대기
	return (uint16_t) (US_TCNT/(11.6));
}