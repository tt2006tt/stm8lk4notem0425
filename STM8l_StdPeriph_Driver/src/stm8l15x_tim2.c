/**
  ******************************************************************************
  * @file    stm8l15x_tim2.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the TIM2 peripheral:
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
  *          This driver provides functions to configure and initialize the TIM2
  *          peripheral
  *          These functions are split in 7 groups: 
  *   
  *          1. TIM2 TimeBase management: this group includes all needed functions 
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
  *          2. TIM2 Output Compare management: this group includes all needed 
  *             functions to configure the Capture/Compare unit used in Output 
  *             compare mode: 
  *                   - Configure each channel, independently, in Output Compare mode
  *                   - Select the output compare modes
  *                   - Select the Polarities of each channel
  *                   - Set/Get the Capture/Compare register values
  *                   - Select the Output Compare Fast mode 
  *                   - Select the Output Compare Forced mode  
  *                   - Output Compare-Preload Configuration 
  *                   - Enable/Disable the Capture/Compare Channels    
  *                   
  *          3. TIM2 Input Capture management: this group includes all needed 
  *             functions to configure the Capture/Compare unit used in 
  *             Input Capture mode:
  *                   - Configure each channel in input capture mode
  *                   - Configure Channel1/2 in PWM Input mode
  *                   - Set the Input Capture Prescaler
  *                   - Get the Capture/Compare values      
  *        
  *          4. TIM2 interrupts, DMA and flags management
  *                   - Enable/Disable interrupt sources
  *                   - Get flags status
  *                   - Clear flags/ Pending bits
  *                   - Enable/Disable DMA requests 
  *                   - Select CaptureCompare DMA request  
  *              
  *          5. TIM2 clocks management: this group includes all needed functions 
  *             to configure the clock controller unit:
  *                   - Select internal/External clock
  *                   - Select the external clock mode: ETR(Mode1/Mode2) or TIx
  *         
  *          6. TIM2 synchronization management: this group includes all needed 
  *             functions to configure the Synchronization unit:
  *                   - Select Input Trigger  
  *                   - Select Output Trigger  
  *                   - Select Master Slave Mode 
  *                   - ETR Configuration when used as external trigger   
  *     
  *          7. TIM2 specific interface management, this group includes all 
  *             needed functions to use the specific TIM2 interface:
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
#include "stm8l15x_TIM2.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM2 
  * @brief TIM2 driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/** @defgroup TIM2_Private_Functions
  * @{
  */

/** @defgroup TIM2_Group1 TimeBase management functions
 *  @brief   TimeBase management functions 
 *
@verbatim   
 ===============================================================================
                       TimeBase management functions
 ===============================================================================  
  
       ===================================================================      
              TIM2 Driver: how to use it in Timing(Time base) Mode
       =================================================================== 
       To use the Timer in Timing(Time base) mode, the following steps are mandatory:
       
       1. Enable TIM2 clock using CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE) function.
        
       2. Call TIM2_TimeBaseInit() to configure the Time Base unit with the
          corresponding configuration.
          
       3. Enable global interrupts if you need to generate the update interrupt.
          
       4. Enable the corresponding interrupt using the function TIM2_ITConfig(TIM2_IT_Update) 
          
       5. Call the TIM2_Cmd(ENABLE) function to enable the TIM2 counter.
       
       Note1: All other functions can be used separately to modify, if needed,
          a specific feature of the Timer. 

@endverbatim
  * @{
  */

/**
  * @brief  Deinitialize the TIM2 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM2_DeInit(void)
{
  TIM2->CR1 = TIM_CR1_RESET_VALUE;
  TIM2->CR2 = TIM_CR2_RESET_VALUE;
  TIM2->SMCR = TIM_SMCR_RESET_VALUE;
  TIM2->ETR = TIM_ETR_RESET_VALUE;
  TIM2->IER = TIM_IER_RESET_VALUE;
  TIM2->SR2 = TIM_SR2_RESET_VALUE;

  /* Disable channels */
  TIM2->CCER1 = TIM_CCER1_RESET_VALUE;
  /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
  TIM2->CCMR1 = 0x01;/*TIM2_ICxSource_TIxFPx */
  TIM2->CCMR2 = 0x01;/*TIM2_ICxSource_TIxFPx */

  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM2->CCER1 = TIM_CCER1_RESET_VALUE;
  TIM2->CCMR1 = TIM_CCMR1_RESET_VALUE;
  TIM2->CCMR2 = TIM_CCMR2_RESET_VALUE;

  TIM2->CNTRH = TIM_CNTRH_RESET_VALUE;
  TIM2->CNTRL = TIM_CNTRL_RESET_VALUE;

  TIM2->PSCR = TIM_PSCR_RESET_VALUE;

  TIM2->ARRH = TIM_ARRH_RESET_VALUE;
  TIM2->ARRL = TIM_ARRL_RESET_VALUE;

  TIM2->CCR1H = TIM_CCR1H_RESET_VALUE;
  TIM2->CCR1L = TIM_CCR1L_RESET_VALUE;
  TIM2->CCR2H = TIM_CCR2H_RESET_VALUE;
  TIM2->CCR2L = TIM_CCR2L_RESET_VALUE;


  TIM2->OISR = TIM_OISR_RESET_VALUE;
  TIM2->EGR = 0x01;/* TIM_EGR_UG */
  TIM2->BKR = TIM_BKR_RESET_VALUE;
  TIM2->SR1 = TIM_SR1_RESET_VALUE;
}

