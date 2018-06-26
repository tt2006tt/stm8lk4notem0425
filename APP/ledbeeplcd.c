#include "ledbeeplcd.h"

//#include "stdlib.h"
#include "oledfont.h"  	 
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 
#pragma optimize=none
void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=600;
		while(a--);
		ms--;
	}
	return;
}

#pragma optimize=none
void delay_ms2(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1;
		while(a--);
		ms--;
	}
	return;
}


//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
#pragma optimize=none

void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	{
	  OLED_DC_Set();nop();
	}
	else
	{
	  OLED_DC_Clr();nop();
	}
	//delay_ms2(1);
	OLED_CS_Clr();
	nop();
	//delay_ms2(1);
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		nop();
		//delay_ms2(1);
		if(dat&0x80)
		{
		   OLED_SDIN_Set();
			nop();
		}
		else
		{
		   OLED_SDIN_Clr();
		   nop();
		}
	
		//delay_ms2(1);
		OLED_SCLK_Set();
		nop();
		//delay_ms2(1);
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	nop();
	//delay_ms2(1);
	OLED_DC_Set(); 
	nop();
} 

	
#pragma optimize=none

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//开启OLED显示   
void OLED_Display_On(void)
{
	//OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC?üá?
	//OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAD,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0X8B,OLED_CMD);  //sleep mode wakeup
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
	
}
//关闭OLED显示    sleep mode 
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
	//OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC?üá?
	//OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAD,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0X8B,OLED_CMD);  //sleep mode
	
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	 
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x02,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址      
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

		  
		  
void OLED_Show38X64_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag)
{ 				  
	unsigned char t,adder = 0,z;
	for(z = 0;z < 8; z++)
	{
		OLED_Set_Pos(x,y + z);  
		for(t = 0 ;t < 38; t++)
		{   
			if(flag){

				OLED_WR_Byte( Num38x64[8 * no + z][t],OLED_DATA);
			}
			else{
			OLED_WR_Byte( 0x00,OLED_DATA);
			}
			adder += 1;
		} 
	}
}



/*一行32个像素 字符是一行16个像素flag 代表是否显示*/
void OLED_Show32X56_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag)
{					
  unsigned char t,adder = 0,z;
  for(z = 0;z < 7; z++)
  {
  	OLED_Set_Pos(x,y + z);	
  	for(t = 0 ;t < 32; t++)
  	{	
  		if(flag){
			
			OLED_WR_Byte( Num32x56[7 * no + z][t],OLED_DATA);
  		}
		else{
			OLED_WR_Byte( 0x00,OLED_DATA);
		}
		adder += 1;
  	} 
  }
}

void OLED_Show24X48_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag)
{					
  unsigned char t,adder = 0,z;
  for(z = 0;z < 6; z++)
  {
  	OLED_Set_Pos(x,y + z);	
  	for(t = 0 ;t < 24; t++)
  	{	
  		if(flag){
			
			OLED_WR_Byte( Num24X48[6 * no + z][t],OLED_DATA);
  		}
		else{
			OLED_WR_Byte( 0x00,OLED_DATA);
		}
		adder += 1;
  	} 
  }
}


//7 为周字 8 为月 9为日
void OLED_Show16X16_Week(unsigned char x , unsigned char y , unsigned char no,bool flag)
{					
  unsigned char t,adder = 0,z;
  for(z = 0;z < 2; z++)
  {
  	OLED_Set_Pos(x,y + z);	
  	for(t = 0 ;t < 16; t++)
  	{	
  		if(flag){
			
			OLED_WR_Byte( Week16x16[2 * no + z][t],OLED_DATA);
  		}
		else{
			OLED_WR_Byte( 0x00,OLED_DATA);
		}
		adder += 1;
  	} 
  }
}



