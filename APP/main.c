#include "main.h"

volatile uint8_t flag_10ms = 0;


Typdef_DataFormat DataFormat = {0};

Typdef_ProgramPara ProgramPara = {0};
volatile uint8_t Receive = 0;
volatile uint8_t Mode = 0;



char ubUartRxBuf[RXMAX] = {0};//�������洮������

RTC_TimeTypeDef GETRTC_Time;
RTC_DateTypeDef GETRTC_Data;

void ProcessSensors(void);


/* Private functions prototype -----------------------------------------------*/



void NETWORKING_FLAG(void)
{
	static uint8_t i = 0;
	static bool flag = FALSE;
	if(Mode == Mode_Time){
		return ;
	}
	if(ProgramPara.Network_flag == 1 && Mode != Mode_Init){//�����ɹ�
		ProgramPara.Key_Type = 0;
		OLED_net(0,0,TRUE);	
		delay_ms2(2);

	}
	else if((ProgramPara.Network_flag == 2) || (ProgramPara.Network_flag == 3)){//ʧ�ܻ���������

		if(++i > 100){
			i = 0;
			if(flag == FALSE){
				OLED_net(0,0,flag);
				flag = TRUE;
			}
			else{
				OLED_net(0,0,flag);
				flag = FALSE;
			}
			
		}	
	}
}


int main( void )
{	
    uint8_t Mode1 = 0;

    InitAll();
	//Read_ChipID_Init(&ProgramPara);
    Mode = Mode_Init;
    ProgramPara.Battfresh_flag = TRUE;
    //Batt_Test();
    //Batt_Test();
    if ((((uint8_t)WAKEKEY_PORT->IDR) & WAKEKEY_PIN) == 0x00){
        delay_ms(10);
        if ((((uint8_t)WAKEKEY_PORT->IDR) & WAKEKEY_PIN) == 0x00){
            ProgramPara.Key_Type = 0;
            SetBit(ProgramPara.Key_Type,2);
        }
    }
    delay_ms(700);
    //Batt_Test();
    Usart1Init();//���ڳ�ʼ��
    while(1){

         
       while(!flag_10ms);//��������³���10msѭ��һ��
        flag_10ms = 0;
         mykey_Press();

        if(++ProgramPara.Cnt_Minite >= 18000){//���3min
          if(Mode != Mode_Init)
          {
            if(Mode != Mode_Charge){
              if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0){
              }
              else{		
                Mode_haltfun();//�͹���ģʽ
              }
            }
          }

        ProgramPara.Cnt_Minite = 0;

        }

        Batt_Test();
        UartWorking();
		
        NETWORKING_FLAG();
		



        if(Mode != Mode_Init)
        {

          if(++ProgramPara.Refresh_Minite >= 200 && (ProgramPara.Refresh_flag == FALSE)){
                  ProgramPara.Refresh_flag = TRUE;//ˢ����Ļ
                 	 
                  ProgramPara.Refresh_Minite = 0;
          }
		  if(++ProgramPara.Batt_Minite >= 300 ){
                  ProgramPara.Battfresh_flag = TRUE;//ˢ����Ļ
                  ProgramPara.Batt_Minite = 0;
          }
        }
        //if((Mode != Mode_Pm2) && (Mode != Mode_Pm10) && (Mode != Mode_Time) && (Mode != Mode_Charge) && (Mode != Mode_Init))
        //{
           // OLED_Clear();
          //  Mode = Mode1;//Mode_Pm2;
       // }
        switch(Mode){
            case Mode_Init:Board_Init(); Mode1 = Mode;        
            break;	
            case Mode_Pm2:Pm_Detect();Mode1 = Mode;
            break;
            case Mode_Pm10:Pm10_Detect();Mode1 = Mode;
            break;

            case Mode_Time:Get_TheTime();Mode1 = Mode;
            break;
            case Mode_Charge:    
				
                if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0){
                }
                else{ 	
                      Mode_haltfun();//�͹���ģʽ
                }
               
              	Mode1 = Mode;
              	
            break;
            default:OLED_Clear();Mode = Mode_Pm2;
            break;

        }
        
        
        
   }
       
}





