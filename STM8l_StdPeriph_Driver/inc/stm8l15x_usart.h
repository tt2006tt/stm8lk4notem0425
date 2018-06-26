/**
  ********************************************************************************
  * @file    stm8l15x_usart.h
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   This file contains all the functions prototypes for the USART firmware
  *          library.
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
#ifndef __STM8L15x_USART_H
#define __STM8L15x_USART_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8l15x_clk.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */
/** @addtogroup USART
  * @{
  */ 
  
/* Exported types ------------------------------------------------------------*/

/** @defgroup USART_Exported_Types
  * @{
  */





typedef enum 
{ 
  USART_IT_TXE        = (uint16_t)0x0277, /*!< Transmit interrupt */
  USART_IT_TC         = (uint16_t)0x0266, /*!< Transmission Complete interrupt */
  USART_IT_RXNE       = (uint16_t)0x0255, /*!< Receive interrupt */
  USART_IT_IDLE       = (uint16_t)0x0244, /*!< IDLE line interrupt */
  USART_IT_OR         = (uint16_t)0x0235, /*!< Overrun Error interrupt */
  USART_IT_PE         = (uint16_t)0x0100, /*!< Parity Error interrupt */
  USART_IT_ERR        = (uint16_t)0x0500, /*!< Error interrupt */
  USART_IT_NF         = (uint16_t)0x0102, /*!< Noise Error interrupt */
  USART_IT_FE         = (uint16_t)0x0101  /*!< Frame Error interrupt */
} USART_IT_TypeDef;


/**
  * @brief USART Flag possible values
  */
typedef enum 
{	
	USART_FLAG_TXE	   = (uint16_t)0x0080, /*!< Transmit Data Register Empty flag */
	USART_FLAG_TC    = (uint16_t)0x0040, /*!< Transmission Complete flag */
	USART_FLAG_RXNE  = (uint16_t)0x0020, /*!< Read Data Register Not Empty flag */
	USART_FLAG_IDLE  = (uint16_t)0x0010, /*!< Idle line detected flag */
	USART_FLAG_OR    = (uint16_t)0x0008, /*!< OverRun error flag */
	USART_FLAG_NF    = (uint16_t)0x0004, /*!< Noise error flag */
	USART_FLAG_FE    = (uint16_t)0x0002, /*!< Framing Error flag */
	USART_FLAG_PE    = (uint16_t)0x0001, /*!< Parity Error flag */
	USART_FLAG_SBK   = (uint16_t)0x0101  /*!< Send Break characters Flag */
} USART_FLAG_TypeDef;



typedef enum
{
  USART_StopBits_1   = (uint8_t)0x00, /*!< One stop bit is transmitted at the end of frame*/
  USART_StopBits_2   = (uint8_t)0x20, /*!< Two stop bits are transmitted at the end of frame*/
  USART_StopBits_1_5 = (uint8_t)0x30  /*!< One and half stop bits*/
} USART_StopBits_TypeDef;


/** @defgroup USART_Parity
  * @{
  */
typedef enum
{
  USART_Parity_No    = (uint8_t)0x00,      /*!< No Parity*/
  USART_Parity_Even  = (uint8_t)0x04,      /*!< Even Parity*/
  USART_Parity_Odd   = (uint8_t)0x06       /*!< Odd Parity*/
} USART_Parity_TypeDef;




typedef enum
{
  USART_WordLength_8b = (uint8_t)0x00,  /*!< 8 bits Data */
  USART_WordLength_9b = (uint8_t)0x10   /*!< 9 bits Data */
} USART_WordLength_TypeDef;




typedef enum
{
  USART_Mode_Rx    = (uint8_t)0x04,  /*!< Receive Enable */
  USART_Mode_Tx    = (uint8_t)0x08   /*!< Transmit Enable */
} USART_Mode_TypeDef;





/* Exported functions ------------------------------------------------------- */
	
/*  Function used to set the USART configuration to the default reset state ***/ 
void USART_DeInit(USART_TypeDef* USARTx);

/* Initialization and Configuration functions *********************************/
void USART_Init(USART_TypeDef* USARTx, uint32_t BaudRate, USART_WordLength_TypeDef
                USART_WordLength, USART_StopBits_TypeDef USART_StopBits,
                USART_Parity_TypeDef USART_Parity, USART_Mode_TypeDef USART_Mode);

void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);


/* Interrupts and flags management functions **********************************/
void USART_ITConfig(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT,
                    FunctionalState NewState);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, USART_IT_TypeDef USART_IT);

FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, USART_FLAG_TypeDef USART_FLAG);
void uartSendDataBuf(uint8_t *tempbuf,uint8_t buflen);


#endif /* __STM8L15x_USART_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
