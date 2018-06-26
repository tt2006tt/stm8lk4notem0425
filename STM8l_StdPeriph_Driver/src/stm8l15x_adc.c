/**
  ******************************************************************************
  * @file    stm8l15x_adc.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:           
  *           - Initialization and Configuration
  *           - Power saving
  *           - Analog Watchdog configuration              
  *           - Temperature Sensor & Vrefint (Voltage Reference internal) management 
  *           - Regular Channels Configuration
  *           - Regular Channels DMA Configuration
  *           - Injected channels Configuration      
  *           - Interrupts and flags management       
  *         
  *  @verbatim
  *                               
  *          ===================================================================      
  *                                   How to use this driver
  *          ===================================================================      
  *          1. Enable The ADC controller clock using CLK_PeripheralClockConfig() 
  *            function : CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE).
  *
  *            2. Configure the ADC Prescaler, conversion resolution and data 
  *              alignment using the ADC_Init() function.
  * 
  *            3. Activate the ADC peripheral using ADC_Cmd() function.  
  *
  *          Regular channels group configuration
  *          ====================================    
  *            - To configure the ADC regular channels group features, use 
  *              ADC_Init() and ADC_RegularChannelConfig() functions.
  *            - To activate the continuous mode, use the ADC_continuousModeCmd()
  *              function.
  *            - To configure and activate the Discontinuous mode, use the 
  *              ADC_DiscModeChannelCountConfig() and ADC_DiscModeCmd() functions.        
  *            - To read the ADC converted values, use the ADC_GetConversionValue()
  *              function.
  *
  *          DMA for Regular channels group features configuration
  *          ====================================================== 
  *           - To enable the DMA mode for regular channels group, use the 
  *             ADC_DMACmd() function.
  *           - To enable the generation of DMA requests continuously at the end
  *             of the last DMA transfer, use the ADC_DMARequestAfterLastTransferCmd() 
  *             function.    
             
  *          Injected channels group configuration
  *          =====================================    
  *            - To configure the ADC Injected channels group features, use 
  *              ADC_InjectedChannelConfig() and  ADC_InjectedSequencerLengthConfig()
  *              functions.
  *            - To activate the continuous mode, use the ADC_continuousModeCmd()
  *              function.
  *            - To activate the Injected Discontinuous mode, use the 
  *              ADC_InjectedDiscModeCmd() function.  
  *            - To activate the AutoInjected mode, use the ADC_AutoInjectedConvCmd() 
  *              function.        
  *            - To read the ADC converted values, use the ADC_GetInjectedConversionValue() 
  *              function.
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
#include "stm8l15x_adc.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the specified ADC peripheral according to the specified 
  *         parameters.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_ConversionMode : specifies the ADC conversion mode,
  *          This parameter can be one of the following values:
  *            @arg ADC_ConversionMode_Single: Single Conversion Mode
  *            @arg ADC_ConversionMode_Continuous: Continuous Conversion Mode
  * @param  ADC_Resolution : specifies the ADC Data resolution,
  *          This parameter can be one of the following values:
  *            @arg ADC_Resolution_12Bit: 12 bit resolution
  *            @arg ADC_Resolution_10Bit: 10 bit resolution
  *            @arg ADC_Resolution_8Bit: 8 bit resolution
  *            @arg ADC_Resolution_6Bit: 6 bit resolution      
  * @param  ADC_Prescaler : specifies the ADC Prescaler,
  *          This parameter can be one of the following values:
  *            @arg ADC_Prescaler_1: ADC Clock frequency is divided by 1
  *            @arg ADC_Prescaler_2: ADC Clock frequency is divided by 2
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx,
              ADC_ConversionMode_TypeDef ADC_ConversionMode,
              ADC_Resolution_TypeDef ADC_Resolution,
              ADC_Prescaler_TypeDef ADC_Prescaler)
{
  /* Check the parameters */
  //assert_param(IS_ADC_CONVERSION_MODE(ADC_ConversionMode));
  //assert_param(IS_ADC_RESOLUTION(ADC_Resolution));
  //assert_param(IS_ADC_PRESCALER(ADC_Prescaler));

  /*clear CR1 register */
  ADCx->CR1 &= (uint8_t)~(ADC_CR1_CONT | ADC_CR1_RES);

  /* set the resolution and the conversion mode */
  ADCx->CR1 |= (uint8_t)((uint8_t)ADC_ConversionMode | (uint8_t)ADC_Resolution);

  /*clear CR2 register */
  ADCx->CR2 &= (uint8_t)~(ADC_CR2_PRESC);

  /* set the Prescaler */
  ADCx->CR2 |= (uint8_t) ADC_Prescaler;
}

