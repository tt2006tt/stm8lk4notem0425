/**
  ******************************************************************************
  * @file    stm8l15x_tim1.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the TIM1 peripheral:
  *            - TimeBase management
  *            - Output Compare management
  *            - Input Capture management
  *            - Interrupts, DMA and flags management
  *            - Clocks management
  *            - Synchronization management
  *            - Specific interface management
  *              
  *  @verbatim
  *  
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          This driver provides functions to configure and initialize the TIM1 
  *          peripheral
  *          These functions are split in 7 groups: 
  *   
  *          1. TIM1 TimeBase management: this group includes all needed functions 
  *             to configure the TIM Timebase unit:
  *                   - Set/Get Prescaler
  *                   - Set/Get Autoreload  
  *                   - Counter modes configuration
  *                   - Select the One Pulse mode
  *                   - Update Request Configuration
  *                   - Update Disable Configuration
  *                   - Auto-Preload Configuration 
  *                   - Enable/Disable the counter
  *                 
  *          2. TIM1 Output Compare management: this group includes all needed 
  *             functions to configure the Capture/Compare unit used in Output 
  *             compare mode: 
  *                   - Configure each channel, independently, in Output Compare mode
  *                   - Select the output compare modes
  *                   - Select the Polarities of each channel
  *                   - Set/Get the Capture/Compare register values
  *                   - Select the Output Compare Fast mode 
  *                   - Select the Output Compare Forced mode  
  *                   - Output Compare-Preload Configuration 
  *                   - Clear Output Compare Reference
  *                   - Select the OCREF Clear signal
  *                   - Enable/Disable the Capture/Compare Channels    
  *                   
  *          3. TIM1 Input Capture management: this group includes all needed 
  *             functions to configure the Capture/Compare unit used in 
  *             Input Capture mode:
  *                   - Configure each channel in input capture mode
  *                   - Configure Channel1/2 in PWM Input mode
  *                   - Set the Input Capture Prescaler
  *                   - Get the Capture/Compare values      
  *        
  *          4. TIM1 interrupts, DMA and flags management
  *                   - Enable/Disable interrupt sources
  *                   - Get flags status
  *                   - Clear flags/ Pending bits
  *                   - Enable/Disable DMA requests 
  *                   - Configure DMA burst mode
  *                   - Select CaptureCompare DMA request  
  *              
  *          5. TIM1 clocks management: this group includes all needed functions 
  *             to configure the clock controller unit:
  *                   - Select internal/External clock
  *                   - Select the external clock mode: ETR(Mode1/Mode2) or TIx
  *         
  *          6. TIM1 synchronization management: this group includes all needed 
  *             functions to configure the Synchronization unit:
  *                   - Select Input Trigger  
  *                   - Select Output Trigger  
  *                   - Select Master Slave Mode 
  *                   - ETR Configuration when used as external trigger   
  *     
  *          7. TIM1 specific interface management, this group includes all 
  *             needed functions to use the specific TIM1 interface:
  *                   - Encoder Interface Configuration
  *                   - Select Hall Sensor        
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
#include "stm8l15x_tim1.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM1
  * @brief TIM1 driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup TIM1_Private_Functions_Prototypes
  * @{
  */


/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/  
/** @defgroup TIM1_Private_Functions
  * @{
  */

