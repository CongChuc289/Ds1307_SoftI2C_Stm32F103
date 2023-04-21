#include "DS1307.h"
#include "Soft_I2C.h"

DS1307_STRUCT DS1307_t;

void DS1307_Init(void)
{
	I2C_Soft_Init();
}

uint8_t RTC_Bcd2Bin(uint8_t bcd) {
	
	return 10 * (bcd >> 4)+(bcd & 0x0F);
}

uint8_t RTC_Bin2Bcd(uint8_t bin) {
		
	return (bin / 10) << 4 | (bin % 10);
}
uint8_t RTC_CheckMinMax(uint8_t val, uint8_t min, uint8_t max) {
	if (val < min) {
		return min;
	} else if (val > max) {
		return max;
	}
	return val;
}

void RTC_GetDateTime(void) {
	uint8_t data[7];	
	uint8_t res;	
	res = I2C_ReadMulti( DS1307_I2C_ADDR, 0x00,data, 7);//tu ADD reg=0x00
	if(res == 0)
	{
		DS1307_t.sec = RTC_Bcd2Bin(data[0]);
		DS1307_t.min = RTC_Bcd2Bin(data[1]);
		DS1307_t.hour = RTC_Bcd2Bin(data[2]);
		DS1307_t.day = RTC_Bcd2Bin(data[3]);
		DS1307_t.date = RTC_Bcd2Bin(data[4]);
		DS1307_t.month = RTC_Bcd2Bin(data[5]);
		DS1307_t.year = RTC_Bcd2Bin(data[6]);
	}
}
void RTC_SetDateTime(uint8_t gio,uint8_t phut,uint8_t giay,uint8_t thu,uint8_t ngay,uint8_t thang,uint8_t nam) {
	uint8_t data[7];
	
	data[0] = RTC_Bin2Bcd(RTC_CheckMinMax(giay, 0, 59));
	data[1] = RTC_Bin2Bcd(RTC_CheckMinMax(phut, 0, 59));
	data[2] = RTC_Bin2Bcd(RTC_CheckMinMax(gio, 0, 23));
	data[3] = RTC_Bin2Bcd(RTC_CheckMinMax(thu, 1, 7));
	data[4] = RTC_Bin2Bcd(RTC_CheckMinMax(ngay, 1, 31));
	data[5] = RTC_Bin2Bcd(RTC_CheckMinMax(thang, 1, 12));
	data[6] = RTC_Bin2Bcd(RTC_CheckMinMax(nam, 0, 99));
	
	I2C_WriteMulti( DS1307_I2C_ADDR, 0x00, data, 7);
}
