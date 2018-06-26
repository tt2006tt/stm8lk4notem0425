#ifndef __STM8L15x_TIM2_H
#define __STM8L15x_TIM2_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

typedef enum
{
  TIM2_ForcedAction_Active   = ((uint8_t)0x50),   /*!< Output Reference is forced low */
  TIM2_ForcedAction_Inactive = ((uint8_t)0x40)    /*!< Output Reference is forced high */
}
TIM2_ForcedAction_TypeDef;


typedef enum
{
  TIM2_Prescaler_1     = ((uint8_t)0x00),   /*!< Time base Prescaler = 1 (No effect)*/
  TIM2_Prescaler_2     = ((uint8_t)0x01),   /*!< Time base Prescaler = 2 */
  TIM2_Prescaler_4     = ((uint8_t)0x02),   /*!< Time base Prescaler = 4 */
  TIM2_Prescaler_8     = ((uint8_t)0x03),   /*!< Time base Prescaler = 8 */
  TIM2_Prescaler_16    = ((uint8_t)0x04),   /*!< Time base Prescaler = 16 */
  TIM2_Prescaler_32    = ((uint8_t)0x05),   /*!< Time base Prescaler = 32 */
  TIM2_Prescaler_64    = ((uint8_t)0x06),   /*!< Time base Prescaler = 64 */
  TIM2_Prescaler_128   = ((uint8_t)0x07)    /*!< Time base Prescaler = 128 */
}TIM2_Prescaler_TypeDef;


typedef enum
{
  TIM2_CounterMode_Up               = ((uint8_t)0x00),   /*!< Counter Up Mode */
  TIM2_CounterMode_Down             = ((uint8_t)0x10),   /*!< Counter Down Mode */
  TIM2_CounterMode_CenterAligned1   = ((uint8_t)0x20),   /*!< Counter Central aligned Mode 1 */
  TIM2_CounterMode_CenterAligned2   = ((uint8_t)0x40),   /*!< Counter Central aligned Mode 2 */
  TIM2_CounterMode_CenterAligned3   = ((uint8_t)0x60)    /*!< Counter Central aligned Mode 3 */
}TIM2_CounterMode_TypeDef;


typedef enum
{
  TIM2_IT_Update   = ((uint8_t)0x01),   /*!< Update Interrupt*/
  TIM2_IT_CC1      = ((uint8_t)0x02),   /*!< Capture Compare Channel1 Interrupt*/
  TIM2_IT_CC2      = ((uint8_t)0x04),   /*!< Capture Compare Channel2 Interrupt*/
  TIM2_IT_Trigger  = ((uint8_t)0x40),   /*!< Trigger  Interrupt*/
  TIM2_IT_Break    = ((uint8_t)0x80)    /*!< Break Interrupt*/
}TIM2_IT_TypeDef;


typedef enum
{
  TIM2_FLAG_Update   = ((uint16_t)0x0001),  /*!< Update Flag */
  TIM2_FLAG_CC1      = ((uint16_t)0x0002),  /*!< Capture compare 1 Flag */
  TIM2_FLAG_CC2      = ((uint16_t)0x0004),  /*!< Capture compare 2 Flag */
  TIM2_FLAG_Trigger  = ((uint16_t)0x0040),  /*!< Trigger Flag */
  TIM2_FLAG_Break    = ((uint16_t)0x0080),  /*!< Break Flag */
  TIM2_FLAG_CC1OF    = ((uint16_t)0x0200),  /*!< Capture compare 1 over capture Flag */
  TIM2_FLAG_CC2OF    = ((uint16_t)0x0400)   /*!< Capture compare 2 over capture Flag */
}TIM2_FLAG_TypeDef;





/* Exported functions ------------------------------------------------------- */
/* TimeBase management ********************************************************/
void TIM2_DeInit(void);
void TIM2_TimeBaseInit(TIM2_Prescaler_TypeDef TIM2_Prescaler,
                       TIM2_CounterMode_TypeDef TIM2_CounterMode, uint16_t TIM2_Period);
void TIM2_ARRPreloadConfig(FunctionalState NewState);
void TIM2_Cmd(FunctionalState NewState);
void TIM2_ClearFlag(TIM2_FLAG_TypeDef TIM2_FLAG);

/* Interrupts, DMA and flags management ***************************************/
void TIM2_ITConfig(TIM2_IT_TypeDef TIM2_IT, FunctionalState NewState);
void TIM2_ClearITPendingBit(TIM2_IT_TypeDef TIM2_IT);

#endif /* __STM8L15x_TIM2_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
