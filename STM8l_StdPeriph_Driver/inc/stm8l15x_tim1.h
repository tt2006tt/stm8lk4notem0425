/**
  ******************************************************************************
  * @file    stm8l15x_tim1.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file contains all the functions prototypes for the TIM1 firmware
  *          library.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L15x_TIM1_H
#define __STM8L15x_TIM1_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"



/** TIM1 Counter Mode */
typedef enum
{
  TIM1_CounterMode_Up                = ((uint8_t)0x00),
  TIM1_CounterMode_Down              = ((uint8_t)0x10),
  TIM1_CounterMode_CenterAligned1    = ((uint8_t)0x20),
  TIM1_CounterMode_CenterAligned2    = ((uint8_t)0x40),
  TIM1_CounterMode_CenterAligned3    = ((uint8_t)0x60)
}TIM1_CounterMode_TypeDef;



/** TIM1 interrupt sources */
typedef enum
{
  TIM1_IT_Update                     = ((uint8_t)0x01),
  TIM1_IT_CC1                        = ((uint8_t)0x02),
  TIM1_IT_CC2                        = ((uint8_t)0x04),
  TIM1_IT_CC3                        = ((uint8_t)0x08),
  TIM1_IT_CC4                        = ((uint8_t)0x10),
  TIM1_IT_COM                        = ((uint8_t)0x20),
  TIM1_IT_Trigger                    = ((uint8_t)0x40),
  TIM1_IT_Break                      = ((uint8_t)0x80)
}TIM1_IT_TypeDef;






/** TIM1 Flags */
typedef enum
{
  TIM1_FLAG_Update                   = ((uint16_t)0x0001),
  TIM1_FLAG_CC1                      = ((uint16_t)0x0002),
  TIM1_FLAG_CC2                      = ((uint16_t)0x0004),
  TIM1_FLAG_CC3                      = ((uint16_t)0x0008),
  TIM1_FLAG_CC4                      = ((uint16_t)0x0010),
  TIM1_FLAG_COM                      = ((uint16_t)0x0020),
  TIM1_FLAG_Trigger                  = ((uint16_t)0x0040),
  TIM1_FLAG_Break                    = ((uint16_t)0x0080),
  TIM1_FLAG_CC1OF                    = ((uint16_t)0x0200),
  TIM1_FLAG_CC2OF                    = ((uint16_t)0x0400),
  TIM1_FLAG_CC3OF                    = ((uint16_t)0x0800),
  TIM1_FLAG_CC4OF                    = ((uint16_t)0x1000)
}TIM1_FLAG_TypeDef;




void TIM1_DeInit(void);
void TIM1_TimeBaseInit(uint16_t TIM1_Prescaler,
                       TIM1_CounterMode_TypeDef TIM1_CounterMode,
                       uint16_t TIM1_Period,
                       uint8_t TIM1_RepetitionCounter);

void TIM1_Cmd(FunctionalState NewState);
void TIM1_ITConfig(TIM1_IT_TypeDef TIM1_IT, FunctionalState NewState);
void TIM1_ARRPreloadConfig(FunctionalState NewState);

void TIM1_ClearFlag(TIM1_FLAG_TypeDef TIM1_FLAG);
void TIM1_ClearITPendingBit(TIM1_IT_TypeDef TIM1_IT);


#endif /* __STM8L15x_TIM1_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
