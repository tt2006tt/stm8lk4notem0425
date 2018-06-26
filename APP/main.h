#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "stm8l15x.h"
#include "sensoradc.h"
#include "temhum.h"
#include "ledbeeplcd.h"
#include "flashbatt.h"
//-----------------------


#define HSI_CLOCK

#define BIT(x)	(1 << (x))

#define VDD_3_3V

#define	C5VCE_PORT	(GPIOC)
#define	C5VCE_PIN	(GPIO_Pin_4)

#define	CHARGESTATUS_PORT	(GPIOA)
#define	CHARGESTATUS_PIN	(GPIO_Pin_5)


#define BIT_SHORT   	0  //短按


#define WWDG_CNT        0x7E
#define WWDG_WIN        0x7F

#define RXMAX           32

#define Mode_Init    		0x01	//初始化模式
#define Mode_Pm2                0x02	//测量湿度模式
#define Mode_Pm10		0x03//测量PM10模式

//#define Mode_Mp  		0x04		//测量温度模式
//#define Mode_Tem		0x05		//测量PM2.5模式
//#define Mode_Hum		0x06		//VOC测量模式
#define Mode_Time		0x04		//时间显示模式



#define Mode_Charge		0x20		//低功耗模式


#define RTC_ONOFF	1
#define LOGO	2//1为公司logo 0 brother 2天合

/************************************************
 * uart_command
 ************************************************/
#define UartStop		0x56
#define UartPoll		0x81
#define UartPoll_Ack	        0x01
#define UartSmartconfig	        0x82
#define Uartledcolor	        0x83
#define Uartledcolor_Ack	0x02

#define UartStopWarning	        0x84
#define UartGetId		0x85
#define UartGetId_ACK	        0x03
#define UartNewId_Save	        0x86
#define UartNewId_Save_ACK	0x04
#define UartWaring		0x87
#define UartWaring_Ack	        0x05
#define UartFirstLink	        0x88
#define UartFirstLink_Ack	0x06
#define UartSetPpm		0x89
#define UartSetPpm_Ack	        0x07

#define UartAirPoll_Ack         0x08
#define UartAirSetTime	        0x90
#define UartAirPoll		0x91



//#define MP_502	//HC 甲醛502所有ppm都乘以100
#define MP_503	//VOC

typedef enum
{
  /* RMPCR1 register bits */
  REMAP_Pin_USART1TxRxPortA = ((uint16_t)0x011C), /*!< USART1 Tx- Rx (PC3- PC2) remapping to PA2- PA3 */
  REMAP_Pin_USART1TxRxPortC = ((uint16_t)0x012C), /*!< USART1 Tx- Rx (PC3- PC2) remapping to PC5- PC6 */
  REMAP_Pin_USART1Clk       = ((uint16_t)0x014B), /*!< USART1 CK (PC4) remapping to PA0 */
  REMAP_Pin_SPI1Full        = ((uint16_t)0x0187), /*!< SPI1 MISO- MOSI- SCK- NSS(PB7- PB6- PB5- PB4)
                                                       remapping to PA2- PA3- PC6- PC5 */
  /* RMPCR2 register bits */
  REMAP_Pin_ADC1ExtTRIG1    = ((uint16_t)0x0201), /*!< ADC1 External Trigger 1 (PA6) remapping to PD0 */
  REMAP_Pin_TIM2TRIGPortA   = ((uint16_t)0x0202), /*!< TIM2 Trigger (PB3) remapping to PA4 */
  REMAP_Pin_TIM3TRIGPortA   = ((uint16_t)0x0204), /*!< TIM3 Trigger (PD1) remapping to PA5 */
  REMAP_Pin_TIM2TRIGLSE     = ((uint16_t)0x0208), /*!< TIM2 Trigger remapping to LSE */
  REMAP_Pin_TIM3TRIGLSE     = ((uint16_t)0x0210), /*!< TIM3 Trigger remapping to LSE */
  REMAP_Pin_SPI2Full        = ((uint16_t)0x0220), /*!< SPI2 MISO- MOSI- SCK- NSS(PG7- PG6- PG5- PG4)
                                                       remapping to PI3- PI2- PI1- PI0 */
  REMAP_Pin_TIM3TRIGPortG   = ((uint16_t)0x0240), /*!< TIM3 Trigger (PD1) remapping to PG3 */
  REMAP_Pin_TIM23BKIN       = ((uint16_t)0x0280), /*!< TIM2 Break Input (PA4) remapping to PG0
                                                           and TIM3 Break Input (PA5) remapping to PG1 */
  /* RMPCR3 register bits */
  REMAP_Pin_SPI1PortF       = ((uint16_t)0x0301), /*!< SPI1 MISO- MOSI- SCK- NSS(PB7- PB6- PB5- PB4)
                                                       remapping to PF0- PF1- PF2- PF3   */
  REMAP_Pin_USART3TxRxPortF = ((uint16_t)0x0302), /*!< USART3 Tx- Rx (PG1- PG0) remapping to PF0- PF1 */
  REMAP_Pin_USART3Clk       = ((uint16_t)0x0304), /*!< USART3 CK (PG2) remapping to PF2 */
  REMAP_Pin_TIM3Channel1    = ((uint16_t)0x0308), /*!< TIM3 Channel 1 (PB1) remapping to PI0 */
  REMAP_Pin_TIM3Channel2    = ((uint16_t)0x0310), /*!< TIM3 Channel 2 (PD0) remapping to PI3 */
  REMAP_Pin_CCO             = ((uint16_t)0x0320)  /*!< CCO (PC4) remapping to PE2 */
}REMAP_Pin_TypeDef;