/**
  * @brief  Enables or disables the selected ADC peripheral.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  NewState : new state of the specified ADC peripheral.
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx,
             FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADON bit to wake up the specified ADC from power down mode */
    ADCx->CR1 |= ADC_CR1_ADON;
  }
  else
  {
    /* Disable the selected ADC peripheral */
    ADCx->CR1 &= (uint8_t)~ADC_CR1_ADON;
  }
}

/**
  Æô¶¯ADC×ª»»£¬ÓÉÈí¼þ´¥·¢Æ÷

  * @brief  Starts ADC conversion, by software trigger.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @retval None
  */
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx)
{
  /*  Start the ADC software conversion */
  ADCx->CR1 |= ADC_CR1_START;
}


 /**
  * @}
  */
/** @defgroup ADC_Group4 Channels Configuration functions
 *  @brief   Channels Configuration functions
 *
@verbatim    
 ===============================================================================
                      Channels Configuration functions
 ===============================================================================  
  This section provides functions allowing to:
   - Enable or disable the ADC channel using ADC_ChannelCmd() function,
   - Configure the channels sampling times using ADC_SamplingTimeConfig() 
     function.
     Note: there are 2 sampling times configuration values : 
            - 1st Group value : for channels 0..23  
            - 2nd Group value : for channels 24..27 (depending on the MCU 
              package density) and Temperature Sensor and Vrefint channels. 
   - Configure the channels Schmitt Trigger for each channel using 
     ADC_SchmittTriggerConfig() function.
   - Get the current ADC conversion value.
   
 @endverbatim
  * @{
  */
    
/**
  * @brief  Enables or disables the selected ADC channel(s).
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_Channels: specifies the ADC channels to be initialized
  *          This parameter can be one of the following values:
  *            @arg ADC_Channel_0: Channel 0
  *            @arg ADC_Channel_1: Channel 1
  *            @arg ADC_Channel_2: Channel 2
  *            @arg ADC_Channel_3: Channel 3
  *            @arg ADC_Channel_4: Channel 4
  *            @arg ADC_Channel_5: Channel 5
  *            @arg ADC_Channel_6: Channel 6
  *            @arg ADC_Channel_7: Channel 7
  *            @arg ADC_Channel_8: Channel 8
  *            @arg ADC_Channel_9: Channel 9
  *            @arg ADC_Channel_10: Channel 10
  *            @arg ADC_Channel_11: Channel 11
  *            @arg ADC_Channel_12: Channel 12
  *            @arg ADC_Channel_13: Channel 13
  *            @arg ADC_Channel_14: Channel 14
  *            @arg ADC_Channel_15: Channel 15
  *            @arg ADC_Channel_16: Channel 16
  *            @arg ADC_Channel_17: Channel 17
  *            @arg ADC_Channel_18: Channel 18
  *            @arg ADC_Channel_19: Channel 19
  *            @arg ADC_Channel_20: Channel 20
  *            @arg ADC_Channel_21: Channel 21
  *            @arg ADC_Channel_22: Channel 22
  *            @arg ADC_Channel_23: Channel 23
  *            @arg ADC_Channel_24: Channel 24
  *            @arg ADC_Channel_25: Channel 25
  *            @arg ADC_Channel_26: Channel 26
  *            @arg ADC_Channel_27: Channel 27
  *            @arg ADC_Channel_Vrefint: Vrefint Channel
  *            @arg ADC_Channel_TempSensor: Temperature sensor Channel
  *            @arg ADC_Channel_00To07: select from channel00 to channel07
  *            @arg ADC_Channel_08To15: select from channel08 to channel15
  *            @arg ADC_Channel_16To23: select from channel16 to channel23
  *            @arg ADC_Channel_24To27: select from channel24 to channel27
  * @param  NewState : new state of the specified ADC channel(s).
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */





