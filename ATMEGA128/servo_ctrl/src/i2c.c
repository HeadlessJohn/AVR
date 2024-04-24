/*
 * I2C.c
 */ 

#include "i2c.h"

void I2c_Init()
{
	I2C_DDR |= (1<<I2C_SCL) | (1<<I2C_SDA);	// 출력 설정
	TWBR = 72;		// 100KHz
	//TWBR = 32;		// 200KHz
	//TWBR = 12;		// 400KHz
}

void I2C_Start()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// TWINT에 1을 셋트하여 인터럽트를 발생시키는것 같지만
	// 소프트웨어적으로 1을 셋트하여 플래그를 클리어 하는것임!!
	// TWINT 가 0이면 계속 대기
	while ( (TWCR & (1<<TWINT))==0 );	// 하드웨어적으로 TWINT를 클리어 함
}

void I2C_Stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<< TWSTO);	// stop bit 설정
}

void I2C_TxData(uint8_t data)	  // 1byte
{
	TWDR = data;	
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // 전송 완료 대기
}

void I2C_TxByte(uint8_t devAddRW, uint8_t data)
{
	I2C_Start();
	I2C_TxData(devAddRW);
	I2C_TxData(data);
	I2C_Stop();
}

void I2C_TxBytes(uint8_t devAddRW, uint8_t *data)
{
	uint8_t size = sizeof(data)/sizeof(data[0]);
	I2C_Start();
	I2C_TxData(devAddRW);
	for (uint8_t i=0; i<size; i++) {
		I2C_TxData(data[i]);
	}
	I2C_Stop();
}