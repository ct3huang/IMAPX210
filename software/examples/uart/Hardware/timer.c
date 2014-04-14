#include "timer.h"

#define VIC0VECTADDR23		(*(volatile unsigned *)(0x71200100+4*23))
#define VIC0VECTADDR7		(*(volatile unsigned *)(0x71200100+4*7))
int i=0;
//��ʱ����������
void __irq Isr_Timer0(void)
{ 

	TCON |=0;
	TINT_CSTAT |=1<<5;		//�����ʱ��״̬λ
	i++;
	VIC0ADDRESS=0xffffffff;//����жϱ�־λ
	TCON |=1;
    //debug("timer:%d\n",i);
}

//extern void OS_CPU_IRQ_ISR(void);
 void timer_init(void)
 {
    TINT_CSTAT=1<<5;			//�����ʱ��״̬λ
	 TINT_CSTAT |= 1<<0;       //��timer0�ж�,����timer0�жϷ���
	 VIC0INTENABLE |= 1<<23;   //��timer0��ʹ��
	 VIC0VECTADDR23=(volatile unsigned )Isr_Timer0;//�жϷ��������
	 
	// VIC0VECTADDR7=(volatile unsigned long)OS_CPU_IRQ_ISR;
	 TCFG0 =65;   			// ���÷�Ƶ����(66��Ƶ), ��ʱ��ʱ��Ƶ��Ϊ1Mhz
	 TCNTB0 = 1000;     //���ó�ֵ������TCTB0
	 TCON |= 1<<1;      	//���ó�ֵ��Ҫ����TCNTB
	 TCON |= 1<<3;     	//�Զ���װ����
	 TCON &= ~(1<<1);   	//����Update TCNTB0,TCMPB0
	 TCON |= 1<<0;       	//timer0 open;
 }
