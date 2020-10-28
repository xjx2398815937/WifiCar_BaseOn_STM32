#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "ultrasonic.h"
#include "motor.h"
#include "wifi.h"
#include "ov7725.h"
#include "sccb.h"

uint8_t retry = 0;
extern uint8_t Ov7725_vsync;
extern OV7725_MODE_PARAM cam_mode;

void Init()//��ʼ������
{
	//���ڵĳ�ʼ��
	USART_Config();
	
	printf("\r\n��ӭʹ������˵ı�ҵ���-WIFI����С��\r\n");
	printf("\r\n����ϵͳ��ʼ��\r\n");
	
	printf("\r\n���ڳ�ʼ�����\r\n");
	
	//LED�ĳ�ʼ��
	LED_Init();
	printf("\r\nLED��ʼ�����\r\n");
	
	//�������������ĳ�ʼ��
	Hcsr04Init1(); 
	printf("\r\n��������ʼ�����\r\n");
	
	//��������ĳ�ʼ��
	Motor_Init();
	Motor_Enable();
	TIM3_PWM_Init(10);
	printf("\r\n���������ʼ�����\r\n");
	
	//WIFI�ĳ�ʼ��
	printf("\r\n����WIFI����\r\n");
	WifiConfig();
	
	OV7725_GPIO_Config();
	while(OV7725_Init() != SUCCESS)
	{
		if(retry==0)
		{
			printf("\r\nû�м�⵽OV7725����ͷ�����ͨ����ͷ\r\n");
			retry = 1;
		}
	}
	/*��������ͷ����������ģʽ*/
	OV7725_Special_Effect(cam_mode.effect);
	/*����ģʽ*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*���Ͷ�*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*���ն�*/
	OV7725_Brightness(cam_mode.brightness);
	/*�Աȶ�*/
	OV7725_Contrast(cam_mode.contrast);
	/*����Ч��*/
	OV7725_Special_Effect(cam_mode.effect);
	/*����ͼ�������ģʽ��С*/
	OV7725_Window_Set(	cam_mode.cam_sx,
											cam_mode.cam_sy,
											cam_mode.cam_width,
											cam_mode.cam_height,
											cam_mode.QVGA_VGA);
	printf("\r\nOV7725����ͷ��ʼ�����\r\n");
	Ov7725_vsync = 0;
	
	
}
int main()
{
	Init();
	uint8_t data[1];//���������յ������ݣ�֮����з���
	uint8_t length[4];
	
	while(1)
	{
		
			
			Length(length);
			M8266WIFI_SPI_Send_Data(length,4,0,NULL);

			if(M8266WIFI_SPI_Has_DataReceived())
			{
				M8266WIFI_SPI_RecvData(data,1,1,0,NULL);
				switch(data[0])
				{
					//�Զ���ʻ
					case '0':
						while(!M8266WIFI_SPI_Has_DataReceived())
						{
							Length(length);
							M8266WIFI_SPI_Send_Data(length,4,0,NULL);
							
							if(Hcsr04GetLength() > 45)
							{
								Advance();
							}
							else
							{
								Stop();
								Left();
							}
						}
						break;
					//�ֶ�����
					case '1':
						Stop();
						break;
					//ǰ��
					case '2':
						Advance();
						break;
					//����
					case '3':
						Back();
						break;
					//��ת
					case '4':
						Left();
						break;
					//��ת
					case '5':
						Right();
						break;
					//�ٶȿ�
					case '6':
						TIM3_PWM_Init(10);
						Stop();
						break;
					//�ٶ���
					case '7':
						TIM3_PWM_Init(8);
						Stop();					
						break;
					//ֹͣ
					case '8':
						Stop();
						break;
					case '9':
						while(1)
						{
								
								/*���յ���ͼ����з���Phone*/
								if(Ov7725_vsync == 2 )
								{
									FIFO_PREPARE;  			/*FIFO׼��*/					
									ImagDataSentToPhone(	cam_mode.cam_width,
																				cam_mode.cam_height);	/*�ɼ����������ֻ�*/
									Ov7725_vsync = 0;
								}
								M8266WIFI_SPI_RecvData(data,1,1,0,NULL);
								if(data[0]=='5')
								{
									break;
								}
						}
						break;
						
					default:
						break;
				}

			}


		}
		
	
}

