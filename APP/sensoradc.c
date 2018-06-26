#include "main.h"
uint16_t  Cnt_Init = 0;




/*********************************************
函数功能：ADC_Init初始化 
输入参数：无
输出参数：无
备    注：通过修改宏定义改变所要初始化的IO
*********************************************/
#pragma optimize=none

void Sensor_ADC_Init(void){
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1 , ENABLE);              //使能ADC1时钟
  
  GPIO_Init(GPIOA , GPIO_Pin_6 , GPIO_Mode_In_FL_No_IT);  //设置PA->6 为悬空输入，并中断禁止
  
  
  ADC_Init(ADC1,
           ADC_ConversionMode_Single,   //单次转换模式
           ADC_Resolution_10Bit,        //12位精度转换械
           ADC_Prescaler_2              //时钟设置为2分频
             );  
  
  ADC_ChannelCmd(ADC1,
                 ADC_Channel_0,         //设置为通道0进行采样
                 ENABLE);
  
  ADC_Cmd(ADC1 , ENABLE);               //使能ADC  
  
}

void Sensor_ADC_detect_Init(ADC_Channel_TypeDef ADC_Channel)
{
	ADC_Init(ADC1,
                ADC_ConversionMode_Single,   //单词转换
                ADC_Resolution_10Bit, 	   //10位精度转换
                ADC_Prescaler_1			   //时钟设置为2分频
                );	


	
	if(ADC_Channel == ADC_Channel_0){
		
            ADC1->SQR[3] |= (uint8_t)(0x01);//开通道0
            ADC1->SQR[3] &= ~(uint8_t)(0x04);//关通道2
	}
	 
	 ADC_Cmd(ADC1 , ENABLE);			   //使能ADC  
	 


}


#pragma optimize=none

uint16_t Adc_Data(ADC_Channel_TypeDef ADC_Channel)
{ 

     //Sensor_ADC_detect_Init(ADC_Channel);//单次转换时必须要加这句
     ADC_SoftwareStartConv(ADC1);
     while(ADC_GetFlagStatus(ADC1 , ADC_FLAG_EOC) == 0);  //等待转换结束
     ADC_ClearFlag(ADC1 , ADC_FLAG_EOC);				  //清除中断标志


    return (ADC_GetConversionValue(ADC1)); //返回ADC结果

}

uint16_t Current_ADC_Value2[6] ={0};

//10位ADC

uint16_t Ad_sensor_detect(ADC_Channel_TypeDef ADC_Channel){
	
    static uint32_t adc_index2 = 0;
    uint16_t adc_total = 0;
    //从1开始 丢弃第一个
	adc_index2 = 0;
	adc_total = 0;

	for(uint8_t i = 0;i < 6;i++){
			
    	Current_ADC_Value2[(adc_index2++)] = Adc_Data(ADC_Channel);
    
        adc_total += Current_ADC_Value2[i];
    }
    adc_total /= 6;
    
#ifdef VDD_3_3V
	return (adc_total*33/102);//抹掉了尾数 4是为了降低尾数，防止数据溢出
#endif //自定范围 0-330 对应0-3.3V

#ifdef VDD_5_V
	return (adc_total*50/102);//自定范围 0-500 对应0-5V
	
#endif /* VDD_5_V */
}




