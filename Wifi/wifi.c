/************************
*����:��ӵ�ESP8266WIFIоƬ�ĳ�ʼ��
*			{}
*�������ţ�
*ESP8266			STM32
*GND			->	GND
*3V3			->	3V3
*SCLK 		-> 	PA5
*MISO			->	PA6
*MOSI			->	PA7
*nCS			->	PA4
*nREST		->	PC4
*���ߣ������
*************************/
#include "wifi.h"
#include "usart.h"

//WIFI���������
u8 ssid[32] = "208";//WIFI������
u8 password[64] = "qiaoqiupup";//����
u16 remote_port = 8899; //Ŀ�Ķ˿ں�Ϊ8899
//char* remote_addr = "192.168.43.1"; //Ŀ��IP���ֻ�����·����������·���������IP��ַ�Ѿ����ֻ���MAC
																			//��ַ���а󶨣���������·������ԭ�������С��ֱ�������ֻ��ȵ�Ļ�
//																			//ÿ�η����IP��ַ��ȷ��������С�����Ӳ����ֻ�
//char* remote_addr = "192.168.1.103"; //Ŀ��IP���ֻ�����·����������·���������IP��ַ�Ѿ����ֻ���MAC
//																			//��ַ���а󶨣���������·������ԭ�������С��ֱ�������ֻ��ȵ�Ļ�
////																			//ÿ�η����IP��ַ��ȷ��������С�����Ӳ����ֻ�
char* remote_addr = "192.168.0.100"; //Ŀ��IP���ֻ�����·����������·���������IP��ַ�Ѿ����ֻ���MAC
																		//��ַ���а󶨣���������·������ԭ�������С��ֱ�������ֻ��ȵ�Ļ�
																		//ÿ�η����IP��ַ��ȷ��������С�����Ӳ����ֻ�
void WifiConfig(void)
{
	u8 success=0;
       
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
  LED_Init();
	M8266HostIf_Init();
#ifdef M8266WIFI_CONFIG_VIA_SPI
	success = M8266WIFI_Module_Init_Via_SPI();
#else
#error You should define M8266WIFI_CONFIG_VIA_SPI in brd_cfg.h
#endif
	 if(success)
	{
		for(int key=0; key<3; key++)  // Flash the Two LEDs in the Main Board
		{
			 LED_set(0, 0); LED_set(1, 0);  delay_ms(100);
			 LED_set(0, 1); LED_set(1, 0);  delay_ms(100);
			 LED_set(0, 0); LED_set(1, 1);  delay_ms(100);
			 LED_set(0, 1); LED_set(1, 1);  delay_ms(100);
		}
		
		if(1 == M8266WIFI_SPI_Set_Opmode(1,1,NULL))//����wifi�Ĺ�����sta��ģʽ��
		{
				printf("\r\n������WIFI������STAģʽ��\r\n");
		}
		
				printf("\r\n��������Ŀ��·������SSID��jiaxing��password��jiahewanshixing\r\n");
		while(!(M8266WIFI_SPI_STA_Connect_Ap(ssid,password,1,6,NULL)))//���ӵ���SSID�����룬�Ƿ񱣴����ӣ���ʱʱ�䣬����ֵ��
		{
				printf("\r\n���ͨĿ��·������Դ\r\n");					
		}
				printf("\r\n�����ӵ�Ŀ��·����\r\n");
		
				printf("\r\n��������Ŀ��IP��192.168.43.1��Ŀ�Ķ˿ںţ�8899\r\n");
		while((!(M8266WIFI_SPI_Setup_Connection(1,0,remote_addr,remote_port,0,5,NULL)))||(!(M8266WIFI_SPI_Setup_Connection(1,0,remote_addr,8898,1,5,NULL))))//TCP�ͻ��ˣ����һ����ַ��Ŀ��IP��Ŀ�Ķ˿ںţ����Ӻţ���ʱʱ�䣬����ֵ
		{ 
				printf("\r\n����ֻ�������\r\n");
			
		}
				printf("\r\n�����ӵ�Ŀ�ķ�����\r\n");
	}

}