void InitAll(void){
    InitCpuClock();//�ó���������Ϊ�ⲿʱ�� ����Ƶ
    RTC_CLOCK_Init();
	
    KEY_Input_Init();//���Ѱ�����ʼ��
    LED_Init();//LED��ʼ��
    GPIO_Init(OLED_SCLK_PORT, (GPIO_Pin_TypeDef)OLED_SCLK_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_SDIN_PORT, (GPIO_Pin_TypeDef)OLED_SDIN_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_RST_PORT, (GPIO_Pin_TypeDef)OLED_RST_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_DC_PORT, (GPIO_Pin_TypeDef)OLED_DC_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_CS_PORT, (GPIO_Pin_TypeDef)OLED_CS_PINS, GPIO_Mode_Out_PP_Low_Fast);
    OLED_Init();		//��ʼ��OLED  
    InitTimer2();//����ϵͳ�ܶ�ʱ��2ms��һ���ж�
    ITC->ISPR4 &= 0xF3;//����ʱ��2�����ȼ����ͣ�����UART�ж�
    Sensor_ADC_Init();//ADC��ʼ��

    Sensor_ADC_detect_Init(ADC_Channel_0);//��ؼ��
    MCU_Gpio_Init();//5V���ƽų�ʼ��
    Batt_Test();
    Batt_Test();
    
    //GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
    RTC_GetDate(RTC_Format_BIN , &GETRTC_Data);
    RTC_GetTime(RTC_Format_BIN , &GETRTC_Time);  
    //EEPROM_INIT();
    enableInterrupts();//�����ж�
    WWDG->WR = WWDG_WR_RESET_VALUE;
    WWDG->CR = (uint8_t)((uint8_t)(WWDG_CR_WDGA | WWDG_CR_T6) | (uint8_t)WWDG_CNT);
    WWDG->WR = (uint8_t)((uint8_t)(~WWDG_CR_WDGA) & (uint8_t)(WWDG_CR_T6 | WWDG_WIN));

}
/**
  * @brief  Deinitializes the Remapping registers to their default reset values.
  * @param  None
  * @retval None
  */
void SYSCFG_REMAPDeInit(void)
{
  /*!< Set RMPCR1 to reset value */
  SYSCFG->RMPCR1 = SYSCFG_RMPCR1_RESET_VALUE;

  /*!< Set RMPCR2 to reset value */
  SYSCFG->RMPCR2 = SYSCFG_RMPCR2_RESET_VALUE;

  /*!< Set RMPCR3 to reset value */
  SYSCFG->RMPCR3 = SYSCFG_RMPCR3_RESET_VALUE;
}

void SYSCFG_REMAPPinConfig(REMAP_Pin_TypeDef REMAP_Pin, FunctionalState NewState)
{
  uint8_t regindex = 0;


  /* Read register index */
  regindex = (uint8_t) ((uint16_t) REMAP_Pin >> 8);

  /* Check if REMAP_Pin is in RMPCR1 register */
  if (regindex == 0x01)
  {
    SYSCFG->RMPCR1 &= (uint8_t)((uint8_t)((uint8_t)REMAP_Pin << 4) | (uint8_t)0x0F);
    if (NewState != DISABLE)
    {
      SYSCFG->RMPCR1 |= (uint8_t)((uint16_t)REMAP_Pin & (uint16_t)0x00F0);
    }
  }
  /* Check if REMAP_Pin is in RMPCR2 register */
  else if (regindex == 0x02)
  {
    if (NewState != DISABLE)
    {
      SYSCFG->RMPCR2 |= (uint8_t) REMAP_Pin;
    }
    else
    {
      SYSCFG->RMPCR2 &= (uint8_t)((uint16_t)(~(uint16_t)REMAP_Pin));
    }
  }
  /* REMAP_Pin is in RMPCR3 register */
  else
  {
    if (NewState != DISABLE)
    {
      SYSCFG->RMPCR3 |= (uint8_t) REMAP_Pin;
    }
    else
    {
      SYSCFG->RMPCR3 &= (uint8_t)((uint16_t)(~(uint16_t)REMAP_Pin));
    }
  }
}


