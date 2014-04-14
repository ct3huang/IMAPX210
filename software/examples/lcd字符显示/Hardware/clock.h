#ifndef __CLOCK_H
#define __CLOCK_H

/*APLL_FOUT=12*333/(3*2)=666Mhz*/
#define APLL_CON_VAL  ((1<<31) | (333 << 16) | (3 << 8) |(1))
/*MPLL_FOUT=12*266/(3*2^2)=266Mhz*/
#define MPLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (2))
/*EPLL_FOUT=12*(32+0)/(1*2^2)=96Mhz*/
#define EPLL_CON0_VAL  ((1<<31) | (32 << 16) | (1 << 8) | (2))
#define EPLL_CON1_VAL  0

/*CLK_SRCʱ��ѡ��Ĵ���������ֵ��ACLK,MCLK,ECLK��ʹ��PLL*/
#define CLK_SRC_VAL   0x07  
/*����ARMCLK=667Mhz��HCLKX2=266Mhz��HCLK=133Mhz��
PCLK=66Mhz��CLKSECUR=66Mhz��CLKJPEG=66Mhz*/
#define CLK_DIV0_VAL     ((3<<24) | (3<<20) | (3<<18) | (3<<12) | (1<<8)) 

/*�������õ�һЩʱ��Ƶ�ʣ������ʱ�������޹�
��ֻ�Ƕ�����ⲿʹ�õ���ص�ʱ��ֵ*/
#define ACLK 667000000
#define MCLK 266000000
#define HCLK 133000000
#define HCLKX2 266000000
#define PCLK  66000000
#define CLKSECUR 66000000
#define CLKJPEG 66000000
#define CLKCAM  66000000
void clock_init(void);

#endif /*__CORECLOCK_H*/
