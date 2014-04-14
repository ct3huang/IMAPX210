#ifndef __X200_H
#define __X200_H

#include <stdint.h>
#include "imapx200_gpio.h"
#include "imapx200_uart.h"
#include "imapx200_lcd.h"
#include "imapx200_clock.h"
#ifdef __cplusplus
extern "C" {
#endif

/*����λ����*/
#define BIT(x) (BIT0<<x)
#define BIT0            0x00000001   
#define BIT1            0x00000002   
#define BIT2            0x00000004   
#define BIT3            0x00000008   
#define BIT4            0x00000010   
#define BIT5            0x00000020   
#define BIT6            0x00000040   
#define BIT7            0x00000080   
#define BIT8            0x00000100   
#define BIT9            0x00000200   
#define BIT10           0x00000400   
#define BIT11           0x00000800   
#define BIT12           0x00001000   
#define BIT13           0x00002000   
#define BIT14           0x00004000   
#define BIT15           0x00008000   
#define BIT16           0x00010000   
#define BIT17           0x00020000   
#define BIT18           0x00040000   
#define BIT19           0x00080000   
#define BIT20           0x00100000   
#define BIT21           0x00200000   
#define BIT22           0x00400000   
#define BIT23           0x00800000   
#define BIT24           0x01000000   
#define BIT25           0x02000000   
#define BIT26           0x04000000   
#define BIT27           0x08000000   
#define BIT28           0x10000000   
#define BIT29           0x20000000   
#define BIT30           0x40000000   
#define BIT31           0x80000000      



/*��ʱ���Ĵ���*/
#define TCFG0				    (*(volatile unsigned *)(0x7F006000))   /*��ʱ�����üĴ���0,��д*/
#define TCFG1				    (*(volatile unsigned *)(0x7F006004))   /*��ʱ�����üĴ���1,��д*/
#define TCON				    (*(volatile unsigned *)(0x7F006008))   /*��ʱ�����ƼĴ���,��д*/
/*��ʱ��0*/
#define TCNTB0				    (*(volatile unsigned *)(0x7F00600C))   /*��ʱ��0����������,��д*/
#define TCMPB0				    (*(volatile unsigned *)(0x7F006010))   /*��ʱ��0�Ƚϻ���Ĵ���,��д*/
#define TCNTO0				    (*(volatile unsigned *)(0x7F006014))   /*��ʱ��0�����۲�Ĵ���,��*/
/*��ʱ��1*/
#define TCNTB1				    (*(volatile unsigned *)(0x7F006018))   /*��ʱ��1����������,��д*/
#define TCMPB1				    (*(volatile unsigned *)(0x7F00601C))   /*��ʱ��1�Ƚϻ���Ĵ���,��д*/
#define TCNTO1				    (*(volatile unsigned *)(0x7F006020))   /*��ʱ��1�����۲�Ĵ���,��*/
/*��ʱ��2*/
#define TCNTB2				    (*(volatile unsigned *)(0x7F006024))   /*��ʱ��2����������,��д*/
#define TCMPB2				    (*(volatile unsigned *)(0x7F006028))   /*��ʱ��2�Ƚϻ���Ĵ���,��д*/
#define TCNTO2				    (*(volatile unsigned *)(0x7F00602C))   /*��ʱ��2�����۲�Ĵ���,��*/
/*��ʱ��3*/
#define TCNTB3				    (*(volatile unsigned *)(0x7F006030))   /*��ʱ��3����������,��д*/
#define TCMPB3				    (*(volatile unsigned *)(0x7F006034))   /*��ʱ��3�Ƚϻ���Ĵ���,��д*/
#define TCNTO3				    (*(volatile unsigned *)(0x7F006038))   /*��ʱ��3�����۲�Ĵ���,��*/
/*��ʱ��4*/
#define TCNTB4				    (*(volatile unsigned *)(0x7F00603C))   /*��ʱ��4����������,��д*/
#define TCNTO4				    (*(volatile unsigned *)(0x7F006040))   /*��ʱ��4�����۲�Ĵ���,��*/

#define TINT_CSTAT				(*(volatile unsigned *)(0x7F006044))   /*��ʱ���жϿ��ƺ�״̬�Ĵ���,��д*/

/*�ж�ʹ�ܼĴ���*/
#define VIC0ADDRESS				(*(volatile unsigned *)(0x71200f00))   /*ʸ����ַ�Ĵ���0,��д*/
#define VIC1ADDRESS			  (*(volatile unsigned *)(0x71300f00))   /*ʸ����ַ�Ĵ���1,��д*/


#define VIC0VECTADDR				    (*(volatile unsigned *)(0x71200100))   /*ʸ����ַ�Ĵ���0,��д*/
#define VIC1VECTADDR				    (*(volatile unsigned *)(0x71300100))   /*ʸ����ַ�Ĵ���1,��д*/

#define VIC0INTENABLE				    (*(volatile unsigned *)(0x71200010))   /*�ж�ʹ�ܼĴ���0,��д*/
#define VIC1INTENABLE				    (*(volatile unsigned *)(0x71300010))   /*�ж�ʹ�ܼĴ���1,��д*/

#define VIC0INTENCLEAR				    (*(volatile unsigned *)(0x71200014))   /*�ж�ʹ������Ĵ���0,д*/
#define VIC1INTENCLEAR				    (*(volatile unsigned *)(0x71300014))   /*�ж�ʹ������Ĵ���1,д*/

#ifdef __cplusplus
}
#endif
#endif /*end __S3C6410_H*/