//pm2.5检测
void Pm_Detect(void){
  
  uint8_t number[3] = {0};

  if(ProgramPara.Refresh_flag == TRUE ){
    ProgramPara.Refresh_flag = FALSE;



    if(ProgramPara.PM25.Num >= 999) ProgramPara.PM25.Num = 999;
    if(ProgramPara.PM25.Num < 100){
      number[0] = ProgramPara.PM25.Num % 10;//个位
      number[1] = ProgramPara.PM25.Num / 10;//十位

	  	
      OLED_Show32X56_Pic(0 , 1 , number[1],FALSE);//百位不显示
      OLED_Show32X56_Pic(32 , 1 , number[1],TRUE);//十位
      OLED_Show32X56_Pic(64 , 1 , number[0],TRUE);//个位
      
    }
    else{
      number[0] = ProgramPara.PM25.Num % 10;//个位
      number[1] = ProgramPara.PM25.Num % 100 / 10;//十位
      number[2] = ProgramPara.PM25.Num / 100;//百位

      OLED_Show32X56_Pic(0 , 1 , number[2],TRUE);//百位
      OLED_Show32X56_Pic(32 , 1 , number[1],TRUE);//十位
      OLED_Show32X56_Pic(64 , 1 , number[0],TRUE);//个位
      
    }


    if(ProgramPara.PM25.Num < 35){
        OLED_Showch24X24_Pic(104,5,0);//优
        LEDG_ON();
        LEDR_OFF();
    }
    else if((ProgramPara.PM25.Num < 75) && ((ProgramPara.PM25.Num >= 35))){
        OLED_Showch24X24_Pic(104,5,1);//良
        LEDG_ON();
        LEDR_OFF();
    }
    else if((ProgramPara.PM25.Num < 115) && ((ProgramPara.PM25.Num >= 75))){
        OLED_Showch24X24_Pic(104,5,2);//轻
        LEDG_ON();
        LEDR_OFF();
    }
    else if((ProgramPara.PM25.Num < 150) && ((ProgramPara.PM25.Num >= 115))){
        OLED_Showch24X24_Pic(104,5,3);//中
        LEDR_ON();
        LEDG_OFF();
    }
    else if((ProgramPara.PM25.Num < 250) && ((ProgramPara.PM25.Num >= 150))){
        OLED_Showch24X24_Pic(104,5,4);//差
        LEDR_ON();
        LEDG_OFF();
    }
    else if(ProgramPara.PM25.Num >= 250){
        OLED_Showch24X24_Pic(104,5,5);//重
        LEDR_ON();
        LEDG_OFF();
    }

 	OLED_ShowN24X24_Pic(104,0,0);//pm2.5
	//OLED_ShowH24x24_Pic(104,5,2);//ug/m3
  }
  
}


//更新温度


void Pm10_Detect(void){
	uint8_t number[3] = {0};
	
	if(ProgramPara.Refresh_flag == TRUE ){
		ProgramPara.Refresh_flag = FALSE;

		if(ProgramPara.PM10.Num >= 999) ProgramPara.PM10.Num = 999;
		if(ProgramPara.PM10.Num < 100){
                  number[0] = ProgramPara.PM10.Num % 10;//个位
                  number[1] = ProgramPara.PM10.Num / 10;//十位

                  
                  OLED_Show32X56_Pic(0 , 1 , number[1],FALSE);//百位不显示
                  OLED_Show32X56_Pic(32 , 1 , number[1],TRUE);//十位
                  OLED_Show32X56_Pic(64 , 1 , number[0],TRUE);//个位
                            
                  }
                  else{
                    number[0] = ProgramPara.PM10.Num % 10;//个位
                    number[1] = ProgramPara.PM10.Num % 100 / 10;//十位
                    number[2] = ProgramPara.PM10.Num / 100;//百位

                    
                    OLED_Show32X56_Pic(0 , 1 , number[2],TRUE);//百位
                    OLED_Show32X56_Pic(32 , 1 , number[1],TRUE);//十位
                    OLED_Show32X56_Pic(64 , 1 , number[0],TRUE);//个位
                    
                  }

                   
                   if(ProgramPara.PM10.Num < 50){
                           OLED_Showch24X24_Pic(104,5,0);//优
                                LEDR_OFF();
                                LEDG_ON();
                   }
                   else if((ProgramPara.PM10.Num < 150) && ((ProgramPara.PM25.Num >= 50))){
                           OLED_Showch24X24_Pic(104,5,1);//良
                                LEDR_OFF();
                                LEDG_ON();
                   }
                   else if((ProgramPara.PM10.Num < 250) && ((ProgramPara.PM25.Num >= 150))){
                           OLED_Showch24X24_Pic(104,5,2);//轻
                                LEDR_OFF();
                                LEDG_ON();
                   }
                   else if((ProgramPara.PM10.Num < 350) && ((ProgramPara.PM25.Num >= 250))){
                           OLED_Showch24X24_Pic(104,5,3);//中
                                LEDR_ON();
                                LEDG_OFF();
                   }
                   else if((ProgramPara.PM10.Num < 420) && ((ProgramPara.PM25.Num >= 350))){
                           OLED_Showch24X24_Pic(104,5,4);//差
                           LEDR_ON();
                           LEDG_OFF();
                   }
                   else if(ProgramPara.PM10.Num >= 420){
                           OLED_Showch24X24_Pic(104,5,5);//重
                           LEDR_ON();
                           LEDG_OFF();
                   }

		
       OLED_ShowN24X24_Pic(104,0,1);//pm10
       //OLED_ShowH24x24_Pic(104,5,2);//ug/m3
	}

}


static volatile unsigned char pos2 = 0;   	
unsigned char pos1 = 0;
static bool Board_flag = FALSE;

