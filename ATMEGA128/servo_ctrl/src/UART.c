

#ifndef _2x_speed
 #define _2x_speed 1
#endif

#include "UART.h"


void UART0_init(uint32_t baud){
	UBRR0H = ((uint8_t)((_2x_speed+1)*(F_CPU/16/baud)-1)) >> 8;
    UBRR0L = (uint8_t)((_2x_speed+1)*(F_CPU/16/baud)-1);
	UCSR0A |= (_2x_speed<<U2X0); // 2x speed
          //      async   |  parity mode disabled   | 1 stop bit |                8bit data
	UCSR0C |= (0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (0<<UCSZ02) | (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // enable receiver and transmitter
}

void UART0_transmit(char data){
    //UCSR0A의 UDRE0비트가 1이 되어야 송신 준비가 완료된 것
	while(!(UCSR0A & (1<<UDRE0))); // wait for empty transmit buffer
    //LSB부터 전송됨
	UDR0 = data;                   // put data into buffer and send
}

unsigned char UART0_receive(void){
	while(!(UCSR0A & (1<<RXC0))); // wait for data to be received
	return UDR0;                   // get and return received data from buffer
}

void UART0_print(uint8_t *str){
    while(*str){
        UART0_transmit(*str++);
    }
}

uint8_t UART0_data_load(uint8_t *rx_buf){
	static uint8_t rx_index = 0;
	uint8_t data_load_complete = 0;
	uint8_t data = UDR0;
	if (data == '\n' || data == '\r') { //개행문자가 수신되면
		rx_buf[rx_index] = '\0'; // 문자열 종료
		rx_index = 0; // 인덱스 초기화
		data_load_complete = 1; // 수신완료 플래그 설정
	}
	else {
		rx_buf[rx_index++] = data; // 수신 데이터 저장, 인덱스 증가
	}
	return data_load_complete;
}

void UART1_init(uint32_t baud){
	UBRR1H = ((uint8_t)((_2x_speed+1)*(F_CPU/16/baud)-1)) >> 8;
    UBRR1L = (uint8_t)((_2x_speed+1)*(F_CPU/16/baud)-1);
	UCSR1A |= (_2x_speed<<U2X1); // 2x speed
          //      async   |  parity mode disabled   | 1 stop bit |                8bit data
	UCSR1C |= (0<<UMSEL1) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) | (0<<UCSZ12) | (1<<UCSZ11) | (1<<UCSZ10);
	UCSR1B |= (1<<RXEN1) | (1<<TXEN1); // enable receiver and transmitter
}

void UART1_transmit(char data){
    //UCSR0A의 UDRE0비트가 1이 되어야 송신 준비가 완료된 것
	while(!(UCSR1A & (1<<UDRE1))); // wait for empty transmit buffer
    //LSB부터 전송됨
	UDR1 = data;                   // put data into buffer and send
}

unsigned char UART1_receive(void){
	while(!(UCSR1A & (1<<RXC1))); // wait for data to be received
	return UDR1;                   // get and return received data from buffer
}

void UART1_print(uint8_t *str){
    while(*str){
        UART1_transmit(*str++);
    }
}

uint8_t UART1_data_load(uint8_t *rx_buf){
	static uint8_t rx_index = 0;
	uint8_t data_load_complete = 0;
	uint8_t data = UDR1;
	if (data == '\n' || data == '\r') { //개행문자가 수신되면
		rx_buf[rx_index] = '\0'; // 문자열 종료
		rx_index = 0; // 인덱스 초기화
		data_load_complete = 1; // 수신완료 플래그 설정
	}
	else {
		rx_buf[rx_index++] = data; // 수신 데이터 저장, 인덱스 증가
	}
	return data_load_complete;
}

void UART0_rx_interrupt_enable(void){
	UCSR0B |= 1<<RXCIE0; // 수신완료 인터럽트 활성화
}

void UART1_rx_interrupt_enable(void){
	UCSR1B |= 1<<RXCIE1; // 수신완료 인터럽트 활성화
}

void UART0_rx_interrupt_disable(void){
	UCSR0B &= ~(1<<RXCIE0); // 수신완료 인터럽트 비활성화
}

void UART1_rx_interrupt_disable(void){
	UCSR1B &= ~(1<<RXCIE1); // 수신완료 인터럽트 비활성화
}

void UART0_tx_interrupt_enable(void){
	UCSR0B |= 1<<TXCIE0; // 송신완료 인터럽트 활성화
}

void UART1_tx_interrupt_enable(void){
	UCSR1B |= 1<<TXCIE1; // 송신완료 인터럽트 활성화
}

void UART0_tx_interrupt_disable(void){
	UCSR0B &= ~(1<<TXCIE0); // 송신완료 인터럽트 비활성화
}

void UART1_tx_interrupt_disable(void){
	UCSR1B &= ~(1<<TXCIE1); // 송신완료 인터럽트 비활성화
}

void UART0_udr_empty_interrupt_enable(void){
	UCSR0B |= 1<<UDRIE0; // UDR 레지스터 빈 인터럽트 활성화
}

void UART1_udr_empty_interrupt_enable(void){
	UCSR1B |= 1<<UDRIE1; // UDR 레지스터 빈 인터럽트 활성화
}

void UART0_udr_empty_interrupt_disable(void){
	UCSR0B &= ~(1<<UDRIE0); // UDR 레지스터 빈 인터럽트 비활성화
}

void UART1_udr_empty_interrupt_disable(void){
	UCSR1B &= ~(1<<UDRIE1); // UDR 레지스터 빈 인터럽트 비활성화
}

