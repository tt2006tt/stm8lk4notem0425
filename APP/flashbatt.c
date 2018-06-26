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
  
  while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == 1);     //�ȴ���̽���
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
**�������ƣ�void KEY_Input_Init()     Name: KEY_Input_Init()
**������������ʼ����ť����IO���� ���ڻ��ѻ���
**��ڲ�������
**�������
*******************************************************************************/
void KEY_Input_Init(void)
{

  GPIO_Init(WAKEKEY_PORT , WAKEKEY_PIN , GPIO_Mode_In_PU_IT);         //��ʼ��KEY������PD_7Ϊ�����������벢��ʹ���ж�ģʽ
  EXTI_SetPinSensitivity(EXTI_Pin_7 , EXTI_Trigger_Falling);  //Portx�˿�bit2 �ⲿ�ж���2Ϊ�½��ش����ж�

  //GPIO_Init(WAKEKEY_PORT , GPIO_Pin_6 , GPIO_Mode_In_PU_No_IT);         //��ʼ��KEY������PD_6Ϊ�����������벢��ʹ���ж�ģʽ
  //EXTI_SetPinSensitivity(EXTI_Pin_6 , EXTI_Trigger_Falling);  //Portx�˿�bit2 �ⲿ�ж���2Ϊ�½��ش����ж�

}

void mykey_Press(void){//
  static uint16_t Cnt_Kye = 0;
  static uint16_t Cnt_KeyUP = 0;
  static uint8_t flag_keyup = 0;

  if ((((uint8_t)WAKEKEY_PORT->IDR) & WAKEKEY_PIN) == 0x00){// ��������(GPIO_ReadInputData(KEY_PORT)
    Cnt_Kye++;
    if( Cnt_Kye > 150){//���� 1.5s

	if(Mode != Mode_Init)
	{
              
      if(Mode != Mode_Charge){
        if(GPIO_ReadInputDataBit(CHARGESTATUS_PORT,CHARGESTATUS_PIN) != 0){
        Mode = Mode_Charge;

        Chargehaltfun();

        }
        else{ 	
              Mode_haltfun();//�͹���ģʽ
        }
      }
    }
	else{
		if(ProgramPara.Key_Type == 4){
		}
		else{
          ProgramPara.Network_flag = 2;//��������flag_revise
          ProgramPara.Key_Type = 0;
          SetBit(ProgramPara.Key_Type,1);
		}
	}
	Cnt_Kye = 0;

    }
  }else{
    if(Cnt_Kye > 4 && Cnt_Kye < 50){//����ʱ�����40msС��500ms
        flag_keyup ++;
    } 

    if(flag_keyup){//�����������
        Cnt_KeyUP++;
    }
    if(flag_keyup != 0){//���ֻ��һ��//if(flag_keyup == 1 && Cnt_KeyUP > 50){//���ֻ��һ��
    	if((Mode != Mode_Charge) && (Mode != Mode_Init)){
            ProgramPara.Key_Type = 0;
            ProgramPara.Cnt_Minite = 0;
            ProgramPara.Refresh_flag = TRUE;//��������ˢ����Ļ
            ProgramPara.Battfresh_flag = TRUE;//���ͼ��ˢ��
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
	DatePackege[len] = 0x55;len++;//��ʼ��־
	DatePackege[len] = 0x61;len++;//Դ��ַLOCAL_ADDR;
	switch(Receive)
	{
		case 0x01:


			DatePackege[len] = 0x65;len++;//Ŀ���ַ
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
			DatePackege[len] |= ProgramPara.Key_Type;len++;//key_type δ�� 0 �̰� 1���� 2 ����3��  3:����

			DatePackege[len] = UartStop;len++;//stop ��Ҫ��+һ��
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
			if(DataFormat.mems[0] == 0x02){//smconfig ʧ��
				ProgramPara.Network_flag = 2;
			}
			else if(DataFormat.mems[0] == 0x01){//smconfig �ɹ�
				ProgramPara.Network_flag = 1;
			}
			else if(DataFormat.mems[0] == 0x03){//smconfig ������
				ProgramPara.Network_flag = 3;
			}

		break;
		
		case 0x05:
    
		break;	
		/*
		case 0x06:
			DatePackege[len] = 0x65;len++;//Ŀ���ַ
			DatePackege[len] = 0x0B;len++;//len
			DatePackege[len] = UartGetId_ACK;len++;//ack_command
			for(y = 0;y<10;y++){
                  DatePackege[len++] = ProgramPara.Dev_ID[y];
             }//װ������
			//DatePackege[len] = Get_XOR(DatePackege,11);len++;//XORУ��
			DatePackege[len] = UartStop;len++;//stop ��Ҫ��+һ��
			uartSendDataBuf(DatePackege,len);
			len = 0;
		break;
		
		case 0x07:
			for(y = 0;y<10;y++){
				ProgramPara.Dev_ID[y] = DataFormat.mems[y];
				FLASH_ProgramByte(DEVID_BaseAddress + y,ProgramPara.Dev_ID[y]);
			}
			DatePackege[len] = UartStop;len++;//stop ��Ҫ��+һ��
                        len = 0;
		break;
		*/
		case 0x08:
		break;
		
		case 0x09:
			//memcpy(ProgramPara.Alarm.Arr,DataFormat.mems,4);
		break;
		case 0x0A:
			//�� ��ʱ ���� ��
			RTC_Set(DataFormat.mems[0],DataFormat.mems[1],DataFormat.mems[2],
					DataFormat.mems[3],DataFormat.mems[4],DataFormat.mems[5]);
		break;
			
		default:
		break;
		
	}
	Receive = 0;
}



