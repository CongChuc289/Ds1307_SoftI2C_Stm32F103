#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H 			   

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define SDA_PIN GPIO_Pin_15
#define SCL_PIN GPIO_Pin_12
#define SDA_PORT GPIOA
#define SCL_PORT GPIOA
 
#define SDA_0 GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define SDA_1 GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define SCL_0 GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define SCL_1 GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define SDA_VAL (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15))

//IIC
void SDA_Input(void);
void SDA_Output(void);
void I2C_Soft_Init(void);              			 
void I2C_Soft_Start(void);				
void I2C_Soft_Stop(void);	  
void I2C_Send_Byte(uint8_t data);
uint8_t I2C_Read_Byte(uint8_t Ack);
void I2C_Ack(void);
void I2C_NAck(void);
uint8_t I2C_Wait_Ack(void);
uint8_t Scan_I2C_t(uint8_t addr);
uint8_t I2C_WriteMulti(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t lenght);
uint8_t I2C_ReadMulti(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t lenght);
#endif

