#ifndef __UART_H__
#define __UART_H__
#include <rtthread.h>

/*UART�Ĵ���*/
typedef struct imapx200_uart
{
rt_uint32_t DBUF;       /*LCR[7]=0,���ջ������Ĵ�����ֻ��*/
rt_uint32_t IER ;      /*LCR[7]=0,�ж�ʹ�ܼĴ�������д*/
rt_uint32_t IIR;       /*�жϱ��Ĵ�����ֻ��*/
rt_uint32_t LCR;       /*�߿��ƼĴ�������д*/
rt_uint32_t MCR;       /*ģʽ�ƼĴ�������д*/
rt_uint32_t LSR;       /*��״̬�Ĵ�����ֻ��*/
rt_uint32_t CSR;       /*CTS״̬�Ĵ�����ֻ��*/
rt_uint32_t LPDLL;     /*�͹���ʱ�ӷ�Ƶ�Ĵ���L����д*/
rt_uint32_t LPDLH;     /*�͹���ʱ�ӷ�Ƶ�Ĵ���H����д*/
}UART_TypeDef;

void rt_hw_uart_init(void);

#endif