/** @defgroup TIM1_Group1 TimeBase management functions
 *  @brief   TimeBase management functions 
 *
@verbatim   
 ===============================================================================
                       TimeBase management functions
 ===============================================================================  
  
       ===================================================================      
              TIM1 Driver: how to use it in Timing(Time base) Mode
       =================================================================== 
       To use the Timer in Timing(Time base) mode, the following steps are mandatory:
       
       1. Enable TIM1 clock using CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE) function.
        
       2. Call TIM1_TimeBaseInit() to configure the Time Base unit with the
          corresponding configuration.
          
       3. Enable global interrupts if you need to generate the update interrupt.
          
       4. Enable the corresponding interrupt using the function TIM1_ITConfig(TIM1_IT_Update) 
          
       5. Call the TIM1_Cmd(ENABLE) function to enable the TIM1 counter.
       
       Note1: All other functions can be used separately to modify, if needed,
          a specific feature of the Timer. 

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the TIM1 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM1_DeInit(void)
{
  TIM1->CR1  = TIM1_CR1_RESET_VALUE;
  TIM1->CR2  = TIM1_CR2_RESET_VALUE;
  TIM1->SMCR = TIM1_SMCR_RESET_VALUE;
  TIM1->ETR  = TIM1_ETR_RESET_VALUE;
  TIM1->IER  = TIM1_IER_RESET_VALUE;

  /* Disable channels */
  TIM1->CCER1 = TIM1_CCER1_RESET_VALUE;
  TIM1->CCER2 = TIM1_CCER2_RESET_VALUE;
  /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
  TIM1->CCMR1 = 0x01;
  TIM1->CCMR2 = 0x01;
  TIM1->CCMR3 = 0x01;
  TIM1->CCMR4 = 0x01;
  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM1->CCER1 = TIM1_CCER1_RESET_VALUE;
  TIM1->CCER2 = TIM1_CCER2_RESET_VALUE;
  TIM1->CCMR1 = TIM1_CCMR1_RESET_VALUE;
  TIM1->CCMR2 = TIM1_CCMR2_RESET_VALUE;
  TIM1->CCMR3 = TIM1_CCMR3_RESET_VALUE;
  TIM1->CCMR4 = TIM1_CCMR4_RESET_VALUE;
  TIM1->CNTRH = TIM1_CNTRH_RESET_VALUE;
  TIM1->CNTRL = TIM1_CNTRL_RESET_VALUE;
  TIM1->PSCRH = TIM1_PSCRH_RESET_VALUE;
  TIM1->PSCRL = TIM1_PSCRL_RESET_VALUE;
  TIM1->ARRH  = TIM1_ARRH_RESET_VALUE;
  TIM1->ARRL  = TIM1_ARRL_RESET_VALUE;
  TIM1->CCR1H = TIM1_CCR1H_RESET_VALUE;
  TIM1->CCR1L = TIM1_CCR1L_RESET_VALUE;
  TIM1->CCR2H = TIM1_CCR2H_RESET_VALUE;
  TIM1->CCR2L = TIM1_CCR2L_RESET_VALUE;
  TIM1->CCR3H = TIM1_CCR3H_RESET_VALUE;
  TIM1->CCR3L = TIM1_CCR3L_RESET_VALUE;
  TIM1->CCR4H = TIM1_CCR4H_RESET_VALUE;
  TIM1->CCR4L = TIM1_CCR4L_RESET_VALUE;
  TIM1->OISR  = TIM1_OISR_RESET_VALUE;
  TIM1->EGR   = 0x01; /* TIM1_EGR_UG */
  TIM1->DTR   = TIM1_DTR_RESET_VALUE;
  TIM1->BKR   = TIM1_BKR_RESET_VALUE;
  TIM1->RCR   = TIM1_RCR_RESET_VALUE;
  TIM1->SR1   = TIM1_SR1_RESET_VALUE;
  TIM1->SR2   = TIM1_SR2_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM1 Time Base Unit according to the specified parameters.
  * @param  TIM1_Prescaler specifies the Prescaler value.
  * @param  TIM1_CounterMode specifies the counter mode from
  *          This parameter can be one of the following values:
  *            @arg TIM1_CounterMode_Up: Counter mode Up
  *            @arg TIM1_CounterMode_Down: Counter mode Down
  *            @arg TIM1_CounterMode_CenterAligned1: Counter mode center aligned
  *            @arg TIM1_CounterMode_CenterAligned2: Counter mode center aligned
  *            @arg TIM1_CounterMode_CenterAligned3: Counter mode center aligned
  * @param  TIM1_Period specifies the Period value.
  * @param  TIM1_RepetitionCounter specifies the Repetition counter value
  * @retval None
  */
void TIM1_TimeBaseInit(uint16_t TIM1_Prescaler,
                       TIM1_CounterMode_TypeDef TIM1_CounterMode,
                       uint16_t TIM1_Period,
                       uint8_t TIM1_RepetitionCounter)
{
  /* Check parameters */
  //assert_param(IS_TIM1_COUNTER_MODE(TIM1_CounterMode));


  /* Set the Autoreload value */
  TIM1->ARRH = (uint8_t)(TIM1_Period >> 8);
  TIM1->ARRL = (uint8_t)(TIM1_Period);

  /* Set the Prescaler value */
  TIM1->PSCRH = (uint8_t)(TIM1_Prescaler >> 8);
  TIM1->PSCRL = (uint8_t)(TIM1_Prescaler);

  /* Select the Counter Mode */
  TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR)))
                        | (uint8_t)(TIM1_CounterMode));

  /* Set the Repetition Counter value */
  TIM1->RCR = TIM1_RepetitionCounter;

}


/**
  * @brief  Enables or disables TIM1 peripheral Preload register on ARR.
  * @param  NewState new state of the TIM1 peripheral Preload register.
  *          This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void TIM1_ARRPreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the ARPE Bit */
  if (NewState != DISABLE)
  {
    TIM1->CR1 |= TIM1_CR1_ARPE;
  }
  else
  {
    TIM1->CR1 &= (uint8_t)(~TIM1_CR1_ARPE);
  }
}