/**
  * @brief  Returns the last ADC converted data.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  uint16_t tmpreg = 0;

  /* Get last ADC converted data.*/
  tmpreg = (uint16_t)(ADCx->DRH);
  tmpreg = (uint16_t)((uint16_t)((uint16_t)tmpreg << 8) | ADCx->DRL);
  
  /* Return the selected ADC conversion value */
  return (uint16_t)(tmpreg) ;
}


/**
  * @}
  */

/** @defgroup ADC_Group6 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
                   Interrupts and flags management functions
 ===============================================================================  

  This section provides functions allowing to configure the ADC Interrupts and 
  get the status and clear flags and Interrupts pending bits.
  
  The ADC provides 3 Interrupt sources and 3 Flags:
  
  Flags :
  ---------- 
     1. ADC_FLAG_OVR : Overrun detection when ADC channel converted data is lost

     2. ADC_FLAG_EOC : End of conversion - to indicate the end of a regular 
                  CHANNEL conversion or a GROUP conversions, depending of the 
                  ADC Continuous Conversion Mode (Continuous or Single 
                  conversion) and of the DMA usage.
                  Note : if DMA is used, EOC occurs at the end of the sequence 
                         conversion, else it occurs after each conversion
     3. ADC_FLAG_AWD: to indicate if the converted voltage crosses the 
                programmed Analog watchdog thresholds values.

     
  Interrupts :
  ------------
     1. ADC_IT_OVR : specifies the interrupt source for the Overrun detection event.
     2. ADC_IT_EOC : specifies the interrupt source for the End of conversion event.
     3. ADC_IT_AWD : specifies the interrupt source for the Analog watchdog event.

@endverbatim
  * @{
  */ 



/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_EOC: End of Conversion flag
  *            @arg ADC_FLAG_AWD: Analog Watchdog flag
  *            @arg ADC_FLAG_OVER: Over Run flag    
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, ADC_FLAG_TypeDef ADC_FLAG)
{
  FlagStatus flagstatus = RESET;

  /* Check the parameters */
  //assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET)
  {
    /* ADC_FLAG is set */
    flagstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    flagstatus = RESET;
  }

  /* Return the ADC_FLAG status */
  return  flagstatus;
}

/**
  * @brief  Clears the ADC's pending flags.
  * @param  ADCx where x can be 1 to select the specified ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_EOC: End of Conversion flag
  *            @arg ADC_FLAG_AWD: Analog Watchdog flag
  *            @arg ADC_FLAG_OVER: Over Run flag 
  * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx,
                   ADC_FLAG_TypeDef ADC_FLAG)
{
  /* Check the parameters */
  //assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADCx->SR = (uint8_t)~ADC_FLAG;
}


void ADC_ChannelCmd(ADC_TypeDef* ADCx, ADC_Channel_TypeDef ADC_Channels, FunctionalState NewState)
{
  uint8_t regindex = 0;
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  regindex = (uint8_t)((uint16_t)ADC_Channels >> 8);

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC channel(s). */
    ADCx->SQR[regindex] |= (uint8_t)(ADC_Channels);
  }
  else
  {
    /* Disable the selected ADC channel(s). */
    ADCx->SQR[regindex] &= (uint8_t)(~(uint8_t)(ADC_Channels));
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
