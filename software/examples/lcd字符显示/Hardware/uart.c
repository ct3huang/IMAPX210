#include "uart.h"
#include "clock.h"
/************************************************************************************
*�ļ���  ��uart.c																	                                  *
*�ļ����ã�uart����Դ�ļ�													                                    *
*����    ��ũ����																	                                  *
*����QQ  ��382421307																                                  *
*�ļ�����ʱ�䣺2013/05/9			  												                              *	
*************************************************************************************/
void uart0_init(uint32_t baudrate)
{
  /*���GPA0��GPA1����*/
  GPACON&=0x00;
  /*����GPA0���ӵ�RXD0��GPA1���ӵ�TXD0*/
  GPACON|=0x22;
  /*����λ��ͨģʽ����żУ��ΪNone������λΪ8��ֹͣλΪ1*/
 // ULCON0=0x03;
  //UBRDIV0=(PCLK/(baudrate*16)-1);
}
//���ڷ���
void uart0_send_byte(uint8_t data)
{   
     while((LSR0&(0x01<<5))==0);
		 THR0=data;
}
//���ڽ���
void uart0_send_string(const  uint8_t *pt)
{
    while(*pt)
	{
    uart0_send_byte(*pt);
	pt++;
	}
}
//����3����һ���ֽ�
void uart3_send_byte(uint8_t data)
{   
     while((LSR3&(0x01<<5))==0);
		 THR3=data;
}
//����3����һ���ַ�
void uart3_send_string(const  uint8_t *pt)
{
    while(*pt)
	{
    uart3_send_byte(*pt);
	pt++;
	}
}

//����printf�ĵ��Ժ���
void debug(char* fmt, ...)
{
    char* pArg= (void*)0;//�ȼ���ԭ����va_list
    char c;
	  char buf[64];
    pArg = (char*) &fmt;//ע�ⲻҪд�� p=fmt !! ��Ϊ����Ҫ�Բ���ȡַ��������ȡֵ
    pArg += sizeof(fmt);//�ȼ���ԭ����va_start        
    
    do
    {
        c =*fmt;
        if (c != '%')
        {
            uart3_send_byte(c);//��ԭ������ַ�
        }
        else
        {
            //����ʽ�ַ��������
            switch(*++fmt)
            {
                case 'd':
                    sprintf(buf,"%d",*((int*)pArg));  
                    pArg += sizeof(int); //�ȼ���ԭ����va_arg								
                    break;
                case 'x':
                    sprintf(buf,"%x",*((int*)pArg));
								    pArg += sizeof(int); //�ȼ���ԭ����va_arg
                    break;
				case 'f':
					sprintf(buf,"%f",*((float*)pArg));
					pArg += sizeof(float); //�ȼ���ԭ����va_arg
                default:
                    break;
            }
           uart3_send_string((const uint8_t *)buf);
        }
        ++fmt;
    }while (*fmt != '\0');
    pArg = (void*)0; //�ȼ���va_end
    return;
}
