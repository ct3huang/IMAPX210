#ifndef __UART_H
#define __UART_H
/************************************************************************************
*�ļ���  ��uart.h																	                                  *
*�ļ����ã�uart����ͷ�ļ�													                                    *
*����    ��ũ����																	                                  *
*����QQ  ��382421307																                                  *
*�ļ�����ʱ�䣺2013/05/9			  												                              *	
*************************************************************************************/
#include "imapx200.h"
#include "stdio.h"

void uart0_init(uint32_t baudrate);
void uart0_send_byte(uint8_t data);
void uart0_send_string(const  uint8_t *pt);
void debug(char* fmt, ...);
#endif /*__UART_H*/
