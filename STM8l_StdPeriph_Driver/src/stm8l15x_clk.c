/**
  ******************************************************************************
  * @file    stm8l15x_clk.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the clock controller (CLK) peripheral:
  *           - Internal/external clocks, CSS and CCO configuration
  *           - System clocks configuration
  *           - Peripheral clocks configuration
  *           - CSS on LSE configuration 
  *           - Low power clock configuration  
  *           - Interrupts and flags management
  *
  *  @verbatim
  *               
  *          ===================================================================
  *                               CLK specific features
  *          ===================================================================
  *    
  *          After reset the device is running from Internal High Speed oscillator
  *          divided by 8 (HSI/8 = 2MHz) with all peripherals off.
  *           - The clock for all peripherals is switched off, except for the BootROM 
  *             clock used for bootloader, in which case, the software should be properly 
  *             written to switch off that clock after the bootloader execution.     
  *
  *          Once the device starts from reset, the user application has to:
  *           - Configure the clock source to be used to drive the System clock
  *             (if the application needs higher frequency/performance)
  *           - Configure the System clock frequency  
  *           - Enable the clock for the peripheral(s) to be used
  *           - Configure the clock source(s) for peripherals which clocks are not
  *             derived from the System clock (RTC/LCD, BEEP)
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

#include "stm8l15x_clk.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/** @defgroup CLK 
  * @brief CLK driver modules
  * @{
  */ 
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Constant ---------------------------------------------------------*/
CONST uint8_t SYSDivFactor[5] = {1, 2, 4, 8, 16}; /*!< Holds the different Master clock Divider factors */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CLK_Private_Functions
  * @{
  */ 

/** @defgroup CLK_Group1 Internal and external clocks, CSS and CCO configuration functions
 *  @brief   Internal and external clocks, CSS and CCO configuration functions 
 *
@verbatim   
 ===============================================================================
      Internal/external clocks, CSS and CCO configuration functions
 ===============================================================================  

  This section provides functions allowing to configure the internal/external clocks,
  CSS and CCO pins.
  
  1. HSI (high-speed internal), 16 MHz factory-trimmed RC used directly as System 
     clock source.

  2. LSI (low-speed internal), 32 KHz low consumption RC used as IWDG and/or RTC
     and/or BEEP clock source.

  3. HSE (high-speed external), 1 to 16 MHz crystal oscillator used directly as 
     System clock source. Can be used also as RTC/LCD clock source.

  4. LSE (low-speed external), 32 KHz oscillator used as RTC/LCD and/or BEEP clock source.

  5. CSS (Clock security system), once enabled and if a HSE clock failure occurs 
     (HSE used as System clock source), the System clock is automatically switched
     to HSI and an interrupt is generated if enabled. 

  6. CCO (configurable clock output), used to output HSI, LSE, HSE, HSI, LSI
     clock (through a configurable prescaler) on PC4 pin.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the CLK peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CLK_DeInit(void)
{
  CLK->ICKCR = CLK_ICKCR_RESET_VALUE;
  CLK->ECKCR = CLK_ECKCR_RESET_VALUE;
  CLK->CRTCR = CLK_CRTCR_RESET_VALUE;
  CLK->CBEEPR = CLK_CBEEPR_RESET_VALUE;
  CLK->SWR  = CLK_SWR_RESET_VALUE;
  CLK->SWCR = CLK_SWCR_RESET_VALUE;
  CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
  CLK->PCKENR1 = CLK_PCKENR1_RESET_VALUE;
  CLK->PCKENR2 = CLK_PCKENR2_RESET_VALUE;
  CLK->PCKENR3 = CLK_PCKENR3_RESET_VALUE;
  CLK->CSSR  = CLK_CSSR_RESET_VALUE;
  CLK->CCOR = CLK_CCOR_RESET_VALUE;
  CLK->HSITRIMR = CLK_HSITRIMR_RESET_VALUE;
  CLK->HSICALR = CLK_HSICALR_RESET_VALUE;
  CLK->HSIUNLCKR = CLK_HSIUNLCKR_RESET_VALUE;
  CLK->REGCSR = CLK_REGCSR_RESET_VALUE;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering Halt and active Halt modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from Halt and active Halt mode when the FHWU bit is
  *         set in the ICKCR register, or in case of HSE failure used as system clock
  *         (if the Clock Security System CSS is enabled).             
  * @note   HSI can not be stopped if it is used as active CCO source, as active 
  *         RTC clock, if the safe oscillator (AUX) is enabled or as system clock source,
  *         In this case, you have to select another source of the system clock 
  *         then stop the HSI.
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.  
  * @param  NewState: new state of the HSI.
    *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.  
  * @retval None
  */
void CLK_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set HSION bit */
    CLK->ICKCR |= CLK_ICKCR_HSION;
  }
  else
  {
    /* Reset HSION bit */
    CLK->ICKCR &= (uint8_t)(~CLK_ICKCR_HSION);
  }
}



