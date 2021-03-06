#include "main.h"

#define BEEP_PORT
#define BEEP_PIN





//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(STMSTM8S103K3系列)
//              说明: 


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

/****************时钟*********************/
#define OLED_SCLK_PORT  (GPIOB)
#define OLED_SCLK_PINS  (GPIO_Pin_2)

/****************数据*********************/
#define OLED_SDIN_PORT  (GPIOB)
#define OLED_SDIN_PINS  (GPIO_Pin_3)

/****************复位*********************/
#define OLED_RST_PORT  (GPIOB)
#define OLED_RST_PINS  (GPIO_Pin_1)

/****************数据/命令*********************/
#define OLED_DC_PORT  (GPIOD)
#define OLED_DC_PINS  (GPIO_Pin_0)

/****************片选*********************/
#define OLED_CS_PORT  (GPIOB)
#define OLED_CS_PINS  (GPIO_Pin_0)


#define OLED_SCLK_Clr() GPIO_WriteLow(OLED_SCLK_PORT, OLED_SCLK_PINS)
#define OLED_SCLK_Set() GPIO_WriteHigh(OLED_SCLK_PORT, OLED_SCLK_PINS)

#define OLED_SDIN_Clr() GPIO_WriteLow(OLED_SDIN_PORT, OLED_SDIN_PINS)
#define OLED_SDIN_Set() GPIO_WriteHigh(OLED_SDIN_PORT, OLED_SDIN_PINS)

#define OLED_RST_Clr() GPIO_WriteLow(OLED_RST_PORT, OLED_RST_PINS)
#define OLED_RST_Set() GPIO_WriteHigh(OLED_RST_PORT, OLED_RST_PINS)


#define OLED_DC_Clr() GPIO_WriteLow(OLED_DC_PORT, OLED_DC_PINS)
#define OLED_DC_Set() GPIO_WriteHigh(OLED_DC_PORT, OLED_DC_PINS)


#define OLED_CS_Clr()  GPIO_WriteLow(OLED_CS_PORT, OLED_CS_PINS)
#define OLED_CS_Set()  GPIO_WriteHigh(OLED_CS_PORT, OLED_CS_PINS)


#define LEDB_PORT		(GPIOB)
#define LEDB_PIN		(GPIO_Pin_6)

#define LEDR_PORT		(GPIOB)
#define LEDR_PIN		(GPIO_Pin_4)

#define LEDG_PORT		(GPIOB)
#define LEDG_PIN		(GPIO_Pin_5)


#define LEDG_OFF()		GPIO_WriteHigh(LEDG_PORT, LEDG_PIN)
#define LEDG_ON()		GPIO_WriteLow(LEDG_PORT, LEDG_PIN)

#define LEDR_OFF()		GPIO_WriteHigh(LEDR_PORT, LEDR_PIN)
#define LEDR_ON()		GPIO_WriteLow(LEDR_PORT, LEDR_PIN)

#define LEDB_OFF()		GPIO_WriteHigh(LEDB_PORT, LEDB_PIN)
#define LEDB_ON()		GPIO_WriteLow(LEDB_PORT, LEDB_PIN)



//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   

void delay_ms(unsigned int ms);
void delay_ms2(unsigned int ms);	     
//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_Showbatt(unsigned char x, unsigned char y,unsigned char battrey);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_Charge(unsigned char x , unsigned char y,unsigned char battrey,bool flag);

void OLED_ShowH24x24_Pic(unsigned char x , unsigned char y , unsigned char no);
void OLED_Showminu(bool flag);
void OLED_net(unsigned char x , unsigned char y,bool flag);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowN24X24_Pic(unsigned char x , unsigned char y , unsigned char no);
void OLED_Show32X56_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag);
void OLED_Show24X48_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag);
void OLED_Show8x16_char(unsigned char x , unsigned char y , unsigned char no,bool flag);
void OLED_Show16X16_Week(unsigned char x , unsigned char y , unsigned char no,bool flag);
void OLED_Show30X56_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag);
void OLED_ShowNum16X32(unsigned char x , unsigned char y , unsigned char no);
void OLED_Showch24X24_Pic(unsigned char x , unsigned char y , unsigned char no);
void OLED_Show38X64_Pic(unsigned char x , unsigned char y , unsigned char no,bool flag);

void LED_Init(void);
void OLED_Showlogo(void);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1);

void disp_lowbatter(void);