void OLED_Show8x16_char(unsigned char x , unsigned char y , unsigned char no,bool flag)
{					
  unsigned char i,adder = 0;
	
	if(flag){
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
			OLED_WR_Byte(Num8x16[no*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(Num8x16[no*16+i+8],OLED_DATA);
	
	}
	else{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
			OLED_WR_Byte(0x00,OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(0x00,OLED_DATA);
	}
		adder += 1;
  
  
}



/*显示温  湿 PM2.5  TVOC  4个图片  对应no  0~4 */
void OLED_ShowN24X24_Pic(unsigned char x , unsigned char y , unsigned char no)
{					
  unsigned char t,adder = 0,z;
  for(z = 0;z < 3; z++)
  {
  	OLED_Set_Pos(x,y + z);	
	for(t = 0 ;t < 24; t++)
	{
		OLED_WR_Byte( LP24x24[3 * no + z][t],OLED_DATA);
		adder += 1;
	} 
  }
}

/*显示温  湿 PM2.5  TVOC  4个图片  对应no  0~4 */
void OLED_Showch24X24_Pic(unsigned char x , unsigned char y , unsigned char no)
{					
  unsigned char t,adder = 0,z;
  for(z = 0;z < 3; z++)
  {
  	OLED_Set_Pos(x,y + z);	
	for(t = 0 ;t < 24; t++)
	{
		OLED_WR_Byte( chinese24x24[3 * no + z][t],OLED_DATA);
		adder += 1;
	} 
  }
}






/*显示联网图标*/
void OLED_net(unsigned char x , unsigned char y,bool flag)
{					
  unsigned char t = 0;
  OLED_Set_Pos(x,y);
  if(flag == TRUE){
	  for(t = 0;t < 16;t++)
	  {
		OLED_WR_Byte(net[t],OLED_DATA);
	  }
  }
  else if(flag == FALSE){
  	  for(t = 0;t < 16;t++)
	  {
		OLED_WR_Byte(0x00,OLED_DATA);
	  }
  }
}


/*显示电池符号  battrey: 0~13 代表电量*/
void OLED_Charge(unsigned char x , unsigned char y,unsigned char battrey,bool flag)
{      			    
  unsigned char t = 0;
	if(flag == TRUE){
	  OLED_Set_Pos(x,y);
	  for(t = 0;t < 16;t++)
	  {
	  	OLED_WR_Byte(battart[t],OLED_DATA);
	  }
	  /*重新设置光标位置不然会按照之前的光标往后画，
	  代表有多少电量
	*/
	  OLED_Set_Pos(x,y);
	  if(battrey >= 13){
		battrey = 13;
	  }
	  for(t = 0;t < battrey+1;t++)//有一格是头
	  {
	  	OLED_WR_Byte(0xFF,OLED_DATA);
	  }
	}
  else{
  	  OLED_Set_Pos(x,y);
	  for(t = 0;t < 16;t++)
	  {
	  	OLED_WR_Byte(0x00,OLED_DATA);
	  }
  }
}

#if(LOGO == 1)

void OLED_Showlogo(void)
{      			    
	unsigned char t,z;
     unsigned int adder=0;
	for(z = 0;z < 7; z++)
	{
	  OLED_Set_Pos(25,z);	
	  for(t = 0 ;t < 77; t++)
	  {
		OLED_WR_Byte( Logo56[adder],OLED_DATA);
		adder ++;
	  } 
	}

}
#elif(LOGO == 0)


void OLED_Showlogo(void)
{      			    
	unsigned char t;
     unsigned int adder=0;

	  OLED_Set_Pos(22,3);	
	  for(t = 0 ;t < 83; t++)
	  {
		OLED_WR_Byte( Logo56[adder],OLED_DATA);
		adder ++;
	  } 
	

}
#elif(LOGO == 2)
void OLED_Showlogo(void)
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
	for(y=3;y<6;y++)
	{
		OLED_Set_Pos(6,y);
    	for(x=0;x<120;x++)
	    {      
	    	OLED_WR_Byte(Logo56[j++],OLED_DATA);	    	
	    }
	}
} 




#endif

void disp_lowbatter(void)
{
	unsigned char t;
  	OLED_Set_Pos(20,1);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
  	OLED_Set_Pos(24,1);
  	for(t = 0;t < 76;t++)
  	{
  		OLED_WR_Byte(0x0f,OLED_DATA);
  	}
  	OLED_Set_Pos(100,1);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}

  	OLED_Set_Pos(20,2);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
  	OLED_Set_Pos(100,2);
  	for(t = 0;t < 8;t++)
  	{
  		OLED_WR_Byte(0x0f,OLED_DATA);
  	}
  	OLED_Set_Pos(108,2);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
	
  	OLED_Set_Pos(20,3);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
  	OLED_Set_Pos(108,3);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}

  	OLED_Set_Pos(20,4);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
  	OLED_Set_Pos(108,4);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}

  	OLED_Set_Pos(20,5);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
  	OLED_Set_Pos(100,5);
  	for(t = 0;t < 8;t++)
  	{
  		OLED_WR_Byte(0xf0,OLED_DATA);
  	}
  	OLED_Set_Pos(108,5);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}

  	OLED_Set_Pos(20,6);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}
  	OLED_Set_Pos(24,6);
  	for(t = 0;t < 76;t++)
  	{
  		OLED_WR_Byte(0xf0,OLED_DATA);
  	}
  	OLED_Set_Pos(100,6);
  	for(t = 0;t < 4;t++)
  	{
  		OLED_WR_Byte(0xff,OLED_DATA);
  	}

}



//初始化SSD1306					    
void OLED_Init(void)
{

   
  	OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
	/*				  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0×óóò·′?? 0xa1?y3￡
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0é???·′?? 0xc8?y3￡
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	*/

	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
        OLED_WR_Byte(0x33,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0×óóò·′?? 0xa1?y3￡
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0é???·′?? 0xc8?y3￡
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 
}


/*******************************************************************************
**函数名称：void LED_Init()     Name: LED_Init()
**功能描述：初始化按钮引脚IO参数 用于唤醒机器
**入口参数：无
**输出：无
*******************************************************************************/
void LED_Init(void)
{
	GPIO_Init(LEDB_PORT , LEDB_PIN, GPIO_Mode_Out_PP_High_Slow); 
	GPIO_Init(LEDR_PORT , LEDR_PIN , GPIO_Mode_Out_PP_High_Slow);
	GPIO_Init(LEDG_PORT , LEDG_PIN , GPIO_Mode_Out_PP_High_Slow);
	

	LEDG_OFF();
	
	LEDB_OFF();
	LEDR_OFF();
}


