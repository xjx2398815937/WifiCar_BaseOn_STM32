#include "led.h"
/************************
*�������԰�����LED�ĳ�ʼ��
*�������ƣ�
*	LED0��ON�� ������
*	LED0��OFF�����ص�
*�������ţ�
*	LED0-->PB5
*	LED1-->PE5
*���ߣ������
*************************/
/*�Ƶ�������ŵĳ�ʼ��*/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*��ʼ��LED0*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED_0_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_0_GPIO_PORT,&GPIO_InitStruct);
	/*��ʼ��LED1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED_1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_1_GPIO_PORT,&GPIO_InitStruct);	
}
void LED_set(u8 led_no, u8 on)
{
	if(led_no==0)
	{
		if(on)
		   GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		else
			 GPIO_SetBits(GPIOB, GPIO_Pin_5);
	}
	else
	{
		if(on)
		   GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		else
			 GPIO_SetBits(GPIOE, GPIO_Pin_5);
	}
}
