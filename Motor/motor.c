#include "motor.h"
/************************************************
���ߣ�
���� GND
���� 5V
���� ENA	-->PB0(PWM��������Ƶ����ת��)
���� ENB	-->PB1(PWM��������Ƶ����ת��)
(���ĸ����ſ��Ƶ����ת������)
���� IN1	-->PB12
���� IN2	-->PB13 
�������ꤣ�
���� IN3	-->PB14
���� IN4	-->PB15
���Ҳ���ꤣ�
���ߣ������
*************************************************/

/*************************************************
�������ƣ�void Motor_Init(void)
�������ܣ�С����ʼ��
��ڲ�������
���ڲ�������
*************************************************/
void Motor_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //

	GPIO_Init(GPIOB,&GPIO_InitStructure); 
}
/*************************************************
�������ƣ�void Motor_Enable(void)
�������ܣ�С���˶�ʹ��
��ڲ�������
���ڲ�������
*************************************************/
void Motor_Enable(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
}
/*************************************************
�������ƣ� void Advance(void)
�������ܣ�С��ǰ��
��ڲ�������
���ڲ�������
*************************************************/
void Advance(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);	
}

/*************************************************
�������ƣ�void Back(void)
�������ܣ�С������
��ڲ�������
���ڲ�������
*************************************************/
void Back(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);		
}

/*************************************************
�������ƣ�void Left(void)
�������ܣ�С����ת
��ڲ�������
���ڲ�������
*************************************************/
void Left(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);	//����
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);  //����
	GPIO_SetBits(GPIOB,GPIO_Pin_15);					
}

/*************************************************
�������ƣ�void Right(void)
�������ܣ�С����ת
��ڲ�������
���ڲ�������
*************************************************/
void Right(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);							
}

/*************************************************
�������ƣ�void Stop(void)
�������ܣ�С��ֹͣ
��ڲ�������
���ڲ�������
*************************************************/
void Stop(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);					
}
/*************************************************
�������ƣ�void TIM3_PWM_Init(void)
�������ܣ�ͨ������TIM_TimeBaseStructure.TIM_Period��ֵ�ı�PWM���ڣ�
					ͨ������TIM_OCInitStructure.TIM_Pulse��ֵ�ı�PWMռ�ձȣ�ʵ�ֵ���
					ʹ�õ���ͨ�ö�ʱ��TIM3��ͨ��3��4
��ڲ�����int speed�� 1-10 	���ռ�ձ�Ϊ100%
���ڲ�������
*************************************************/
void TIM3_PWM_Init(int speed)
{
	
	//C���Եı�׼ C89�������ڴ����ź��涨�����	C99������������λ�ö����Զ���ȣ���ħ�����н�������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/************************ʱ����ʼ���ṹ��************************************/
	//PWM������ f=72M/(7199+1)*(9+1) = 10K һ���ֱ���������
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 9; 
	TIM_TimeBaseStructure.TIM_Prescaler = 7199; 

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	/*************************GPIO���ŵĳ�ʼ��*************************************/	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Output Compare Active Mode configuration: Channel3 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = speed; //ռ�ձ�Ϊ100%
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx,PB0
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = speed;//ռ�ձ�Ϊ100%
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);			//PB1
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	//���������е�OCxȷ������channle����Ҫ��OC3����channel 3  
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ��� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
		
}

