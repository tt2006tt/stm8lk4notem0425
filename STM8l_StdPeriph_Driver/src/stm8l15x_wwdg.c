/**
  ********************************************************************************
  * @file    stm8l15x_wwdg.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Window watchdog (WWDG) peripheral:           
  *           - Refresh window and Counter configuration
  *           - WWDG activation
  *           - Couter and software reset management
  *             
  *  @verbatim
  *    
  *          ===================================================================
  *                                     WWDG features
  *          ===================================================================
  *                                        
  *          Once enabled the WWDG generates a system reset on expiry of a programmed
  *          time period, unless the program refreshes the counter (downcounter) 
  *          before to reach 0x3F value (i.e. a reset is generated when the counter
  *          value rolls over from 0x40 to 0x3F). 
  *          An MCU reset is also generated if the counter value is refreshed
  *          before the counter has reached the refresh window value. This 
  *          implies that the counter must be refreshed in a limited window.
  *            
  *          Once enabled the WWDG cannot be disabled except by a system reset.
  *          
  *          If the WWDG is activated and the watchdog reset on halt option is 
  *          selected (Option byte), then the HALT instruction will generate a reset.
  *          
  *          WWDGF flag in RST_SR register can be used to inform when a WWDG
  *          reset occurs.
  *            
  *          WWDG timeout = (WWDG counter clock) * 12288 * (T[5:0] + 1)
  *                      
  *          Min-max timeout value @16 MHz(PCLK1): ~0.768 ms / ~49.152 ms
  *                            
  *          ===================================================================
  *                                 How to use this driver
  *          =================================================================== 
  *          1. Configure the WWDG refresh window using WWDG_SetWindowValue() function
  *            
  *          2. Set the WWDG counter value and start it using WWDG_Enable() function.
  *             When the WWDG is enabled the counter value should be configured to 
  *             a value greater than 0x40 to prevent generating an immediate reset.     
  *            
  *          3. Then the application program must refresh the WWDG counter at regular
  *             intervals during normal operation to prevent an MCU reset, using
  *             WWDG_SetCounter() function. This operation must occur only when
  *             the counter value is lower than the refresh window value, 
  *             programmed using WWDG_SetWindowValue().         
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
#include "stm8l15x_wwdg.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */
/** @defgroup WWDG 
  * @brief WWDG driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BIT_MASK          ((uint8_t)0x7F)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/




/**
  * @brief  Sets the WWDG counter value.
  * @param  Counter: specifies the watchdog counter value.
  *   This parameter must be a number between 0x40 and 0x7F (to prevent generating
  *   an immediate reset) 
  * @retval None
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  //assert_param(IS_WWDG_COUNTER_VALUE(Counter));

  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = (uint8_t)(Counter & (uint8_t)BIT_MASK);
}

