#ifndef _DS1307_H_
#define _DS1307_H_

#include "stm32f10x.h"

/* USER CODE BEGIN PTD */
#define DS1307_I2C_ADDR       0xD0

#define DS1307_REG_SECOND     0x00
#define DS1307_REG_MINUTE     0x01
#define DS1307_REG_HOUR       0x02
#define DS1307_REG_DAY        0x03
#define DS1307_REG_DATE       0x04
#define DS1307_REG_MONTH      0x05
#define DS1307_REG_YEAR       0x06
#define DS1307_REG_CONTROL    0x07

#define DS1307_REG_UTC_HR     0x08
#define DS1307_REG_UTC_MIN    0x09
#define DS1307_REG_CENT       0x10

#define DS1307_TIMEOUT        1000

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
}DS1307_STRUCT;

extern DS1307_STRUCT DS1307_t;

void DS1307_Init(void);
void DS1307_Write(unsigned char addr,unsigned char dat);
unsigned char DS1307_Read(unsigned char addr);
void DS1307_Get(void);
void DS1307_Set(void);

//extern uint8_t I2C_ReadMulti(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t lenght);
//extern uint8_t I2C_WriteMulti(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t lenght);
void RTC_GetDateTime(void);
void RTC_SetDateTime(uint8_t gio,uint8_t phut,uint8_t giay,uint8_t thu,uint8_t ngay,uint8_t thang,uint8_t nam) ;
uint8_t RTC_CheckMinMax(uint8_t val, uint8_t min, uint8_t max);
uint8_t RTC_Bin2Bcd(uint8_t bin);
#endif
