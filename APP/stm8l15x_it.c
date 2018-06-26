/**
  ******************************************************************************
  * @file    TIM2/TIM2_TRIGLSE/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.5.2
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
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
#include "stm8l15x_it.h"
#include "main.h"


uint8_t Cnt_10ms = 0;
/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM2_TRIGLSE
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(NonHandledInterrupt, 0)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler, 4)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler, 6)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */

}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler, 8)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler, 9)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler, 11)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler, 12)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler, 13)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
	  ProgramPara.Refresh_flag = FALSE;//ˢ����Ļ
	  ProgramPara.Flag_wakeup = TRUE;//���ѱ�־
	  //ProgramPara.Flag_wakeup = FALSE;//���ѱ�־
	 // if(Mode == Mode_Charge){
		//LEDB_OFF();
	//	LEDR_OFF();
	//	LEDG_OFF();
	//	Mode = Mode_Time;
	//  }
	  //GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
  	  //GPIO_WriteHigh(GPIOD,GPIO_Pin_2);
	  EXTI_ClearITPendingBit(EXTI_IT_Pin5);//�����־λ

}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler, 14)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  EXTI_ClearITPendingBit(EXTI_IT_Pin6);//�����־λ

  
  
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler, 15)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  ProgramPara.Refresh_flag = TRUE;//ˢ����Ļ
  ProgramPara.Flag_wakeup = TRUE;//���ѱ�־
  ProgramPara.Cnt_Minite = 0; //���¿�ʼ��ʱ
	
  OLED_Display_On();

  if(Mode == Mode_Charge){
  	LEDB_OFF();
	//USART_Init(USART1,(uint32_t)9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_Rx|USART_Mode_Tx) );
	//GPIO_Init(GPIOD,GPIO_Pin_2,GPIO_Mode_Out_PP_High_Slow);
  	Mode = Mode_Init;
  }
  //GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
  //GPIO_WriteHigh(GPIOD,GPIO_Pin_2);
  EXTI_ClearITPendingBit(EXTI_IT_Pin7);//�����־λ
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler, 16)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler, 17)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler, 18)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
    WWDG_SetCounter(WWDG_CNT);//ι��
    if(++Cnt_10ms >=5 &&(flag_10ms == 0))
    {	
    	if(Mode == Mode_Init){
    		Cnt_Init++;
    	}
        flag_10ms = 1;
        
        Cnt_10ms = 0;
    }
	
    

  TIM2_ClearITPendingBit(TIM2_IT_Update);
}


/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler, 20)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler, 21)
{
  /* In order to detect unexpected events during development,
	 it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler, 22)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */

}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
u16 temp = 0;
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler, 23)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  /*
  if(GPIO_ReadInputDataBit(GPIOD,(GPIO_Pin_1)))
  {
  	xxxx++;
  }
  else
  {
  	xxxx1++;
  }
  temp =  xxxx + xxxx1;
  	if(temp >= 1000)
	{
		xxxx = xxxx;
		ProgramPara.PM25.Num = xxxx;//UG/M3
		xxxx = 0;
		xxxx1 = 0;
	}
	*/
  //TIM1_ClearITPendingBit(TIM1_IT_Update);
 
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */


}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
  //�ʹ��������жϳ�ͻ
  /*
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler, 25)
{
  
  
}
*/

/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler, 26)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler, 27)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
 */
void UartRecvData_Proc(char * buf,uint8_t index)
{
	
	uint8_t i = index;//��ʼ
	
	
	
	//if(buf[i] != 0x55){//start
		//return ; 
	//}
	i++;
	
	/*Դ��ַ*/
	DataFormat.sour_addr = buf[i];
	i++;

	/* Ŀ���ַ */
	DataFormat.dst_addr = buf[i];
	i++;
	
	//if(DataFormat.dst_addr == 0x00)
	//{
		//0x00��ʾѯ������ģ��
	//}
	
	//else if(DataFormat.dst_addr != LOCAL_ADDR)
	//{
		//return ;
	//}
	
	/*		   ���� 		*/
	DataFormat.payloadlength = buf[i];
	i++;
	
	/*		   ���� 		*/
	DataFormat.command = buf[i];
	i++;
//0x55 0x65 0x61 0x01 0x81 0x56
	
	/*����*/
	memcpy(&DataFormat.mems,&buf[i],DataFormat.payloadlength-1);
	

	switch(DataFormat.command)
	{
		case UartAirPoll: 
                        if(DataFormat.mems[0] == 0 && DataFormat.mems[1] == 0 
                           && DataFormat.mems[2] && DataFormat.mems[3] == 1)
                        {
                          Receive = 0x01;
                          return;
                        }
			ProgramPara.PM25.Arr[0] = DataFormat.mems[0];
			ProgramPara.PM25.Arr[1] = DataFormat.mems[1];
			ProgramPara.PM25.Arr[2] = DataFormat.mems[2];
			ProgramPara.PM25.Arr[3] = DataFormat.mems[3];
			ProgramPara.PM10.Arr[0] = DataFormat.mems[4];
			ProgramPara.PM10.Arr[1] = DataFormat.mems[5];
			ProgramPara.PM10.Arr[2] = DataFormat.mems[6];
			ProgramPara.PM10.Arr[3] = DataFormat.mems[7];
			if(ProgramPara.PM25.Num == 151 && Mode == Mode_Init)
			{
				ProgramPara.PM25.Num = 0;
				ProgramPara.PM10.Num = 0;
			}
			//ProgramPara.PM1_0.Arr[0] = DataFormat.mems[4];
			//ProgramPara.PM1_0.Arr[1] = DataFormat.mems[5];

			Receive = 0x01;

				
		break;
		
		case UartStopWarning: Receive = 0x02;

			
		break;
		case UartWaring: Receive = 0x03;

			
		break;
		case UartSmartconfig: Receive = 0x04;//smartconfig	

			
		break;
		case Uartledcolor: Receive = 0x05;
					
		break;
				
		case UartGetId: Receive = 0x06;

		break;
		case UartNewId_Save: Receive = 0x07;

		break;
		case UartFirstLink: Receive = 0x08;
			
		break;
		case UartSetPpm: Receive = 0x09;
			
		break;
		
		case UartAirSetTime: Receive = 0x0A;
			
		break;
				

	}
	
	
}


 uint8_t ubIndex = 0;
 uint8_t rxi=0,cnt=0;
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler, 28)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  
  if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
  {
      ubUartRxBuf[ubIndex] = (uint8_t)USART1->DR;
      ubIndex++;
	  if(ubIndex >RXMAX - 1)
	  {
	  	ubIndex = 0;
		cnt = 0;
	  }
      //USART_ClearITPendingBit(USART1,USART_IT_RXNE);
      for(rxi=0;rxi<RXMAX;rxi++)
      {
         if(ubUartRxBuf[rxi]==0x55)
         {
           cnt++;
           if(ubUartRxBuf[(cnt+rxi-1)] == 0x56)
           {
              UartRecvData_Proc(ubUartRxBuf,rxi);
              memset(ubUartRxBuf,0,RXMAX);
              ubIndex = 0;
              cnt=0;
           }
           
           break;
         }
       }



           
      USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  }
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler, 29)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
