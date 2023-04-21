#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

void Config_Timer1(void);
void Config_Timer1_Std(void);
void Config_Timer1_IT_Std(void);
void Config_Timer2_IT_Std(void);

void Config_Timer2(void);
void Config_Timer2_Std(void);

void Delay_Timer1_us(unsigned int us);
void Delay_Timer1_Ms(unsigned int ms);
void Delay_Timer1_Ms_Std(unsigned int ms);

void Delay_Timer2_us(unsigned int us);
void Delay_Timer2_Ms(unsigned int ms);
void Delay_Timer2_Ms_Std(unsigned int ms);

#endif
