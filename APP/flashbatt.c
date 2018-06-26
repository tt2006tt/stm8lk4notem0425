#include "flashbatt.h"


/*

void EEPROM_INIT(void)
{
    FLASH_DeInit();

  
//Unlock program memory 
    FLASH->PUKR = FLASH_RASS_KEY1;
    FLASH->PUKR = FLASH_RASS_KEY2;
    
// Unlock data memory 
    FLASH->DUKR = FLASH_RASS_KEY2; // Warning: keys are reversed on data memory !!! 
    FLASH->DUKR = FLASH_RASS_KEY1;
    
    FLASH_SetProgrammingTime(FLASH_ProgramTime_TProg);
}

void writeSomeByte(uint32_t Address, uint8_t *Data,uint8_t length)
{
  uint8_t i;
  for(i=0;i<length;i++)
  {
    FLASH_ProgramByte( Address , *Data++ );   
    Address = Address + 1;
  }
  
  while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == 1);     //等待编程结束
}


void readSomeByte(uint32_t Address, uint8_t Data[],uint8_t length)
{
  uint8_t i;
  //uint8_t ReadWord;
  for(i=0;i<length;i++)
  {
    Data[i] = FLASH_ReadByte( Address);
    Address = Address + 1;
  }
}
*/


/*******************************************************************************
**函数名称：void KEY_Input_Init()     Name: KEY_Input_Init()
**功能描述：初始化按钮引脚IO参数 用于唤醒机器
**入口参数：无
**输出：无
*******************************************************************************/
void KEY_Input_Init(void)
{

  GPIO_Init(WAKEKEY_PORT , WAKEKEY_PIN , GPIO_Mode_In_PU_IT);         //初始化KEY，设置PD_7为上拉电阻输入并且使能中断模式
  EXTI_SetPinSensitivity(EXTI_Pin_7 , EXTI_Trigger_Falling);  //Portx端口bit2 外部中断线2为下降沿触发中断

  //GPIO_Init(WAKEKEY_PORT , GPIO_Pin_6 , GPIO_Mode_In_PU_No_IT);         //初始化KEY，设置PD_6为上拉电阻输入并且使能中断模式
  //EXTI_SetPinSensitivity(EXTI_Pin_6 , EXTI_Trigger_Falling);  //Portx端口bit2 外部中断线2为下降沿触发中断

}

void mykey_Press(void){//
  static uint16_t Cnt_Kye = 0;
  static uint16_t Cnt_KeyUP = 0;
  static uint8_t flag_keyup = 0;

  if ((((uint8_t)WAKEKEY_PORT->IDR) & WAKEKEY_PIN) == 0x00){// 按键按下(GPIO_ReadInputData(KEY_PORT)
    Cnt_Kye++;
    if( Cnt_Kye > 150){//长按 1.5s

	if(Mode != Mode_Init)
	{
              
      if(Mode != Mode_Charge){
        if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0){
        Mode = Mode_Charge;

        Chargehaltfun();

        }
        else{ 	
              Mode_haltfun();//低功耗模式
        }
      }
    }
	else{
		if(ProgramPara.Key_Type == 4){
		}
		else{
          ProgramPara.Network_flag = 2;//进入配网flag_revise
          ProgramPara.Key_Type = 0;
          SetBit(ProgramPara.Key_Type,1);
		}
	}
	Cnt_Kye = 0;

    }
  }else{
    if(Cnt_Kye > 4 && Cnt_Kye < 50){//按下时间大于40ms小于500ms
        flag_keyup ++;
    } 

    if(flag_keyup){//如果发生单击
        Cnt_KeyUP++;
    }
    if(flag_keyup != 0){//如果只按一次//if(flag_keyup == 1 && Cnt_KeyUP > 50){//如果只按一次
    	if((Mode != Mode_Charge) && (Mode != Mode_Init)){
            ProgramPara.Key_Type = 0;
            ProgramPara.Cnt_Minite = 0;
            ProgramPara.Refresh_flag = TRUE;//按键按下刷新屏幕
            ProgramPara.Battfresh_flag = TRUE;//电池图标刷新
            OLED_Init();
            if (++Mode > Mode_Time) Mode= Mode_Pm2;
            LEDB_OFF();
            LEDR_OFF();
            LEDG_OFF();

            

    	}
        Cnt_KeyUP = 0;
        flag_keyup = 0;


    }
    if(flag_keyup != 1 && Cnt_KeyUP > 50){
        flag_keyup = 0;
        Cnt_KeyUP = 0;
    }
	
    Cnt_Kye = 0;
  }
  
}



