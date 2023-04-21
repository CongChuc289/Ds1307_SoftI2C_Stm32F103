#include "CLOCK.h"
void Config_CLOCK_HSE(void){
// 1. Enable HSE
	RCC->CR |= RCC_CR_HSEON;                                 
	while(!(RCC->CR & RCC_CR_HSERDY));                    
// 2. Config Flash	
	FLASH->ACR |= FLASH_ACR_PRFTBE;                          // Enable Prefetch Buffer

	FLASH->ACR |= (1<<1);                                    // Flash 2 wait state
  FLASH->ACR &= ~((1<<2)|(1<<0));
// 3. PREDIV
	RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);                      
// 4. PLL Source Mux
  RCC->CFGR |= RCC_CFGR_PLLSRC;                            
// 5. PLL miultipler
	RCC->CFGR |= (1<<18)|(1<<19)|(1<<20);  
	RCC->CFGR &= ~(1<<21);
// 6. Enable PLL
	RCC->CR |= RCC_CR_PLLON;                               
  while(!(RCC->CR & RCC_CR_PLLRDY));                      
	
	RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
// 7. AHB prescaler 	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                         
// 8. APB1 prescaler
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;      
// 9. APB2 prescaler
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                       
	
	SystemCoreClockUpdate();
	
	//SysTick_Config(SystemCoreClock / 1000);
}
void Config_CLOCK_HSI(void){
// 1. Enable HSE
	RCC->CR |= RCC_CR_HSION;                                 
	while(!(RCC->CR & RCC_CR_HSIRDY));                    
// 2. Config Flash	
	FLASH->ACR |= FLASH_ACR_PRFTBE;                          // Enable Prefetch Buffer

	FLASH->ACR |= (1<<1);                                    // Flash 2 wait state
  FLASH->ACR &= ~((1<<2)|(1<<0));
// 3. PREDIV
	RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);                      
// 4. PLL Source Mux
  RCC->CFGR |= RCC_CFGR_PLLSRC;                            
// 5. PLL miultipler
	RCC->CFGR |= RCC_CFGR_PLLMULL7;  
// 6. Enable PLL
	RCC->CR |= RCC_CR_PLLON;                               
  while(!(RCC->CR & RCC_CR_PLLRDY));                      
	
	RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
// 7. AHB prescaler 	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                         
// 8. APB1 prescaler
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;      
// 9. APB2 prescaler
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                       
	
	//SystemCoreClockUpdate();
	
	//SysTick_Config(SystemCoreClock / 1000);
}
void Config_CLOCK_HSE_Std(void){
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
  while(!(RCC_WaitForHSEStartUp() == SUCCESS));
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//72Mhz
	RCC_PLLCmd(ENABLE);
	while(!(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)));
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}
