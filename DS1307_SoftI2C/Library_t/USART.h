#ifndef USART_H_
#define USART_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define BUFFER_SIZE 100


void Config_USART1(void);
void Config_USART1_Std(void);
void Config_USART1_IT_Std(void);
void Config_USART1_IT(void);
void Config_USART1_REMAP_IT_Std(void);

void Config_USART2_Std(void);
void Config_USART2_IT_Std(void);
void Config_USART3_Std(void);
void Config_UART4_IT_Std(void);

void USARTx_Send_data_Std(USART_TypeDef* USARTx, unsigned char *data, unsigned int lenght);
void USART1_Send_data(unsigned char *data, unsigned int lenght);

void USART2_Send_data(unsigned char *data, unsigned int lenght);

unsigned char USART1_Get_data(void);

void Send_RS485(USART_TypeDef* USARTx, unsigned char *data, unsigned int length, GPIO_TypeDef* GPIOx, unsigned short GPIO_Pin_x);
void Config_USART1_DMA_Std(void);
#endif
