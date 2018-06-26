/**
  ******************************************************************************
  * @file    stm8l15x_usart.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Universal synchronous asynchronous receiver
  *          transmitter (USART):           
  *           - Initialization and Configuration
  *           - Data transfers
  *           - Multi-Processor Communication
  *           - Half-duplex mode
  *           - Smartcard mode
  *           - IrDA mode
  *           - DMA transfers management
  *           - Interrupts and flags management 
  *           
  *  @verbatim
  *      
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          1. Enable peripheral clock using CLK_PeripheralClockConfig(CLK_Peripheral_USARTx,
  *             ENABLE) function (Refer to the product datasheet for the available USART
  *           	peripherals)
  *
  *          2.  Enable the external Pull-up on the used USART Pins using the
  *              GPIO_ExternalPullUpConfig() function or an external pull-up equivalent resistor
	*              (RPU = 45 KOhm typical value). 
	*
  *          3. Program the Baud Rate, Word Length , Stop Bit, Parity and Mode (Receiver/Transmitter)
  *           	using the USART_Init() function.
  *
  *          4. For synchronous mode, enable the clock and program the polarity,
  *             phase and last bit using the USART_ClockInit() function.
  *
  *          5. Enable the corresponding interrupt using the function USART_ITConfig() if you need 
	*             to use interrupt mode. 
  *
  *          6. When using the DMA mode 
  *                   - Configure the DMA using DMA_Init() function
  *                   - Activate the needed channel Request using USART_DMACmd() function
  * 
  *          7. Enable the USART using the USART_Cmd() function.
  * 
  *          8. Enable the DMA using the DMA_Cmd() function, when using DMA mode. 
  *
  *          Refer to Multi-Processor, half-duplex, Smartcard, IrDA sub-sections for more details.
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
#include "stm8l15x_usart.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/** @defgroup USART 
  * @brief USART driver modules
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup USART_Private_Functions
  * @{
  */

/** @defgroup USART_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
                  Initialization and Configuration functions
 ===============================================================================  

  This subsection provides a set of functions allowing to initialize the USART 
  in asynchronous and in synchronous modes.
   - For the asynchronous mode only these parameters can be configured: 
        - Baud Rate
        - Word Length 
        - Stop Bit
        - Parity: If the parity is enabled, then the MSB bit of the data written
          in the data register is transmitted but is changed by the parity bit.
          Depending on the frame length defined by the M bit (8-bits or 9-bits),
          the possible USART frame formats are as listed in the following table:
   +-------------------------------------------------------------+     
   |   M bit |  PCE bit  |            USART frame                |
   |---------------------|---------------------------------------|             
   |    0    |    0      |    | SB | 8 bit data | STB |          |
   |---------|-----------|---------------------------------------|  
   |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|  
   |    1    |    0      |    | SB | 9 bit data | STB |          |
   |---------|-----------|---------------------------------------|  
   |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +-------------------------------------------------------------+            
        - Receiver/transmitter modes

  The USART_Init() function follows the USART  asynchronous configuration procedure
  (details for the procedure are available in reference manual (RM0031)).

  - For the synchronous mode in addition to the asynchronous mode parameters these 
    parameters should be also configured:
        - USART Clock Enabled
        - USART polarity
        - USART phase
        - USART LastBit
  
  These parameters can be configured using the USART_ClockInit() function.

@endverbatim
  * @{
  */

/**
  * @brief   Deinitializes the USART peripheral.
  * @param  USARTx: where x can be 1, 2 or 3 to select the specified USART peripheral.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{

  /* Clear the Idle Line Detected bit in the status register by a read
      to the USART_SR register followed by a Read to the USART_DR register */
  (void) USARTx->SR;
  (void) USARTx->DR;

  USARTx->BRR2 = USART_BRR2_RESET_VALUE;  /* Set USART_BRR2 to reset value 0x00 */
  USARTx->BRR1 = USART_BRR1_RESET_VALUE;  /* Set USART_BRR1 to reset value 0x00 */

  USARTx->CR1 = USART_CR1_RESET_VALUE;  /* Set USART_CR1 to reset value 0x00 */
  USARTx->CR2 = USART_CR2_RESET_VALUE;  /* Set USART_CR2 to reset value 0x00 */
  USARTx->CR3 = USART_CR3_RESET_VALUE;  /* Set USART_CR3 to reset value 0x00 */
  USARTx->CR4 = USART_CR4_RESET_VALUE;  /* Set USART_CR4 to reset value 0x00 */
}