void Board_Init(void)
{
  		    
  unsigned char t = 0;
  if(Board_flag == FALSE){
      Board_flag = TRUE;
      OLED_Clear();
      OLED_Showlogo();
      Batt_Test();
  }


  if(((Cnt_Init % 100) == 0))//1s
  {
  	pos1++;
	GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
	if(pos1 == 2){
		
		if(ProgramPara.Flag_wakeup == TRUE){
			ProgramPara.Flag_wakeup = FALSE;
			USART_Cmd(USART1,ENABLE);
		}
		
	}
  	OLED_Set_Pos(pos2,7);
	pos2 = pos2 + 6;
  	for(t = 0;t < 6;t++)
  	{
  		OLED_WR_Byte(0x0F,OLED_DATA);
  	}
  }
  if(Cnt_Init >= 2300) {//23s
  	pos2 = 0;
	pos1 = 0;
	Board_flag = FALSE;
  	Cnt_Init = 0;
	OLED_Clear();
	ProgramPara.Cnt_Minite = 0;
	ProgramPara.Refresh_flag = TRUE;//刷新屏幕
	ProgramPara.Battfresh_flag = TRUE;//刷新屏幕
	ProgramPara.Batt_Minite = 0;
	Mode = Mode_Pm2;
  }

}
uint8_t Batt_level(void)
{
	uint8_t lv = 0;
	ProgramPara.Voltage = Ad_sensor_detect(ADC_Channel_0);
	if(ProgramPara.Voltage < 170)	lv = 1;
	else if((ProgramPara.Voltage > 165) && (ProgramPara.Voltage <= 173)) lv = 2;//3.46V以下
	else if((ProgramPara.Voltage > 173) && (ProgramPara.Voltage <= 180)) lv = 5;//3.4~3.6V
	else if((ProgramPara.Voltage > 180) && (ProgramPara.Voltage <= 185)) lv = 7;//3.6~3.8V
	else if((ProgramPara.Voltage > 185) && (ProgramPara.Voltage <= 190)) lv = 9;//3.7~3.8V
	else if((ProgramPara.Voltage > 190) && (ProgramPara.Voltage <= 200)) lv = 11;//3.9~4v
	else if((ProgramPara.Voltage > 200) && (ProgramPara.Voltage <= 210)) lv = 13;//4v~4.1V
	else if(ProgramPara.Voltage > 210) lv = 13;//4.2v以上

	return lv;
}

/*电池电量检测
3.4V 1格

*/
void Batt_Test(void)
{
	static uint16_t i = 0;
	//uint8_t z = 0;
	static bool flag = FALSE;
	uint8_t lv = 0;
	
#if 1 //无电池时候要关闭这里

	lv = Batt_level();

	if(lv == 1 && Mode != Mode_Charge)
	{
                GPIO_WriteLow(GPIOD,GPIO_Pin_2);
                GPIO_WriteLow(C5VCE_PORT,C5VCE_PIN);
		OLED_Clear();
		disp_lowbatter();
		pos2 = 0;
		pos1 = 0;
		Board_flag = FALSE;

		delay_ms(800);
		OLED_Clear();
		delay_ms(800);
		disp_lowbatter();
		delay_ms(800);
		OLED_Clear();
		delay_ms(800);
		disp_lowbatter();
		delay_ms(800);
		OLED_Clear();


		if((GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0) ){
		      Mode = Mode_Charge;
                      Chargehaltfun();
		}
		else if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) == 0){//普通状态
			Mode_haltfun();//低功耗模式 用电流表测电流时要屏蔽这里
		}

          
		
	}
        if(lv > 1 && Mode != Mode_Charge){
          GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
          GPIO_WriteHigh(GPIOD,GPIO_Pin_2);
        }
