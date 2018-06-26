#include "main.h"


#define    DELAYTIME  100



#if RTC_ONOFF
void RTC_CLOCK_Init()
{ 
    CLK_LSICmd(ENABLE);                     //��оƬ�ڲ��ĵ�������LSI
    while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);// �ȴ������ȶ�
   
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI , //ѡ���ڲ����ٵ�Ƶ38KHZʱ��Դ��ΪRTCʱ��Դ
                       CLK_RTCCLKDiv_1        //����Ϊ1��Ƶ
                       );
	
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC , ENABLE);    //ʹ��ʵʱʱ��RTCʱ��

}

void RTC_Set(unsigned char month,unsigned char day ,unsigned char hour , unsigned char min , unsigned char second,unsigned char week)
{ 
  RTC_InitTypeDef  RTCInit;
  RTC_TimeTypeDef RTCTime;
  RTC_DateTypeDef RTCData;
  
  RTC_WriteProtectionCmd(DISABLE);  //���RTC���ݱ���
  
  RTC_EnterInitMode();    //����RTC�����ʼ��ģʽ�������RTCʱ������ڼĴ�����������
  while(RTC_GetFlagStatus(RTC_FLAG_INITF) == RESET);  //�ȴ��������� �ȴ�INITF == 1�����������

  RTCInit.RTC_HourFormat = RTC_HourFormat_24;
  RTCInit.RTC_AsynchPrediv = 37;
  RTCInit.RTC_SynchPrediv = 999;
  RTC_Init(&RTCInit);

  RTC_RatioCmd(ENABLE);

  RTCTime.RTC_Hours = hour;
  RTCTime.RTC_Minutes = min;
  RTCTime.RTC_Seconds = second;
  RTCTime.RTC_H12 = RTC_H12_AM;     //24
  RTC_SetTime(RTC_Format_BIN , &RTCTime);
  
  RTCData.RTC_WeekDay = (RTC_Weekday_TypeDef)week;   //RTC_Weekday_Sunday;    //sunday
  RTCData.RTC_Month = (RTC_Month_TypeDef)month;    //RTC_Month_August;      //8month
  RTCData.RTC_Date = day;      //14days
  //RTCData.RTC_Year = year;
  RTC_SetDate(RTC_Format_BIN , &RTCData);
   
  RTC_ExitInitMode(); //����������
  
  RTC_WriteProtectionCmd(ENABLE);//����Կ�Ĵ��������д����
}


void Get_TheTime(void)
{
	uint8_t number[4] = {0};

  //unsigned char sec_st,sec_su , min_mt,min_mu ,hour_ht , hour_hu , midd ,status;
  if(RTC_GetFlagStatus(RTC_FLAG_RSF) == SET)  //��ʱ����� 
  {
    
    
    RTC_GetDate(RTC_Format_BIN , &GETRTC_Data);
    RTC_GetTime(RTC_Format_BIN , &GETRTC_Time);  
      
     RTC_ClearFlag(RTC_FLAG_RSF);   //�����־    
  }


	 
  if(ProgramPara.Refresh_flag == TRUE){
  	 
     ProgramPara.Refresh_flag = FALSE;

		
      number[0] = GETRTC_Time.RTC_Hours % 10;//��λ
      number[1] = GETRTC_Time.RTC_Hours / 10;//ʮλ
      number[2] = GETRTC_Time.RTC_Minutes % 10;//��λ
      number[3] = GETRTC_Time.RTC_Minutes / 10;//ʮλ
      OLED_Show24X48_Pic(0 , 2 , number[1],TRUE);//ʮλ
      OLED_Show24X48_Pic(24 , 2 , number[0],TRUE);//��λ
      OLED_Show24X48_Pic(48 , 2 , 10,TRUE);//ð��
      OLED_Show24X48_Pic(72 , 2 , number[3],TRUE);//ʮλ
      OLED_Show24X48_Pic(96 , 2 , number[2],TRUE);//��λ

	  if(GETRTC_Data.RTC_Month > 9){
		number[0] = GETRTC_Data.RTC_Month %10;//��λ
                number[1] = GETRTC_Data.RTC_Month / 10;//ʮλ
                OLED_Show8x16_char(24,0,number[1],TRUE);
	  	OLED_Show8x16_char(32,0,number[0],TRUE);
	  }
	  else{
	  	OLED_Show8x16_char(24,0,number[1],FALSE);
	  	OLED_Show8x16_char(32,0,GETRTC_Data.RTC_Month ,TRUE);
	  	
	  }
	  if(GETRTC_Data.RTC_Date> 9){
	  	number[0] = GETRTC_Data.RTC_Date %10;//��λ
                number[1] = GETRTC_Data.RTC_Date / 10;//ʮλ
		OLED_Show8x16_char(56,0,number[1],TRUE);//True
		OLED_Show8x16_char(64,0,number[0],TRUE);//True

	  }
	  else{
	  	OLED_Show8x16_char(56,0,number[1],FALSE);
		OLED_Show8x16_char(64,0,GETRTC_Data.RTC_Date ,TRUE);//True
	  }
	  OLED_Show16X16_Week(40,0,8,TRUE);//��

	  OLED_Show16X16_Week(72,0,9,TRUE);//��
	  
	  OLED_Show16X16_Week(96,0,7,TRUE);//����
	  OLED_Show16X16_Week(112,0,(GETRTC_Data.RTC_WeekDay -1),TRUE);
  }
	
}
#endif