/*******************************************************************************
* Function Name  : Usart1Init.
* Description    : Usart1 Init, .
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Usart1Init(void)
{	//SYSCFG_REMAPDeInit();
	SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC,ENABLE);//remap uart1�ܽ�

    CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
    //GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);//TXD
   // GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_In_PU_No_IT);//RXD
    USART_DeInit(USART1);       //��λUART1 
    /*uart1 ������9600��8bit(����)������rxd*/
    USART_Init(USART1,(uint32_t)9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_Rx|USART_Mode_Tx) );
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    USART_Cmd(USART1,ENABLE);
   
}

/*******************************************************************************
* Function Name  : MCU_Gpio_Init.
* Description    : gpio init , .
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MCU_Gpio_Init(void)
{	
	//5v_CE��λ���� �Ȳ���������Ȼ���ӻ��޷����� 
    GPIO_Init(C5VCE_PORT,C5VCE_PIN,GPIO_Mode_Out_PP_Low_Slow);

	// CH_PD���ƽ�
    GPIO_Init(GPIOD,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Fast);
    GPIO_WriteLow(GPIOD,GPIO_Pin_2);
    //delay_ms(10);
    //GPIO_WriteHigh(GPIOD,GPIO_Pin_2);
    
	//����־λ ����ܽ�
    GPIO_Init(CHARGESTATUS_PORT, CHARGESTATUS_PIN , GPIO_Mode_In_FL_IT);
	EXTI_SetPinSensitivity(EXTI_Pin_5 , EXTI_Trigger_Rising);  //Portx�˿�bit5 �ⲿ�ж���2Ϊ�½��ش����ж�
 

}



/*******************************************************************************
* Function Name  : InitCpuClock.
* Description    : Initial CPU clock, .
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void InitCpuClock(void){

#ifdef HSI_CLOCK
        //CLK_DeInit();
        //CLK_HSEConfig(CLK_HSE_OFF);//ʧ���ⲿʱ��
        CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//�ڲ�����Ƶ
       
		
        CLK_ClockSecuritySystemEnable();
        CLK_HSICmd(ENABLE);
#endif    

      


}
void InitTimer2(void){


  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);//����TIM2

  TIM2_TimeBaseInit(TIM2_Prescaler_1,TIM2_CounterMode_Up,(16000 * 2));//����Ƶ 2����һ�ν����ж�
  TIM2_ClearFlag(TIM2_FLAG_Update);
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update, ENABLE);//ʹ�����ϼ�������ж�
  TIM2_Cmd(ENABLE);  
}



void Read_ChipID_Init(Typdef_ProgramPara *programpara)
{
  uint8_t i;
//  uint8_t privilegeID[8] = {0};
  
  uint8_t *pIDStart=(uint8_t *)(ID_BaseAddress + 4);//ֻ�����8���ֽ�  
  for(i=0;i<10;i++)//��ֹ©�� ���Զ������
  {
    readSomeByte(DEVID_BaseAddress,programpara->Dev_ID,10);
    if(programpara->Dev_ID[0] == 'D' && programpara->Dev_ID[1] == 'A')//���EEPROM��ǰ���ֽ���GA�Ļ�
    {
      break;
    }           
  }
  
  if(programpara->Dev_ID[0] != 'D' && programpara->Dev_ID[1] != 'A')//���EEPROM��ǰ���ֽڲ���GA�Ļ�   
  {
    programpara->Dev_ID[0] = 'D';
    programpara->Dev_ID[1] = 'A';
    programpara->Dev_ID[2] = 'F';
    for(i = 0; i<7;i++)
    {
         programpara->Dev_ID[i+3] = *pIDStart++;//�Զ����ֽ��еĺ���7�ֽ�ΪID
    }

  }   

}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
//uint32_t theline = 0;
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//theline = line;
  /* Infinite loop */
//  theline = line;
  while (1)
  {
    
  }
}
#endif