/**
  * @brief  Enables or disables the TIM1 peripheral.
  * @param  NewState new state of the TIM1 peripheral. 
  *          This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void TIM1_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM1->CR1 |= TIM1_CR1_CEN;
  }
  else
  {
    TIM1->CR1 &= (uint8_t)(~TIM1_CR1_CEN);
  }
}



/**
  * @}
  */

/** @defgroup TIM1_Group4 Interrupts DMA and flags management functions
 *  @brief    Interrupts, DMA and flags management functions 
 *
@verbatim   
 ===============================================================================
                 Interrupts, DMA and flags management functions
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified TIM1 interrupts.
  * @param  NewState new state of the TIM1 peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @param  TIM1_IT specifies the TIM1 interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg TIM1_IT_Update: Update
  *            @arg TIM1_IT_CC1: Capture Compare Channel1
  *            @arg TIM1_IT_CC2: Capture Compare Channel2 
  *            @arg TIM1_IT_CC3: Capture Compare Channel3
  *            @arg TIM1_IT_CC4: Capture Compare Channel4 
  *            @arg TIM1_IT_COM: Commutation
  *            @arg TIM1_IT_Trigger: Trigger 
  *            @arg TIM1_IT_Break: Break  
  * @param  NewState new state of the TIM1 peripheral.
  * @retval None
  */
void TIM1_ITConfig(TIM1_IT_TypeDef  TIM1_IT, FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_TIM1_IT(TIM1_IT));
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM1->IER |= (uint8_t)TIM1_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM1->IER &= (uint8_t)(~(uint8_t)TIM1_IT);
  }
}



/**
  * @brief  Clears the TIM1’s pending flags.
  * @param  TIM1_FLAG specifies the flag to clear.
  *          This parameter can be one of the following values:
  *            @arg TIM1_FLAG_Update: TIM1 update Flag
  *            @arg TIM1_FLAG_CC1: TIM1 Capture Compare 1 Flag
  *            @arg TIM1_FLAG_CC2: TIM1 Capture Compare 2 Flag
  *            @arg TIM1_FLAG_CC3: TIM1 Capture Compare 3 Flag
  *            @arg TIM1_FLAG_CC4: TIM1 Capture Compare 4 Flag
  *            @arg TIM1_FLAG_COM: TIM1 Commutation Flag
  *            @arg TIM1_FLAG_Trigger: TIM1 Trigger Flag
  *            @arg TIM1_FLAG_Break: TIM1 Break Flag
  *            @arg TIM1_FLAG_CC1OF: TIM1 Capture Compare 1 overcapture Flag
  *            @arg TIM1_FLAG_CC2OF: TIM1 Capture Compare 2 overcapture Flag
  *            @arg TIM1_FLAG_CC3OF: TIM1 Capture Compare 3 overcapture Flag
  *            @arg TIM1_FLAG_CC4OF: TIM1 Capture Compare 4 overcapture Flag
  * @retval None.
  */
void TIM1_ClearFlag(TIM1_FLAG_TypeDef TIM1_FLAG)
{
  /* Check the parameters */
  //assert_param(IS_TIM1_CLEAR_FLAG(TIM1_FLAG));

  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
  TIM1->SR1 = (uint8_t)(~(uint8_t)(TIM1_FLAG));
  TIM1->SR2 = (uint8_t)((uint8_t)(~((uint8_t)((uint16_t)TIM1_FLAG >> 8))) & (uint8_t)0x1E);
}



/**
  * @brief  Clears the TIM1's interrupt pending bits.
  * @param  TIM1_IT specifies the pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM1_IT_Update: Update
  *            @arg TIM1_IT_CC1: Capture Compare Channel1
  *            @arg TIM1_IT_CC2: Capture Compare Channel2 
  *            @arg TIM1_IT_CC3: Capture Compare Channel3
  *            @arg TIM1_IT_CC4: Capture Compare Channel4 
  *            @arg TIM1_IT_COM: Commutation
  *            @arg TIM1_IT_Trigger: Trigger 
  *            @arg TIM1_IT_Break: Break  
  * @retval None.
  */
void TIM1_ClearITPendingBit(TIM1_IT_TypeDef TIM1_IT)
{
  /* Check the parameters */
  //assert_param(IS_TIM1_IT(TIM1_IT));

  /* Clear the IT pending Bit */
  TIM1->SR1 = (uint8_t)(~(uint8_t)TIM1_IT);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