/**
  * @brief  Initializes the USART according to the specified parameters.
  * @note   Configure in Push Pull or Open Drain mode the Tx pin by setting the
  *         correct I/O Port register according the product package and line
  *         configuration
  * @param  USARTx: where x can be 1 to select the specified USART peripheral.
  * @param  BaudRate: The baudrate.
  * @param  USART_WordLength: the word length
  *           This parameter can be one of the following values:
  *            @arg USART_WordLength_8b: 8 bits Data
  *            @arg USART_WordLength_9b: 9 bits Data  
  * @param  USART_StopBits: Stop Bit
  *           This parameter can be one of the following values:
  *            @arg USART_StopBits_1: One stop bit is transmitted at the end of frame
  *            @arg USART_StopBits_2: Two stop bits are transmitted at the end of frame
  *            @arg USART_StopBits_1_5: One and half stop bits
  * @param  USART_Parity: Parity
  *           This parameter can be one of the following values:
  *            @arg USART_Parity_No: No Parity
  *            @arg USART_Parity_Even: Even Parity
  *            @arg USART_Parity_Odd: Odd Parity    
  * @param  USART_Mode: Mode
  *           This parameter can be one of the following values:
  *            @arg USART_Mode_Rx: Receive Enable
  *            @arg USART_Mode_Tx: Transmit Enable  
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, uint32_t BaudRate, USART_WordLength_TypeDef
                USART_WordLength, USART_StopBits_TypeDef USART_StopBits,
                USART_Parity_TypeDef USART_Parity,  USART_Mode_TypeDef USART_Mode)
{
  uint32_t BaudRate_Mantissa = 0;

  /* Clear the word length and Parity Control bits */
  USARTx->CR1 &= (uint8_t)(~(USART_CR1_PCEN | USART_CR1_PS | USART_CR1_M));
  /* Set the word length bit according to USART_WordLength value */
  /* Set the Parity Control bit to USART_Parity value */
  USARTx->CR1 |= (uint8_t)((uint8_t)USART_WordLength | (uint8_t)USART_Parity);

  /* Clear the STOP bits */
  USARTx->CR3 &= (uint8_t)(~USART_CR3_STOP);
  /* Set the STOP bits number according to USART_StopBits value */
  USARTx->CR3 |= (uint8_t)USART_StopBits;

  /* Clear the LSB mantissa of USARTDIV */
  USARTx->BRR1 &= (uint8_t)(~USART_BRR1_DIVM);
  /* Clear the MSB mantissa of USARTDIV */
  USARTx->BRR2 &= (uint8_t)(~USART_BRR2_DIVM);
  /* Clear the Fraction bits of USARTDIV */
  USARTx->BRR2 &= (uint8_t)(~USART_BRR2_DIVF);

  BaudRate_Mantissa  = (uint32_t)(CLK_GetClockFreq() / BaudRate );
  /* Set the fraction of USARTDIV */
  USARTx->BRR2 = (uint8_t)((BaudRate_Mantissa >> (uint8_t)8) & (uint8_t)0xF0);
  /* Set the MSB mantissa of USARTDIV */
  USARTx->BRR2 |= (uint8_t)(BaudRate_Mantissa & (uint8_t)0x0F);
  /* Set the LSB mantissa of USARTDIV */
  USARTx->BRR1 = (uint8_t)(BaudRate_Mantissa >> (uint8_t)4);

  /* Disable the Transmitter and Receiver */
  USARTx->CR2 &= (uint8_t)~(USART_CR2_TEN | USART_CR2_REN);
  /* Set TEN and REN bits according to USART_Mode value */
  USARTx->CR2 |= (uint8_t)USART_Mode;
}


/**
  * @brief  Enable the USART peripheral.
  * @param  USARTx: where x can be 1 to select the specified USART peripheral.
  * @param  NewState: The new state of the USART Communication.
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CR1 &= (uint8_t)(~USART_CR1_USARTD); /**< USART Enable */
  }
  else
  {
    USARTx->CR1 |= USART_CR1_USARTD;  /**< USART Disable (for low power consumption) */
  }
}



/**
  * @brief  Transmits 8 bit data through the USART peripheral.
  * @param  Data: The data to transmit.
  * @retval None
  */
void USART_SendData8(USART_TypeDef* USARTx, uint8_t Data)
{
  /* Transmit Data */
  USARTx->DR = Data;
}



