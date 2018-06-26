#include "main.h"

volatile uint8_t flag_10ms = 0;


Typdef_DataFormat DataFormat = {0};

Typdef_ProgramPara ProgramPara = {0};
volatile uint8_t Receive = 0;
volatile uint8_t Mode = 0;



char ubUartRxBuf[RXMAX] = {0};//用来储存串口数据

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
	if(ProgramPara.Network_flag == 1 && Mode != Mode_Init){//连网成功
		ProgramPara.Key_Type = 0;
		OLED_net(0,0,TRUE);	
		delay_ms2(2);

	}
	else if((ProgramPara.Network_flag == 2) || (ProgramPara.Network_flag == 3)){//失败或者配网中

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
    Usart1Init();//串口初始化
    while(1){

         
       while(!flag_10ms);//正常情况下程序10ms循环一次
        flag_10ms = 0;
         mykey_Press();

        if(++ProgramPara.Cnt_Minite >= 18000){//大概3min
          if(Mode != Mode_Init)
          {
            if(Mode != Mode_Charge){
              if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0){
              }
              else{		
                Mode_haltfun();//低功耗模式
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
                  ProgramPara.Refresh_flag = TRUE;//刷新屏幕
                 	 
                  ProgramPara.Refresh_Minite = 0;
          }
		  if(++ProgramPara.Batt_Minite >= 300 ){
                  ProgramPara.Battfresh_flag = TRUE;//刷新屏幕
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
                      Mode_haltfun();//低功耗模式
                }
               
              	Mode1 = Mode;
              	
            break;
            default:OLED_Clear();Mode = Mode_Pm2;
            break;

        }
        
        
        
   }
       
}





void InitAll(void){
    InitCpuClock();//该程序中配置为外部时钟 不分频
    RTC_CLOCK_Init();
	
    KEY_Input_Init();//唤醒按键初始化
    LED_Init();//LED初始化
    GPIO_Init(OLED_SCLK_PORT, (GPIO_Pin_TypeDef)OLED_SCLK_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_SDIN_PORT, (GPIO_Pin_TypeDef)OLED_SDIN_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_RST_PORT, (GPIO_Pin_TypeDef)OLED_RST_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_DC_PORT, (GPIO_Pin_TypeDef)OLED_DC_PINS, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_CS_PORT, (GPIO_Pin_TypeDef)OLED_CS_PINS, GPIO_Mode_Out_PP_Low_Fast);
    OLED_Init();		//初始化OLED  
    InitTimer2();//用于系统总定时，2ms进一次中断
    ITC->ISPR4 &= 0xF3;//将定时器2的优先级调低，低于UART中断
    Sensor_ADC_Init();//ADC初始化

    Sensor_ADC_detect_Init(ADC_Channel_0);//电池检测
    MCU_Gpio_Init();//5V控制脚初始化
    Batt_Test();
    Batt_Test();
    
    //GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
    RTC_GetDate(RTC_Format_BIN , &GETRTC_Data);
    RTC_GetTime(RTC_Format_BIN , &GETRTC_Time);  
    //EEPROM_INIT();
    enableInterrupts();//开总中断
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
	SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC,ENABLE);//remap uart1管脚

    CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
    //GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);//TXD
   // GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_In_PU_No_IT);//RXD
    USART_DeInit(USART1);       //复位UART1 
    /*uart1 波特率9600，8bit(数据)，开启rxd*/
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
	//5v_CE脚位控制 先不开启，不然板子会无法运行 
    GPIO_Init(C5VCE_PORT,C5VCE_PIN,GPIO_Mode_Out_PP_Low_Slow);

	// CH_PD控制脚
    GPIO_Init(GPIOD,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Fast);
    GPIO_WriteLow(GPIOD,GPIO_Pin_2);
    //delay_ms(10);
    //GPIO_WriteHigh(GPIOD,GPIO_Pin_2);
    
	//充电标志位 输入管脚
    GPIO_Init(CHARGESTATUS_PORT, CHARGESTATUS_PIN , GPIO_Mode_In_FL_IT);
	EXTI_SetPinSensitivity(EXTI_Pin_5 , EXTI_Trigger_Rising);  //Portx端口bit5 外部中断线2为下降沿触发中断
 

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
        //CLK_HSEConfig(CLK_HSE_OFF);//失能外部时钟
        CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//内部不分频
       
		
        CLK_ClockSecuritySystemEnable();
        CLK_HSICmd(ENABLE);
#endif    

      


}
void InitTimer2(void){


  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);//启动TIM2

  TIM2_TimeBaseInit(TIM2_Prescaler_1,TIM2_CounterMode_Up,(16000 * 2));//不分频 2毫秒一次进入中断
  TIM2_ClearFlag(TIM2_FLAG_Update);
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update, ENABLE);//使能向上计数溢出中断
  TIM2_Cmd(ENABLE);  
}



void Read_ChipID_Init(Typdef_ProgramPara *programpara)
{
  uint8_t i;
//  uint8_t privilegeID[8] = {0};
  
  uint8_t *pIDStart=(uint8_t *)(ID_BaseAddress + 4);//只读最后8个字节  
  for(i=0;i<10;i++)//防止漏读 所以多读几遍
  {
    readSomeByte(DEVID_BaseAddress,programpara->Dev_ID,10);
    if(programpara->Dev_ID[0] == 'D' && programpara->Dev_ID[1] == 'A')//如果EEPROM中前两字节是GA的话
    {
      break;
    }           
  }
  
  if(programpara->Dev_ID[0] != 'D' && programpara->Dev_ID[1] != 'A')//如果EEPROM中前两字节不是GA的话   
  {
    programpara->Dev_ID[0] = 'D';
    programpara->Dev_ID[1] = 'A';
    programpara->Dev_ID[2] = 'F';
    for(i = 0; i<7;i++)
    {
         programpara->Dev_ID[i+3] = *pIDStart++;//以独有字节中的后面7字节为ID
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
