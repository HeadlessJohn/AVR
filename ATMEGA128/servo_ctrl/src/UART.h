


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

// PE0 : RXD0
// PE1 : TXD0
void UART0_init(uint32_t baud);
void UART0_transmit(char data);
unsigned char UART0_receive(void);
void UART0_print(uint8_t *str);
uint8_t UART0_data_load(uint8_t *rx_buf);
void UART0_rx_interrupt_enable(void);
void UART0_rx_interrupt_disable(void);
void UART0_tx_interrupt_enable(void);
void UART0_tx_interrupt_disable(void);
void UART0_udr_empty_interrupt_enable(void);
void UART0_udr_empty_interrupt_disable(void);

// PD2 : RXD1 
// PD3 : TXD1
void UART1_init(uint32_t baud);
void UART1_transmit(char data);
unsigned char UART1_receive(void);
void UART1_print(uint8_t *str);
uint8_t UART1_data_load(uint8_t *rx_buf);
void UART1_rx_interrupt_enable(void);
void UART1_rx_interrupt_disable(void);
void UART1_tx_interrupt_enable(void);
void UART1_tx_interrupt_disable(void);
void UART1_udr_empty_interrupt_enable(void);
void UART1_udr_empty_interrupt_disable(void);


#endif /* UART_H_ */