void UartWorking(void)
{
	uint8_t len = 0;
	//uint8_t y = 0;//
	uint8_t DatePackege[64] = {0};
	DatePackege[len] = 0x55;len++;//起始标志
	DatePackege[len] = 0x61;len++;//源地址LOCAL_ADDR;
	switch(Receive)
	{
		case 0x01:


			DatePackege[len] = 0x65;len++;//目标地址
			DatePackege[len] = 0x0D;len++;//len
			DatePackege[len] = UartAirPoll_Ack;len++;//ack_command
			
			//voc
			DatePackege[len] |= ((ProgramPara.PPM.Num>> 24) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.PPM.Num >> 16) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.PPM.Num >> 8) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.PPM.Num >> 0) & 0xFF);len++;
			//tem
			DatePackege[len] |= ((ProgramPara.tem>> 24) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.tem >> 16) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.tem >> 8) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.tem >> 0) & 0xFF);len++;
			//hum
			DatePackege[len] |= ((ProgramPara.hum.Num>> 24) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.hum.Num >> 16) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.hum.Num >> 8) & 0xFF);len++;
			DatePackege[len] |= ((ProgramPara.hum.Num >> 0) & 0xFF);len++;
			DatePackege[len] |= ProgramPara.Key_Type;len++;//key_type 未定 0 短按 1长按 2 连按3下  3:报警

			DatePackege[len] = UartStop;len++;//stop 需要多+一个
			uartSendDataBuf(DatePackege,len);
			len = 0;
		break;
		
		case 0x02:

                  ProgramPara.Cnt_Minite = 0;
		break;
		
		case 0x03:
                  ProgramPara.Cnt_Minite = 0;
		break;
		
		case 0x04:
			if(DataFormat.mems[0] == 0x02){//smconfig 失败
				ProgramPara.Network_flag = 2;
			}
			else if(DataFormat.mems[0] == 0x01){//smconfig 成功
				ProgramPara.Network_flag = 1;
			}
			else if(DataFormat.mems[0] == 0x03){//smconfig 配网中
				ProgramPara.Network_flag = 3;
			}

		break;
		
		case 0x05:
    
		break;	
		/*
		case 0x06:
			DatePackege[len] = 0x65;len++;//目标地址
			DatePackege[len] = 0x0B;len++;//len
			DatePackege[len] = UartGetId_ACK;len++;//ack_command
			for(y = 0;y<10;y++){
                  DatePackege[len++] = ProgramPara.Dev_ID[y];
             }//装载数据
			//DatePackege[len] = Get_XOR(DatePackege,11);len++;//XOR校验
			DatePackege[len] = UartStop;len++;//stop 需要多+一个
			uartSendDataBuf(DatePackege,len);
			len = 0;
		break;
		
		case 0x07:
			for(y = 0;y<10;y++){
				ProgramPara.Dev_ID[y] = DataFormat.mems[y];
				FLASH_ProgramByte(DEVID_BaseAddress + y,ProgramPara.Dev_ID[y]);
			}
			DatePackege[len] = UartStop;len++;//stop 需要多+一个
                        len = 0;
		break;
		*/
		case 0x08:
		break;
		
		case 0x09:
			//memcpy(ProgramPara.Alarm.Arr,DataFormat.mems,4);
		break;
		case 0x0A:
			//月 日时 分秒 周
			RTC_Set(DataFormat.mems[0],DataFormat.mems[1],DataFormat.mems[2],
					DataFormat.mems[3],DataFormat.mems[4],DataFormat.mems[5]);
		break;
			
		default:
		break;
		
	}
	Receive = 0;
}



