#ifndef __LED_H
#define __LED_H
/************************************************************************************
*�ļ���  ��led.h																	                                  *
*�ļ����ã�led����ͷ�ļ�													                                    *
*����    ��ũ����																	                                  *
*����QQ  ��382421307																                                  *
*�ļ�����ʱ�䣺2013/05/9			  												                              *	
*************************************************************************************/
#include "imapx200.h"

#define ON  1
#define OFF 0

#define LED1_BIT  (0x01<<2)


#define LED1(x) (x?(GPEDAT&=~LED1_BIT):(GPEDAT|=LED1_BIT))


void LED_GPIO_Config(void);
#endif /*����__LED_H*/
