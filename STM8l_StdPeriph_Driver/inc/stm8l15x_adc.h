/**
  ******************************************************************************
  * @file    stm8l15x_adc.h
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file contains all the functions prototypes for the ADC 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************  
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L15x_ADC_H
#define __STM8L15x_ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */
  
/** @addtogroup ADC
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Types
  * @{
  */


/** @defgroup ADC_Channels 
  * @{
  */
typedef enum
{
  ADC_Channel_0           = ((uint16_t)0x0301), /*!< Channel 00 */
  ADC_Channel_1           = ((uint16_t)0x0302), /*!< Channel 01 */
  ADC_Channel_2           = ((uint16_t)0x0304), /*!< Channel 02 */
  ADC_Channel_3           = ((uint16_t)0x0308), /*!< Channel 03 */
  ADC_Channel_4           = ((uint16_t)0x0310), /*!< Channel 04 */
  ADC_Channel_5           = ((uint16_t)0x0320), /*!< Channel 05 */
  ADC_Channel_6           = ((uint16_t)0x0340), /*!< Channel 06 */
  ADC_Channel_7           = ((uint16_t)0x0380), /*!< Channel 07 */

  ADC_Channel_8           = ((uint16_t)0x0201), /*!< Channel 08 */
  ADC_Channel_9           = ((uint16_t)0x0202), /*!< Channel 09 */
  ADC_Channel_10          = ((uint16_t)0x0204), /*!< Channel 10 */
  ADC_Channel_11          = ((uint16_t)0x0208), /*!< Channel 11 */
  ADC_Channel_12          = ((uint16_t)0x0210), /*!< Channel 12 */
  ADC_Channel_13          = ((uint16_t)0x0220), /*!< Channel 13 */
  ADC_Channel_14          = ((uint16_t)0x0240), /*!< Channel 14 */
  ADC_Channel_15          = ((uint16_t)0x0280), /*!< Channel 15 */

  ADC_Channel_16          = ((uint16_t)0x0101), /*!< Channel 16 */
  ADC_Channel_17          = ((uint16_t)0x0102), /*!< Channel 17 */
  ADC_Channel_18          = ((uint16_t)0x0104), /*!< Channel 18 */
  ADC_Channel_19          = ((uint16_t)0x0108), /*!< Channel 19 */
  ADC_Channel_20          = ((uint16_t)0x0110), /*!< Channel 20 */
  ADC_Channel_21          = ((uint16_t)0x0120), /*!< Channel 21 */
  ADC_Channel_22          = ((uint16_t)0x0140), /*!< Channel 22 */
  ADC_Channel_23          = ((uint16_t)0x0180), /*!< Channel 23 */

  ADC_Channel_24          = ((uint16_t)0x0001), /*!< Channel 24 */
  ADC_Channel_25          = ((uint16_t)0x0002), /*!< Channel 25 */
  ADC_Channel_26          = ((uint16_t)0x0004), /*!< Channel 26 */
  ADC_Channel_27          = ((uint16_t)0x0008), /*!< Channel 27 */

  ADC_Channel_Vrefint     = ((uint16_t)0x0010), /*!< Vrefint Channel  */
  ADC_Channel_TempSensor  = ((uint16_t)0x0020), /*!< Temperature sensor Channel  */

  /* combination*/
  ADC_Channel_00To07      = ((uint16_t)0x03FF), /*!<select from channel00 to channel07 */
  ADC_Channel_08To15      = ((uint16_t)0x02FF), /*!<select from channel08 to channel15 */
  ADC_Channel_16To23      = ((uint16_t)0x01FF), /*!<select from channel16 to channel23 */
  ADC_Channel_24To27      = ((uint16_t)0x00FF)  /*!<select from channel24 to channel27 */

}ADC_Channel_TypeDef;


  
/** @defgroup ADC_Conversion_Mode
  * @{
  */
typedef enum
{
  ADC_ConversionMode_Single     = ((uint8_t)0x00), /*!< Single Conversion Mode */
  ADC_ConversionMode_Continuous = ((uint8_t)0x04)  /*!< Continuous Conversion Mode */
}ADC_ConversionMode_TypeDef;



/** @defgroup ADC_Resolution
  * @{
  */
typedef enum
{
  ADC_Resolution_12Bit = ((uint8_t)0x00), /*!< 12 bit resolution */
  ADC_Resolution_10Bit = ((uint8_t)0x20), /*!< 10 bit resolution */
  ADC_Resolution_8Bit  = ((uint8_t)0x40), /*!<  8 bit resolution */
  ADC_Resolution_6Bit  = ((uint8_t)0x60)  /*!<  6 bit resolution */
}ADC_Resolution_TypeDef;
/**
  * @brief  ADC  Group Channels definition
  */
typedef enum
{
  ADC_Group_SlowChannels = ((uint8_t)0x00), /*!<Slow Channels group(Channel 0 to 23) */
  ADC_Group_FastChannels = ((uint8_t)0x01)  /*!<Fast Channels group (Channel 24, Channel Vrefint, Channel TempSensor) */
}ADC_Group_TypeDef;



typedef enum
{
  ADC_Prescaler_1 = ((uint8_t)0x00), /*!< ADC Clock frequency is divided by 1 */
  ADC_Prescaler_2 = ((uint8_t)0x80)  /*!< ADC Clock frequency is divided by 2 */
}ADC_Prescaler_TypeDef;

typedef enum
{
  ADC_SamplingTime_4Cycles   = ((uint8_t)0x00), /*!< Sampling Time Cycles is 4 */
  ADC_SamplingTime_9Cycles   = ((uint8_t)0x01), /*!< Sampling Time Cycles is  9 */
  ADC_SamplingTime_16Cycles  = ((uint8_t)0x02), /*!< Sampling Time Cycles is  16 */
  ADC_SamplingTime_24Cycles  = ((uint8_t)0x03), /*!< Sampling Time Cycles is  24 */
  ADC_SamplingTime_48Cycles  = ((uint8_t)0x04), /*!< Sampling Time Cycles is  48 */
  ADC_SamplingTime_96Cycles  = ((uint8_t)0x05), /*!< Sampling Time Cycles is  96 */
  ADC_SamplingTime_192Cycles = ((uint8_t)0x06), /*!< Sampling Time Cycles is  192 */
  ADC_SamplingTime_384Cycles = ((uint8_t)0x07)  /*!< Sampling Time Cycles is  384 */
}ADC_SamplingTime_TypeDef;


/** @defgroup  ADC_Flags
  * @{
  */
typedef enum
{
  ADC_FLAG_EOC  = ((uint8_t)0x01), /*!< End of Conversion  flag  */
  ADC_FLAG_AWD  = ((uint8_t)0x02), /*!< Analog Watchdog  flag  */
  ADC_FLAG_OVER = ((uint8_t)0x04)  /*!< Over Run flag  */
}ADC_FLAG_TypeDef;





/* Initialization and Configuration functions *********************************/ 
void ADC_Init(ADC_TypeDef* ADCx,
              ADC_ConversionMode_TypeDef ADC_ConversionMode,
              ADC_Resolution_TypeDef ADC_Resolution,
              ADC_Prescaler_TypeDef ADC_Prescaler);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx);

                             
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);


FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, ADC_FLAG_TypeDef ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, ADC_FLAG_TypeDef ADC_FLAG);
void ADC_ChannelCmd(ADC_TypeDef* ADCx, ADC_Channel_TypeDef ADC_Channels, FunctionalState NewState);


#endif /*__STM8L15x_ADC_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