#endif
        
	if(ProgramPara.Flag_wakeup == TRUE && Mode != Mode_Charge ){
			//开启8266
		GPIO_WriteHigh(C5VCE_PORT,C5VCE_PIN);
		GPIO_WriteHigh(GPIOD,GPIO_Pin_2);
		delay_ms(1);
	}
	if((GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0) 
		&& (Mode != Mode_Init)){//充电状态
		
		if(++i > 100){
			i = 0;
			if(flag == FALSE){
				if(Mode == Mode_Time){
					OLED_Charge(0,0,lv,flag);
				}
				else{
					OLED_Charge(24,0,lv,flag);
				}
				LEDB_ON();
				flag = TRUE;
			}
			else{
				if(Mode == Mode_Time){
					OLED_Charge(0,0,lv,flag);
				}
				else{
					OLED_Charge(24,0,lv,flag);
				}
				LEDB_OFF();
				flag = FALSE;
			}
			
		}
	}
	else if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) == 0){//普通状态
		if((Mode != Mode_Init) && (ProgramPara.Battfresh_flag == TRUE))
		{
			if(Mode != Mode_Charge){
				ProgramPara.Battfresh_flag =FALSE;
				if(Mode == Mode_Time){
					OLED_Charge(0,0,lv,TRUE);
				}
				else{
					OLED_Charge(24,0,lv,TRUE);
				}
				delay_ms2(2);
				LEDB_OFF();
			}
			else if(ProgramPara.Flag_wakeup == TRUE){
				ProgramPara.Battfresh_flag =FALSE;
				LEDB_OFF();
			}

		}
		else if(Mode == Mode_Charge){
			Mode_haltfun();
		}
		
	}
	

	

}

void PWR_UltraLowPowerCmd(FunctionalState NewState)
{
  /* Check the parameters */

  if (NewState != DISABLE)
  {
    /* Enable the PWR ULP */
    PWR->CSR2 |= PWR_CSR2_ULP;
  }
  else
  {
    /* Disable the PWR ULP */
    PWR->CSR2 &= (uint8_t)(~PWR_CSR2_ULP);
  }
}

void Mode_haltfun(void){
	
	//PWR_UltraLowPowerCmd(ENABLE);
	//关闭PM2.5和502传感器
	GPIO_WriteLow(C5VCE_PORT,C5VCE_PIN);
	GPIO_WriteLow(GPIOD,GPIO_Pin_2);
	USART_Cmd(USART1,DISABLE);
	//ADC_Cmd(ADC1 , DISABLE);			   //失能ADC  
	//关闭外设时钟
	//CLK_PeripheralClockConfig(CLK_Peripheral_USART1,DISABLE);
	//CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,DISABLE);
	//CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,DISABLE);
	//每次待机都需要设置为输入模式 不然电流很大
	//GPIO_Init(GPIOD,GPIO_Pin_2,GPIO_Mode_In_FL_No_IT);

	
	//关闭OLED屏幕 包括DCDC
	OLED_Display_Off();
	LEDB_OFF();
	LEDG_OFF();
	LEDR_OFF();
	//Mode = Mode_Init;
	ProgramPara.Network_flag = 0;
	halt();
	if(ProgramPara.Flag_wakeup == TRUE){
          HaltWakeUp();
	}




}
//charge模式关屏幕
void Chargehaltfun(void){
		
      //关闭PM2.5和502传感器
      GPIO_WriteLow(GPIOD,GPIO_Pin_2);
      GPIO_WriteLow(C5VCE_PORT,C5VCE_PIN);
      USART_Cmd(USART1,DISABLE);  
      //CLK_PeripheralClockConfig(CLK_Peripheral_USART1,DISABLE);

      //delay_ms(10);
      //每次待机都需要设置为输入模式 不然电流很大
     // GPIO_Init(GPIOD,GPIO_Pin_2,GPIO_Mode_In_FL_No_IT);
      //delay_ms(10);
      //关闭OLED屏幕 包括DCDC
      //OLED_Clear();
      OLED_Display_Off();
      LEDG_OFF();
      LEDR_OFF();
	  //ProgramPara.Flag_wakeup = FALSE;
      ProgramPara.Network_flag = 0;
      ProgramPara.Batt_Minite = 0;
      ProgramPara.Battfresh_flag = FALSE;

	
	
}




//halt模式被唤醒
void HaltWakeUp(void)
{
	PWR_UltraLowPowerCmd(DISABLE);

	//delay_ms(2);
	//ADC_Cmd(ADC1 , ENABLE);			   //使能ADC  
	//开启外设时钟
	CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
	
	CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,ENABLE);
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);
	//Sensor_ADC_detect_Init(ADC_Channel_0);
	//ADC_Cmd(ADC1 , ENABLE);
	Sensor_ADC_Init();//ADC初始化

        Sensor_ADC_detect_Init(ADC_Channel_0);//电池检测
	
	Mode = Mode_Init;
	//开启OLED屏幕 包括DCDC
	OLED_Display_On();
	Batt_Test();
	RTC_GetDate(RTC_Format_BIN , &GETRTC_Data);
        RTC_GetTime(RTC_Format_BIN , &GETRTC_Time); 
	//ProgramPara.PM_Alarm = FALSE;
	//ProgramPara.Voc_Alarm = FALSE;

}



