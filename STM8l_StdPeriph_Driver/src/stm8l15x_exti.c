/**
  ******************************************************************************
  * @file    stm8l15x_exti.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the EXTI peripheral:
  *            - Interrupt sensitivity of GPIO ports/pins configuration
  *            - Interrupt status management
  *  @verbatim
  *  
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          This driver provides functions to configure and initialize the EXTI 
  *          peripheral
  *          These functions are split in 2 groups: 
  *   
  *          1. EXTI configuration: this group includes all needed functions 
  *             to configure the EXTI GPIO ports and pins:
  *                   - Set GPIO pins sensitivity
  *                   - Select GPIO port, GPIO half port and set the GPIO port sensitivity
  *                         
  *          2. EXTI interrupt status management
  *                   - Get the interrupt status: set/reset
  *                   - Clear interrupt pending bits
  *
  *  @endverbatim
  *   
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

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_exti.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup EXTI_Private_Functions
  * @{
  */

/** @defgroup EXTI_Group1 Interrupt sensitivity of GPIO ports/pins configuration
 *  @brief   Interrupt sensitivity of GPIO ports/pins configuration
 *
@verbatim   
 ===============================================================================
                         EXTI configuration functions
 ===============================================================================  
  
       ===================================================================      
                        EXTI Driver: how to configure EXTI
       =================================================================== 
       To use a GPIO pin as an interrupt source, follow theses steps:
       
         1. Configure the GPIO pin in input mode with interrupt enabled using
            GPIO_Init()
          
         2. Configure the GPIO pin sensitivity (falling, rising...) using 
            EXTI_SetPinSensitivity()
          
         3. Enable global interrupts using enableInterrupts()
       
         4. In the IRQ handler corresponding to the GPIO pin, clear the interrupt
            pending bit using EXTI_ClearITPendingBit()

       To use a GPIO port as an interrupt source, follows theses steps:  
            
         1. Configure the GPIO pins of the same port in input mode with interrupt
            enabled using GPIO_Init()
          
         2. Configure the GPIO port sensitivity (falling, rising...) using 
            EXTI_SetPortSensitivity()
          
         3. Select the GPIO port and the corresponding half port using  
            EXTI_SelectPort() then EXTI_SetHalfPortSelection()
        
         4. Enable global interrupts using enableInterrupts()
       
         5. In the IRQ handler corresponding to the GPIO port, clear the interrupt
            pending bit using EXTI_ClearITPendingBit()

@endverbatim
  * @{
  */


/**
  * @brief  Sets the external interrupt sensitivity of the selected pin.
  * @note   Global interrupts must be disabled before calling this function.
  * @note   The modification of external interrupt sensitivity is only possible
  *         when he interrupts are disabled.
  * @note   The normal behavior is to disable the interrupts before calling this
  *         function, and re-enable them after.
  * @param  EXTI_Pin : The pin to configure.
  *          This parameter can be one of the following values:
  *            @arg EXTI_Pin_0: GPIO Pin 0
  *            @arg EXTI_Pin_1: GPIO Pin 1
  *            @arg EXTI_Pin_2: GPIO Pin 2
  *            @arg EXTI_Pin_3: GPIO Pin 3
  *            @arg EXTI_Pin_4: GPIO Pin 4
  *            @arg EXTI_Pin_5: GPIO Pin 5
  *            @arg EXTI_Pin_6: GPIO Pin 6
  *            @arg EXTI_Pin_7: GPIO Pin 7              
  * @param  EXTI_Trigger : The external interrupt sensitivity value to set.
  *          This parameter can be one of the following values:
  *            @arg EXTI_Trigger_Falling_Low: Interrupt on Falling edge and Low level
  *            @arg EXTI_Trigger_Rising: Interrupt on Rising edge only  
  *            @arg EXTI_Trigger_Falling: Interrupt on Falling edge only 
  *            @arg EXTI_Trigger_Rising_Falling: Interrupt on Rising and Falling edges       
  * @retval None
  */
void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin, EXTI_Trigger_TypeDef EXTI_Trigger)
{

  /* Check function parameters */
  //assert_param(IS_EXTI_PINNUM(EXTI_Pin));
  //assert_param(IS_EXTI_TRIGGER(EXTI_Trigger));

  /* Clear port sensitivity bits */
  switch (EXTI_Pin)
  {
    case EXTI_Pin_0:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P0IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_1:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P1IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_2:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P2IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_3:
      EXTI->CR1 &=  (uint8_t)(~EXTI_CR1_P3IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_4:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P4IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_5:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P5IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_6:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P6IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_7:
      EXTI->CR2 &=  (uint8_t)(~EXTI_CR2_P7IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    default:
      break;
  }
}



void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT)
{
  uint16_t tempvalue = 0;

  /* Check function parameters */

  tempvalue = ((uint16_t)EXTI_IT & (uint16_t)0xFF00);

  if ( tempvalue == 0x0100)
  {
    EXTI->SR2 = (uint8_t)((uint16_t)EXTI_IT & (uint16_t)0x00FF);
  }
  else
  {
    EXTI->SR1 = (uint8_t) (EXTI_IT);
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
