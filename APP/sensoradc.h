#ifndef _SENSORADC_H_
#define	_SENSORADC_H_
#include "main.h"

#define ADC_PORT
#define	ADC_PIN

void Sensor_ADC_Init(void);
uint16_t Adc_Data(ADC_Channel_TypeDef ADC_Channel);
void Sensor_ADC_detect_Init(ADC_Channel_TypeDef ADC_Channel);
void Board_Init(void);
void Pm_Detect(void);
void Mode_haltfun(void);
void Batt_Test(void);
void HaltWakeUp(void);
uint16_t Ad_sensor_detect(ADC_Channel_TypeDef ADC_Channel);
void Pm10_Detect(void);
void Chargehaltfun(void);


extern uint16_t  Cnt_Init;

#endif

