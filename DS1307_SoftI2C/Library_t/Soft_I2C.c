#include "Soft_I2C.h"  
#include "TIMER.h"
#include "stdint.h"

void I2C_Soft_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	SCL_1;
	SDA_1;
}
void SDA_Input(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
void SDA_Output(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
void I2C_Soft_Start(void){
	SDA_Output();
	SCL_1;
	SDA_1;
	Delay_Timer2_us(4);
	SDA_0;
	Delay_Timer2_us(4);
	SCL_0;
}
void I2C_Soft_Stop(void){	
	SDA_Output();
	SDA_0;
	Delay_Timer2_us(4);
	SDA_1;
	SCL_1;
	Delay_Timer2_us(4);		
}
void I2C_Send_Byte(uint8_t data){
	unsigned char i;
	SDA_Output();
	SCL_0;
	for(i = 0; i < 8; i++){
		if(data & 0x80) SDA_1;
		else SDA_0;
		Delay_Timer2_us(2);
		SCL_1;
		Delay_Timer2_us(2);
		SCL_0;
		data <<= 1;
	}	
}			
void I2C_Ack(void){
	SDA_Output();
	SCL_0;
	SDA_0;
	Delay_Timer2_us(2);
	SCL_1;
	Delay_Timer2_us(2);
	SCL_0;
}					
void I2C_NAck(void){
	SDA_Output();
	SCL_0;
	SDA_1;
	Delay_Timer2_us(2);
	SCL_1; // SCL
	Delay_Timer2_us(2);
	SCL_0;
}
uint8_t I2C_Read_Byte(uint8_t Ack)
{
	unsigned char i, data = 0;
	SDA_Input();
	for (i = 0; i < 8; i++) {
		SCL_0;
		Delay_Timer2_us(2);
		SCL_1; // SCL
		Delay_Timer2_us(2);
		data <<= 1;
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)) {
			data |= 0x01;
		}
	}
	if (!Ack) {
		I2C_Ack();//
	} else {
		I2C_NAck();//
	}
	return data;
}

uint8_t I2C_Wait_Ack(void){
	uint8_t time=0;
	SDA_Input();
	SDA_1;
	Delay_Timer2_us(1);
	SCL_1; // SCL
	Delay_Timer2_us(1);
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)){
		time++;
		if(time>250) {
			I2C_Soft_Stop();
			return 1;
		}
	}
	SCL_0;
	return 0; 
}

void Write_Cmd_I2C(uint8_t addr, uint8_t reg, uint8_t data){
	I2C_Soft_Start();
	I2C_Send_Byte(addr|0);
	while(I2C_Wait_Ack());
	I2C_Send_Byte(reg);
	while(I2C_Wait_Ack());
	I2C_Send_Byte(data);
	while(I2C_Wait_Ack());
	
	I2C_Soft_Stop(); 
	Delay_Timer2_Ms_Std(2);
}
uint8_t Write_I2C(uint8_t addr, uint8_t reg, uint8_t data){
	I2C_Soft_Start();
	I2C_Send_Byte(addr|0);
	if(I2C_Wait_Ack()){I2C_Soft_Stop(); return 1;}
	I2C_Send_Byte(reg);
	if(I2C_Wait_Ack()){I2C_Soft_Stop(); return 1;}
	I2C_Send_Byte(data);
	if(I2C_Wait_Ack()){I2C_Soft_Stop(); return 1;}
	
	I2C_Soft_Stop(); 
	Delay_Timer2_Ms_Std(2);
	return 0;
}
uint8_t Read_I2C(uint8_t addr, uint8_t reg){
	I2C_Soft_Start();
	I2C_Send_Byte(addr|0);
	while(I2C_Wait_Ack());
	I2C_Send_Byte(reg);
	while(I2C_Wait_Ack());	
	
	I2C_Soft_Start();
	I2C_Send_Byte(addr|1);
	while(I2C_Wait_Ack());
	reg = I2C_Read_Byte(1);
	
	I2C_Soft_Stop(); 
	Delay_Timer2_Ms_Std(2);
	return reg;	
}
uint8_t I2C_ReadMulti(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t lenght){
	I2C_Soft_Start();
	I2C_Send_Byte(addr|0);
	while(I2C_Wait_Ack());
	I2C_Send_Byte(reg);
	while(I2C_Wait_Ack());	
	
	I2C_Soft_Start();
	I2C_Send_Byte(addr|1);
	while(I2C_Wait_Ack());

	while(lenght){
		if(lenght == 1) *buffer = I2C_Read_Byte(1);
		else *buffer = I2C_Read_Byte(0);
		lenght--;
		buffer++;
	}
	I2C_Soft_Stop(); 
	return 0;	
}
uint8_t I2C_WriteMulti(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t lenght){
	unsigned char i;
	I2C_Soft_Start();
	I2C_Send_Byte(addr);
	while(I2C_Wait_Ack());
	I2C_Send_Byte(reg);
	while(I2C_Wait_Ack());
	
	for(i = 0; i < lenght; i++){
		I2C_Send_Byte(buffer[i]);
		if(I2C_Wait_Ack()){
			I2C_Soft_Stop();
			return 1;
		}
	}
	I2C_Soft_Stop(); 
	return 0;	
}
uint8_t Scan_I2C_t(uint8_t addr){
	I2C_Soft_Start();
	I2C_Send_Byte(addr);
	if(I2C_Wait_Ack()){
		I2C_Soft_Stop(); 
		return 1;
	}
	return 0;
}
