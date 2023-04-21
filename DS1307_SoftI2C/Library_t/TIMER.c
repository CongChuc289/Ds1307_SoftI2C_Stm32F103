#include "TIMER.h"
void Config_Timer1(void){
/*
	1. Enable Timer Clock
	2. Set the Prescaler and ARR
	3. Enable the Timer and wait for the update Flag to set
*/
	RCC->APB2ENR |= (1 << 11);

	TIM1->ARR = 0xFFFF;
	TIM1->PSC = 72 - 1;
 
	TIM1->CR1 &= ~(1 << 4); // Mode counter up
	TIM1->CR1 |= (1<<0); // Enable Counter
	while(!(TIM1->SR & (1<<0))); // Update interrupt flag
}
void Config_Timer2(void){
/*
	1. Enable Timer Clock
	2. Set the Prescaler and ARR
	3. Enable the Timer and wait for the update Flag to set
*/
	RCC->APB1ENR |= (1 << 0);
	
	TIM2->ARR = 0xFFFF;
	TIM2->PSC = 72 - 1;
	
	TIM2->CR1 &= ~(1 << 4); // mode counter up
	TIM2->CR1 |= (1<<0); // Counter enabled 
	TIM2->EGR |= (1<<0); // generates an update event to reload
}
void Delay_Timer1_us(unsigned int us){
	TIM1->CNT=0;
	while(TIM1->CNT < us);
}
void Delay_Timer1_Ms(unsigned int ms){
	for(unsigned int i = 0; i < ms; i++){
		Delay_Timer1_us(1000);
	}
}
void Delay_Timer2_us(unsigned int us){
	TIM2->CNT=0;
	while(TIM2->CNT < us);
}
void Delay_Timer2_Ms(unsigned int ms){
	for(unsigned int i = 0; i < ms; i++){
		Delay_Timer2_us(1000);
	}
}
void Delay_Timer2_Ms_Std(unsigned int ms){
	while(ms){
		TIM_SetCounter(TIM2, 0U);
		while((TIM_GetCounter(TIM2) < 1000U));
		ms --;
	}
}
void Delay_Timer1_Ms_Std(unsigned int ms){
	while(ms){
		TIM_SetCounter(TIM1, 0U);
		while((TIM_GetCounter(TIM1) < 1000U));
		ms --;
	}
}
void Config_Timer2_Std(void){
	TIM_TimeBaseInitTypeDef   TIM_TimerBaseInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimerBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimerBaseInitStruct.TIM_Period = 0xFFFF;
	TIM_TimerBaseInitStruct.TIM_Prescaler = 72 - 1;
	
	TIM_TimerBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimerBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimerBaseInitStruct);
	
	TIM_Cmd(TIM2, ENABLE);
}
void Config_Timer1_Std(void){
	TIM_TimeBaseInitTypeDef TIM_TimerBaseInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
  TIM_TimerBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimerBaseInitStruct.TIM_Period = 0xFFFF;
	TIM_TimerBaseInitStruct.TIM_Prescaler = 72 - 1;
	
	TIM_TimerBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimerBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimerBaseInitStruct);
	
	TIM_Cmd(TIM1, ENABLE);
}
void Config_Timer1_IT_Std(void){
	TIM_TimeBaseInitTypeDef        TIM1_IT;
	NVIC_InitTypeDef 					     NVIC_TIM1;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
  TIM1_IT.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_IT.TIM_Period = 999;
	TIM1_IT.TIM_Prescaler = 72 - 1;
	TIM1_IT.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM1_IT.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM1_IT);
	
	NVIC_TIM1.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_TIM1.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_TIM1.NVIC_IRQChannelSubPriority = 2;
	NVIC_TIM1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_TIM1);
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}
void Config_Timer2_IT_Std(void){
	TIM_TimeBaseInitTypeDef        TIM2_IT;
	NVIC_InitTypeDef 					     NVIC_TIM2;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
  TIM2_IT.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_IT.TIM_Period = 5000;
	TIM2_IT.TIM_Prescaler = 7200 -1;
	TIM2_IT.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM2_IT.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM2_IT);
	
	NVIC_TIM2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_TIM2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_TIM2.NVIC_IRQChannelSubPriority = 2;
	NVIC_TIM2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_TIM2);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}