/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @param  NewState : new state of LSI, value accepted ENABLE, DISABLE.
  * @retval None
  */

void CLK_LSICmd(FunctionalState NewState)
{

  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set LSION bit */
    CLK->ICKCR |= CLK_ICKCR_LSION;
  }
  else
  {
    /* Reset LSION bit */
    CLK->ICKCR &= (uint8_t)(~CLK_ICKCR_LSION);
  }
}

/**
  * @brief  Checks whether the specified CLK flag is set or not.
  * @param  CLK_FLAG : Flag to check. This parameter can be a value of @ref CLK_FLAG_TypeDef
  * @retval FlagStatus : status of the checked flag
  */
FlagStatus CLK_GetFlagStatus(CLK_FLAG_TypeDef CLK_FLAG)
{
  uint8_t reg = 0;
  uint8_t pos = 0;
  FlagStatus bitstatus = RESET;

  /* check the parameters */
  //assert_param(IS_CLK_FLAGS(CLK_FLAG));

  /* get flag register */
  reg = (uint8_t)((uint8_t)CLK_FLAG & (uint8_t)0xF0);

  /* get flag position */
  pos = (uint8_t)((uint8_t)CLK_FLAG & (uint8_t)0x0F);

  if (reg == 0x00) /* The flag to check is in CRTC Rregister */
  {
    reg = CLK->CRTCR;
  }
  else if (reg == 0x10) /* The flag to check is in ICKCR register */
  {
    reg = CLK->ICKCR;
  }
  else if (reg == 0x20) /* The flag to check is in CCOR register */
  {
    reg = CLK->CCOR;
  }
  else if (reg == 0x30) /* The flag to check is in ECKCR register */
  {
    reg = CLK->ECKCR;
  }
  else if (reg == 0x40) /* The flag to check is in SWCR register */
  {
    reg = CLK->SWCR;
  }
  else if (reg == 0x50) /* The flag to check is in CSSR register */
  {
    reg = CLK->CSSR;
  }
  else if (reg == 0x70) /* The flag to check is in REGCSR register */
  {
    reg = CLK->REGCSR;
  }
  else if (reg == 0x80) /* The flag to check is in CSSLSE_CSRregister */
  {
    reg = CSSLSE->CSR;
  }
  else /* The flag to check is in CBEEPR register */
  {
    reg = CLK->CBEEPR;
  }


  if ((reg & (uint8_t)((uint8_t)1 << (uint8_t)pos)) != (uint8_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return((FlagStatus)bitstatus);
}


/**
  * @brief  Configures the RTC clock source.
  * @param  CLK_RTCCLKSource : Specifies the RTC clock source.
  *         This parameter can be a value of @ref CLK_RTCCLKSource_TypeDef.
  * @param  CLK_RTCCLKDiv : Specifies the RTC clock source divider.
  *         This parameter can be a value of @ref CLK_RTCCLKDiv_TypeDef.
  * @retval None
  */
void CLK_RTCClockConfig(CLK_RTCCLKSource_TypeDef CLK_RTCCLKSource, CLK_RTCCLKDiv_TypeDef CLK_RTCCLKDiv)
{
  /* check the parameters */
  //assert_param(IS_CLK_CLOCK_RTC(CLK_RTCCLKSource));
  //assert_param(IS_CLK_CLOCK_RTC_DIV(CLK_RTCCLKDiv));

  /* Selects the source provided on to RTC and its divider*/
  CLK->CRTCR = (uint8_t)((uint8_t)CLK_RTCCLKSource | (uint8_t)CLK_RTCCLKDiv);
}




/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (CLK_HSE_ON or CLK_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the system.
  * @note   HSE state can not be changed if it is used as system clock. In this case,
  *         you have to select another source of the system clock then change 
  *         the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering HALT and active HALT modes.  
  * @param  CLK_HSE: specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg CLK_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg CLK_HSE_ON: turn ON the HSE oscillator
  *            @arg CLK_HSE_Bypass: HSE oscillator bypassed with external clock
  * @note   In case of Enabling HSE Bypass make sure that the HSE clock source is
  *         not used by the RTC, output or involved in a switching operation.
  * @retval None
  */
void CLK_HSEConfig(CLK_HSE_TypeDef CLK_HSE)
{
  /* Check the parameters */
  //assert_param(IS_CLK_HSE(CLK_HSE));

  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  /* Reset HSEON bit */
  CLK->ECKCR &= (uint8_t)~CLK_ECKCR_HSEON;

  /* Reset HSEBYP bit */
  CLK->ECKCR &= (uint8_t)~CLK_ECKCR_HSEBYP;

  /* Configure HSE */
  CLK->ECKCR |= (uint8_t)CLK_HSE;
}

 
uint32_t CLK_GetClockFreq(void)
{
  uint32_t clockfrequency = 0;
  uint32_t sourcefrequency = 0;
  CLK_SYSCLKSource_TypeDef clocksource = CLK_SYSCLKSource_HSI;
  uint8_t tmp = 0, presc = 0;

  /* Get SYSCLK source. */
  clocksource = (CLK_SYSCLKSource_TypeDef)CLK->SCSR;

  if ( clocksource == CLK_SYSCLKSource_HSI)
  {
    sourcefrequency = HSI_VALUE;
  }
  else if ( clocksource == CLK_SYSCLKSource_LSI)
  {
    sourcefrequency = LSI_VALUE;
  }
  else if ( clocksource == CLK_SYSCLKSource_HSE)
  {
    sourcefrequency = HSE_VALUE;
  }
  else
  {
    clockfrequency = LSE_VALUE;
  }

  /* Get System clock divider factor*/
  tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_CKM);
  presc = SYSDivFactor[tmp];

  /* Get System clock clcok frequency */
  clockfrequency = sourcefrequency / presc;

  return((uint32_t)clockfrequency);
}


/**
  * @brief  Enables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure allowing the MCU to perform rescue operations.
  * @note   Once CSS is enabled it cannot be disabled until the next reset.  
  * @param  None
  * @retval None
  */
void CLK_ClockSecuritySystemEnable(void)
{
  /* Set CSSEN bit */
  CLK->CSSR |= CLK_CSSR_CSSEN;
}

  
/**
  * @brief  Configures the system clock (SYSCLK).
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from Halt and active Halt modes, or in case
  *         of failure of the HSE used as system clock (if the Clock Security System CSS is enabled).
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked). 
  *         You can use CLK_GetSYSCLKSource() function to know which clock is
  *         currently used as system clock source. 
  * @param  CLK_SYSCLKSource: specifies the clock source used as system clock.
  *          This parameter can be one of the following values:
  *            @arg CLK_SYSCLKSource_HSI: HSI selected as system clock source
  *            @arg CLK_SYSCLKSource_HSE: HSE selected as system clock source
  *            @arg CLK_SYSCLKSource_LSI: LSI selected as system clock source
  *            @arg CLK_SYSCLKSource_LSE: LSE selected as system clock source
  * @retval None
  */
void CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_TypeDef CLK_SYSCLKSource)
{
  /* check teh parameters */
  //assert_param(IS_CLK_SOURCE(CLK_SYSCLKSource));

  /* Selection of the target clock source */
  CLK->SWR = (uint8_t)CLK_SYSCLKSource;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval Clock used as System clock (SYSCLK) source.
  *         The returned value can be one of the following:
  *         - CLK_SYSCLKSource_HSI: HSI used as system clock
  *         - CLK_SYSCLKSource_LSI: LSI used as system clock
  *         - CLK_SYSCLKSource_HSE: HSE used as system clock
  *         - CLK_SYSCLKSource_LSE: LSE used as system clock
  */
CLK_SYSCLKSource_TypeDef CLK_GetSYSCLKSource(void)
{
  return ((CLK_SYSCLKSource_TypeDef)(CLK->SCSR));
}



/**
  * @brief  Configures the System clock (SYSCLK) dividers.
  * @param  CLK_SYSCLKDiv : Specifies the system clock divider to apply.
  *          This parameter can be one of the following values:
  *            @arg CLK_SYSCLKDiv_1 
  *            @arg CLK_SYSCLKDiv_2
  *            @arg CLK_SYSCLKDiv_4
  *            @arg CLK_SYSCLKDiv_8
  *            @arg CLK_SYSCLKDiv_16
  *            @arg CLK_SYSCLKDiv_64
  *            @arg CLK_SYSCLKDiv_128
  * @retval None
  */
void CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
  /* check the parameters */
  //assert_param(IS_CLK_SYSTEM_DIVIDER(CLK_SYSCLKDiv));

  CLK->CKDIVR = (uint8_t)(CLK_SYSCLKDiv);
}

/**
* @brief  Enables or disables the specified peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @param  CLK_Peripheral: specifies the peripheral to gate its clock.
  *          This parameter can be any combination of the following values:
  *            @arg CLK_Peripheral_TIM2:       TIM2 clock
  *            @arg CLK_Peripheral_TIM3:       TIM3 clock 
  *            @arg CLK_Peripheral_TIM4:       TIM4 clock
  *            @arg CLK_Peripheral_I2C1:       I2C1 clock
  *            @arg CLK_Peripheral_SPI1:       SPI1 clock
  *            @arg CLK_Peripheral_USART1:     USART1 clock
  *            @arg CLK_Peripheral_BEEP:       BEEP clock
  *            @arg CLK_Peripheral_DAC:        DAC clock
  *            @arg CLK_Peripheral_ADC1:       ADC1 clock
  *            @arg CLK_Peripheral_TIM1:       TIM1 clock
  *            @arg CLK_Peripheral_RTC:        RTC clock
  *            @arg CLK_Peripheral_LCD:        LCD clock
  *            @arg CLK_Peripheral_DMA1:       DMA1 clock
  *            @arg CLK_Peripheral_COMP:       COMP clock
  *            @arg CLK_Peripheral_BOOTROM:    BOOTROM clock
  *            @arg CLK_Peripheral_AES:        AES clock
  *            @arg CLK_Peripheral_TIM5:       TIM5 clock
  *            @arg CLK_Peripheral_SPI2:       SPI2 clock
  *            @arg CLK_Peripheral_USART2:     USART2 clock
  *            @arg CLK_Peripheral_USART3:     USART3 clock
  *            @arg CLK_Peripheral_CSSLSE:     CSS on LSE clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
{
  uint8_t reg = 0;

  /* Check the parameters */
 // assert_param(IS_CLK_PERIPHERAL(CLK_Peripheral));
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* get flag register */
  reg = (uint8_t)((uint8_t)CLK_Peripheral & (uint8_t)0xF0);

  if ( reg == 0x00)
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR1 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR1 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
  else if (reg == 0x10)
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR2 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR2 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the peripheral Clock */
      CLK->PCKENR3 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
    }
    else
    {
      /* Disable the peripheral Clock */
      CLK->PCKENR3 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
    }
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