extern volatile uint8_t Mode;


typedef union
{
    uint32_t    Num;   //警报值
    uint8_t     Arr[4];
}Typdef_AlarmValue;

typedef union
{
    uint32_t    Num;   //警报值
    uint8_t     Arr[4];
}Typdef_PmValue;


typedef struct
{
    uint8_t  sour_addr;			//源地址
    uint8_t  dst_addr;			//目标地址
    uint16_t payloadlength;     //命令数据长度
    uint16_t command;           //命令
    uint8_t mems[RXMAX];           //数据长度
}Typdef_DataFormat;


typedef struct
{
    uint16_t  Voltage;          //传感器电压
    uint32_t  Cnt_Minite;       //计时器，分钟
    uint16_t   Refresh_Minite;			//刷新计时器
    uint16_t  Batt_Minite;       //计时器，分钟
    bool   Refresh_flag;          //重新刷新标志位
    bool   Battfresh_flag;          //重新刷新标志位
    uint8_t Dev_ID[10];       //由服务器分配的设备ID
    bool Flag_wakeup;			//唤醒标志位
    uint8_t Flag_Warn;			//报警
    uint8_t Network_flag;				//是否连上网络
    uint8_t Mode_flag;				//子状态	
    uint8_t Key_Type;			//按键状态


    Typdef_AlarmValue PPM;               //读到的PPM的值
    Typdef_PmValue PM25;				//读到的pm2.5

    Typdef_PmValue PM10;				//读到的pm10
    Typdef_PmValue PM1_0;				//读到的pm10

    int32_t tem;				//读到的温度
    Typdef_AlarmValue hum;				//读到的湿度


}Typdef_ProgramPara;


extern Typdef_ProgramPara ProgramPara;
extern Typdef_DataFormat DataFormat;


extern volatile uint8_t flag_10ms;//10ms定时标志位  在Time2中断中置位 ，在main函数中清0
extern char ubUartRxBuf[RXMAX];//串口接收数组
extern volatile uint8_t Receive;
extern RTC_TimeTypeDef GETRTC_Time;
extern RTC_DateTypeDef GETRTC_Data;


void InitTimer2(void);
void InitTimer1(void);
void InitCpuClock(void);
void InitAll(void);
void Usart1Init(void);
void MCU_Gpio_Init(void);
void DelayApi(uint16_t uwDelayCnt);//延时函数，以定时器2为延时基准，最少延时2ms
void Read_ChipID_Init(Typdef_ProgramPara *programpara);
void Read_SetPPM(Typdef_ProgramPara *programpara);


#endif