/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx: where x can be 1 to select the specified USART peripheral.
  * @param  USART_IT specifies the USART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg USART_IT_TXE: Transmit Data Register empty interrupt
  *            @arg USART_IT_TC: Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_OR: Overrun error interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_ERR: Error interrupt
  * @param  NewState new state of the specified USART interrupts.
    *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT, FunctionalState NewState)
{
  uint8_t usartreg, itpos = 0x00;
  //assert_param(IS_USART_CONFIG_IT(USART_IT));
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the USART register index */
  usartreg = (uint8_t)((uint16_t)USART_IT >> 0x08);
  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));

  if (NewState != DISABLE)
  {
    /**< Enable the Interrupt bits according to USART_IT mask */
    if (usartreg == 0x01)
    {
      USARTx->CR1 |= itpos;
    }
    else if (usartreg == 0x05)
    {
      USARTx->CR5 |= itpos;
    }
    /*uartreg =0x02*/
    else
    {
      USARTx->CR2 |= itpos;
    }
  }
  else
  {
    /**< Disable the interrupt bits according to USART_IT mask */
    if (usartreg == 0x01)
    {
      USARTx->CR1 &= (uint8_t)(~itpos);
    }
    else if (usartreg == 0x05)
    {
      USARTx->CR5 &= (uint8_t)(~itpos);
    }
    /*uartreg =0x02*/
    else
    {
      USARTx->CR2 &= (uint8_t)(~itpos);
    }
  }
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: Select the USARTx peripheral.
  * @param  USART_FLAG specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg USART_FLAG_TXE: Transmit Data Register empty
  *            @arg USART_FLAG_TC: Transmission Complete 
  *            @arg USART_FLAG_RXNE: Read Data Register Not Empty
  *            @arg USART_FLAG_IDLE: Idle line detected
  *            @arg USART_FLAG_OR: OverRun error
  *            @arg USART_FLAG_NF: Noise error
  *            @arg USART_FLAG_FE: Framing Error
  *            @arg USART_FLAG_PE: Parity Error
  *            @arg USART_FLAG_SBK: Send Break characters               
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, USART_FLAG_TypeDef USART_FLAG)
{
  FlagStatus status = RESET;


  if (USART_FLAG == USART_FLAG_SBK)
  {
    if ((USARTx->CR2 & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  else
  {
    if ((USARTx->SR & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  /* Return the USART_FLAG status*/
  return status;
}






/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx: where x can be 1 to select the specified USART peripheral.
  * @param  USART_IT: Specifies the USART interrupt pending bit to check.
  *         This parameter can be one of the following values:
  *            @arg USART_IT_TXE: Transmit Data Register empty interrupt
  *            @arg USART_IT_TC: Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_OR: OverRun Error interrupt
  *            @arg USART_IT_PE: Parity Error interrupt
  *            @arg USART_IT_FE: Frame Error interrupt
  *            @arg USART_IT_NF: Noise Flag Error interrupt
  * @retval ITStatus The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t temp = 0;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  uint8_t enablestatus = 0;

  /* Check parameters */
  //assert_param(IS_USART_GET_IT(USART_IT));

  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));
  /* Get the USART IT index */
  itmask1 = (uint8_t)((uint8_t)USART_IT >> (uint8_t)4);
  /* Set the IT mask*/
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);

  /* Check the status of the specified USART pending bit*/
  if (USART_IT == USART_IT_PE)
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USARTx->CR1 & itmask2);
    /* Check the status of the specified USART interrupt*/

    if (((USARTx->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  else if (USART_IT == USART_IT_OR)
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USARTx->CR2 & itmask2);
    /* Check the status of the specified USART interrupt*/

    temp = (uint8_t)(USARTx->CR5 & USART_CR5_EIE);

    if (( (USARTx->SR & itpos) != 0x00) && ((enablestatus || temp)))
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  else
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USARTx->CR2 & itmask2);
    /* Check the status of the specified USART interrupt*/
    if (((USARTx->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  /* Return the USART_IT status*/
  return  pendingbitstatus;
}

/**
  * @brief  Clears the USARTx抯 interrupt pending bits.
  * @param  USARTx: where x can be 1 to select the specified USART peripheral.
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *            @arg USART_IT_TC: Transmission complete interrupt.
  * @note   PE (Parity error), FE (Framing error), NE (Noise error),
  *         OR (OverRun error) and IDLE (Idle line detected) pending bits are
  *         cleared by software sequence: a read operation to USART_SR register
  *         (USART_GetITStatus()) followed by a read operation to USART_DR
  *         register (USART_ReceiveData8() or USART_ReceiveData9()).
  * @note   RXNE pending bit can be also cleared by a read to the USART_DR register
  *         (USART_ReceiveData8() or USART_ReceiveData9()).
  * @note   TC (Transmit complete) pending bit can be also cleared by software
  *         sequence: a read operation to USART_SR register (USART_GetITStatus())
  *         followed by a write operation to USART_DR register (USART_SendData8()
  *         or USART_SendData9()).
  * @note   TXE pending bit is cleared only by a write to the USART_DR register
  *         (USART_SendData8() or USART_SendData9()).
  * @retval None
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT)
{
  //assert_param(IS_USART_CLEAR_IT(USART_IT));

  /*< Clear RXNE or TC pending bit */
  USARTx->SR &= (uint8_t)(~USART_SR_TC);
}

//串口发送字符串函数
void uartSendDataBuf(uint8_t *tempbuf,uint8_t buflen){
      uint8_t i;
      for(i = 0; i < buflen; i++) {             
              while(!(SET==USART_GetFlagStatus(USART1,USART_FLAG_TXE)));//发送完成
              USART_SendData8(USART1,tempbuf[i]);
      }  
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
