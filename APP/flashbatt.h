#ifndef __FLASH_H__
#define __FLASH_H__
#include "main.h"


//#define UPDATE_FLAG             ((uint8_t)0x88) 
#define DEVID_BaseAddress               ((uint16_t)0x00001010)

#define     ID_BaseAddress         (0x4926)//查看手册可知

#define WAKEKEY_PORT	(GPIOD)
#define WAKEKEY_PIN		(GPIO_Pin_7)



void EEPROM_INIT(void);
void writeSomeByte(uint32_t Address, uint8_t *Data,uint8_t length);
void readSomeByte(uint32_t Address, uint8_t Data[],uint8_t length);
void KEY_Input_Init(void);
void mykey_Press(void);

void UartWorking(void);


#endif