/**
  * @brief  Initializes the TIM2 Time Base Unit according to the specified  parameters.
  * @param  TIM2_Prescaler: Prescaler 
  *          This parameter can be one of the following values:
  *            @arg TIM2_Prescaler_1: Time base Prescaler = 1 (No effect)
  *            @arg TIM2_Prescaler_2: Time base Prescaler = 2
  *            @arg TIM2_Prescaler_4: Time base Prescaler = 4
  *            @arg TIM2_Prescaler_8: Time base Prescaler = 8
  *            @arg TIM2_Prescaler_16: Time base Prescaler = 16
  *            @arg TIM2_Prescaler_32: Time base Prescaler = 32
  *            @arg TIM2_Prescaler_64: Time base Prescaler = 64
  *            @arg TIM2_Prescaler_128: Time base Prescaler = 128                            
  * @param  TIM2_CounterMode: Counter mode
  *          This parameter can be one of the following values:
  *            @arg TIM2_CounterMode_Up: Counter Up Mode
  *            @arg TIM2_CounterMode_Down: Counter Down Mode
  *            @arg TIM2_CounterMode_CenterAligned1: Counter Central aligned Mode 1
  *            @arg TIM2_CounterMode_CenterAligned2: Counter Central aligned Mode 2
  *            @arg TIM2_CounterMode_CenterAligned3: Counter Central aligned Mode 3        
  * @param  TIM2_Period: This parameter must be a value between 0x0000 and 0xFFFF.
  * @retval None
  */

void TIM2_TimeBaseInit(TIM2_Prescaler_TypeDef TIM2_Prescaler,
                       TIM2_CounterMode_TypeDef TIM2_CounterMode,
                       uint16_t TIM2_Period)
{

  //assert_param(IS_TIM2_PRESCALER(TIM2_Prescaler));
  //assert_param(IS_TIM2_COUNTER_MODE(TIM2_CounterMode));



  /* Set the Autoreload value */
  TIM2->ARRH = (uint8_t)(TIM2_Period >> 8) ;
  TIM2->ARRL = (uint8_t)(TIM2_Period);

  /* Set the Prescaler value */
  TIM2->PSCR = (uint8_t)(TIM2_Prescaler);

  /* Select the Counter Mode */
  TIM2->CR1 &= (uint8_t)((uint8_t)(~TIM_CR1_CMS)) & ((uint8_t)(~TIM_CR1_DIR));
  TIM2->CR1 |= (uint8_t)(TIM2_CounterMode);

  /* Generate an update event to reload the Prescaler value immediately */
  //TIM2->EGR = TIM2_EventSource_Update;
}












/**
  * @brief  Enables or disables TIM2 peripheral Preload register on ARR.
  * @param  NewState: The new state of the TIM2 peripheral Preload register.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_ARRPreloadConfig(FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Set or Reset the ARPE Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR1 |= TIM_CR1_ARPE;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_ARPE);
  }
}



/**
  * @brief  Enables or disables the TIM2 peripheral.
  * @param  NewState: The new state of the TIM2 peripheral.
  *          This parameter can be ENABLE or DISABLE
  * @retval None
  */
void TIM2_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM2->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    TIM2->CR1 &= (uint8_t)(~TIM_CR1_CEN);
  }
}







void TIM2_ITConfig(TIM2_IT_TypeDef TIM2_IT, FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_TIM2_IT(TIM2_IT));
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM2->IER |= (uint8_t)TIM2_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM2->IER &= (uint8_t)(~(uint8_t)TIM2_IT);
  }
}



void TIM2_ClearFlag(TIM2_FLAG_TypeDef TIM2_FLAG)
{
  /* Check the parameters */
  //assert_param(IS_TIM2_CLEAR_FLAG((uint16_t)TIM2_FLAG));
  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
  TIM2->SR1 = (uint8_t)(~(uint8_t)(TIM2_FLAG));
  TIM2->SR2 = (uint8_t)(~(uint8_t)((uint16_t)TIM2_FLAG >> 8));
}



/**
  * @brief  Clears the TIM's interrupt pending bits.
  * @param  TIM2_IT: Specifies the pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM2_IT_Update: Update
  *            @arg TIM2_IT_CC1: Capture Compare Channel1
  *            @arg TIM2_IT_CC2: Capture Compare Channel2 
  *            @arg TIM2_IT_Trigger: Trigger 
  *            @arg TIM2_IT_Break: Break  
  * @retval None
  */
void TIM2_ClearITPendingBit(TIM2_IT_TypeDef TIM2_IT)
{
  /* Check the parameters */
  //assert_param(IS_TIM2_IT(TIM2_IT));

  /* Clear the IT pending Bit */
  TIM2->SR1 = (uint8_t)(~(uint8_t)TIM2_IT);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
