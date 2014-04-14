#include "s3c6410.h"
#include "clock.h"



void clock_init(void)
{ 
    /*����APLL,MPLL,EPLL������ʱ�䣬�������õ���Ĭ��ֵ������ȥ��*/
    APLL_LOCK = 0x0000ffff;
	MPLL_LOCK = 0x0000ffff;
	EPLL_LOCK = 0x0000ffff;

	/*����CPUΪ�첽ģʽ����CPUʱ�� != HCLKʱ��Ҫ��Ϊ�첽ģʽ */
	OTHERS &= ~0xc0;
	/*�ȴ�CPU�����첽ģʽ*/
	while ((OTHERS & 0xf00) != 0);
    /*����ARMCLK=667Mhz��HCLKX2=266Mhz��HCLK=133Mhz��
    PCLK=66Mhz��CLKSECUR=66Mhz��CLKJPEG=66Mhz*/
	CLK_DIV0 = CLK_DIV0_VAL;
	/*APLL_FOUT=12*333/(3*2)=667Mhz*/
	APLL_CON = APLL_CON_VAL; 
	/*MPLL_FOUT=12*266/(3*2^2)=266Mhz*/
	MPLL_CON = MPLL_CON_VAL;  
	/*EPLL_FOUT=12*(32+0)/(1*2^2)=96Mhz*/
	EPLL_CON0=EPLL_CON0_VAL;
	EPLL_CON1=EPLL_CON1_VAL;
	/*ѡ��ʱ�ӣ�ALCK��MLCK��ELCK��ѡ��PLLʱ��*/
	CLK_SRC =  CLK_SRC_VAL;
}
