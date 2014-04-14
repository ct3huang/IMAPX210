#ifndef __IMAP_UART_H
#define __IMAP_UART_H
/*UART�Ĵ���*/

/*uart0�Ĵ�������*/
#define RBR0        (*(volatile unsigned *)(0x20E20000))        /*LCR[7]=0,���ջ������Ĵ�����ֻ��*/
#define THR0        (*(volatile unsigned *)(0x20E20000))        /*LCR[7]=0,���ͻ������Ĵ�����ֻд*/
#define DLL0        (*(volatile unsigned *)(0x20E20000))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define DLH0        (*(volatile unsigned *)(0x20E20004))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define IER0        (*(volatile unsigned *)(0x20E20004))        /*LCR[7]=0,�ж�ʹ�ܼĴ�������д*/
#define IIR0        (*(volatile unsigned *)(0x20E20008))        /*�жϱ��Ĵ�����ֻ��*/
#define FCR0        (*(volatile unsigned *)(0x20E20008))        /*FIFO���ƼĴ�����ֻд*/
#define LCR0        (*(volatile unsigned *)(0x20E2000C))        /*�߿��ƼĴ�������д*/
#define MCR0        (*(volatile unsigned *)(0x20E20010))        /*ģʽ�ƼĴ�������д*/
#define LSR0        (*(volatile unsigned *)(0x20E20014))        /*��״̬�Ĵ�����ֻ��*/
#define CSR0        (*(volatile unsigned *)(0x20E20018))        /*CTS״̬�Ĵ�����ֻ��*/
#define LPDLL0        (*(volatile unsigned *)(0x20E20020))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define LPDLH0        (*(volatile unsigned *)(0x20E20024))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define USR0        (*(volatile unsigned *)(0x20E2007C))          /*UART״̬�Ĵ�����ֻ��*/
#define TFL0        (*(volatile unsigned *)(0x20E20080))          /*FIFO���伶��Ĵ�����ֻ��*/
#define RFL0        (*(volatile unsigned *)(0x20E20084))          /*FIFO���ռ���Ĵ�����ֻ��*/
#define HTX0        (*(volatile unsigned *)(0x20E200A4))          /*UART�쳣TX�Ĵ�������д*/
#define DMASA0        (*(volatile unsigned *)(0x20E200A8))        /*DAM���Ӧ��Ĵ�����ֻд*/
#define CKSR0        (*(volatile unsigned *)(0x20E20100))          /*UARTʱ��ѡ��Ĵ�������д*/

/*uart1�Ĵ�������*/
#define RBR1        (*(volatile unsigned *)(0x20E21000))        /*LCR[7]=0,���ջ������Ĵ�����ֻ��*/
#define THR1        (*(volatile unsigned *)(0x20E21000))        /*LCR[7]=0,���ͻ������Ĵ�����ֻд*/
#define DLL1        (*(volatile unsigned *)(0x20E21000))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define DLH1        (*(volatile unsigned *)(0x20E21004))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define IER1        (*(volatile unsigned *)(0x20E21004))        /*LCR[7]=0,�ж�ʹ�ܼĴ�������д*/
#define IIR1        (*(volatile unsigned *)(0x20E21008))        /*�жϱ��Ĵ�����ֻ��*/
#define FCR1        (*(volatile unsigned *)(0x20E21008))        /*FIFO���ƼĴ�����ֻд*/
#define LCR1        (*(volatile unsigned *)(0x20E2100C))        /*�߿��ƼĴ�������д*/
#define MCR1        (*(volatile unsigned *)(0x20E21010))        /*ģʽ�ƼĴ�������д*/
#define LSR1        (*(volatile unsigned *)(0x20E21014))        /*��״̬�Ĵ�����ֻ��*/
#define CSR1        (*(volatile unsigned *)(0x20E21018))        /*CTS״̬�Ĵ�����ֻ��*/
#define LPDLL1        (*(volatile unsigned *)(0x20E21020))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define LPDLH1        (*(volatile unsigned *)(0x20E21024))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define USR1        (*(volatile unsigned *)(0x20E2107C))          /*UART״̬�Ĵ�����ֻ��*/
#define TFL1        (*(volatile unsigned *)(0x20E21080))          /*FIFO���伶��Ĵ�����ֻ��*/
#define RFL1        (*(volatile unsigned *)(0x20E21084))          /*FIFO���ռ���Ĵ�����ֻ��*/
#define HTX1        (*(volatile unsigned *)(0x20E210A4))          /*UART�쳣TX�Ĵ�������д*/
#define DMASA1        (*(volatile unsigned *)(0x20E210A8))        /*DAM���Ӧ��Ĵ�����ֻд*/
#define CKSR1        (*(volatile unsigned *)(0x20E21100))          /*UARTʱ��ѡ��Ĵ�������д*/
/*uart2�Ĵ�������*/
#define RBR2        (*(volatile unsigned *)(0x20E22000))        /*LCR[7]=0,���ջ������Ĵ�����ֻ��*/
#define THR2        (*(volatile unsigned *)(0x20E22000))        /*LCR[7]=0,���ͻ������Ĵ�����ֻд*/
#define DLL2        (*(volatile unsigned *)(0x20E22000))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define DLH2        (*(volatile unsigned *)(0x20E22004))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define IER2        (*(volatile unsigned *)(0x20E22004))        /*LCR[7]=0,�ж�ʹ�ܼĴ�������д*/
#define IIR2        (*(volatile unsigned *)(0x20E22008))        /*�жϱ��Ĵ�����ֻ��*/
#define FCR2        (*(volatile unsigned *)(0x20E22008))        /*FIFO���ƼĴ�����ֻд*/
#define LCR2        (*(volatile unsigned *)(0x20E2200C))        /*�߿��ƼĴ�������д*/
#define MCR2        (*(volatile unsigned *)(0x20E22010))        /*ģʽ�ƼĴ�������д*/
#define LSR2        (*(volatile unsigned *)(0x20E22014))        /*��״̬�Ĵ�����ֻ��*/
#define CSR2        (*(volatile unsigned *)(0x20E22018))        /*CTS״̬�Ĵ�����ֻ��*/
#define LPDLL2        (*(volatile unsigned *)(0x20E22020))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define LPDLH2        (*(volatile unsigned *)(0x20E22024))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define USR2        (*(volatile unsigned *)(0x20E2207C))          /*UART״̬�Ĵ�����ֻ��*/
#define TFL2        (*(volatile unsigned *)(0x20E22080))          /*FIFO���伶��Ĵ�����ֻ��*/
#define RFL2        (*(volatile unsigned *)(0x20E22084))          /*FIFO���ռ���Ĵ�����ֻ��*/
#define HTX2        (*(volatile unsigned *)(0x20E220A4))          /*UART�쳣TX�Ĵ�������д*/
#define DMASA2        (*(volatile unsigned *)(0x20E220A8))        /*DAM���Ӧ��Ĵ�����ֻд*/
#define CKSR2        (*(volatile unsigned *)(0x20E22100))          /*UARTʱ��ѡ��Ĵ�������д*/

/*uart3�Ĵ�������*/
#define RBR3        (*(volatile unsigned *)(0x20E23000))        /*LCR[7]=0,���ջ������Ĵ�����ֻ��*/
#define THR3        (*(volatile unsigned *)(0x20E23000))        /*LCR[7]=0,���ͻ������Ĵ�����ֻд*/
#define DLL3        (*(volatile unsigned *)(0x20E23000))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define DLH3        (*(volatile unsigned *)(0x20E23004))        /*LCR[7]=1,ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define IER3        (*(volatile unsigned *)(0x20E23004))        /*LCR[7]=0,�ж�ʹ�ܼĴ�������д*/
#define IIR3        (*(volatile unsigned *)(0x20E23008))        /*�жϱ��Ĵ�����ֻ��*/
#define FCR3        (*(volatile unsigned *)(0x20E23008))        /*FIFO���ƼĴ�����ֻд*/
#define LCR3        (*(volatile unsigned *)(0x20E2300C))        /*�߿��ƼĴ�������д*/
#define MCR3        (*(volatile unsigned *)(0x20E23010))        /*ģʽ�ƼĴ�������д*/
#define LSR3        (*(volatile unsigned *)(0x20E23014))        /*��״̬�Ĵ�����ֻ��*/
#define CSR3        (*(volatile unsigned *)(0x20E23018))        /*CTS״̬�Ĵ�����ֻ��*/
#define LPDLL3        (*(volatile unsigned *)(0x20E23020))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���L����д*/
#define LPDLH3        (*(volatile unsigned *)(0x20E23024))        /*�͹���ʱ�ӷ�Ƶ�Ĵ���H����д*/
#define USR3        (*(volatile unsigned *)(0x20E2307C))          /*UART״̬�Ĵ�����ֻ��*/
#define TFL3        (*(volatile unsigned *)(0x20E23080))          /*FIFO���伶��Ĵ�����ֻ��*/
#define RFL3        (*(volatile unsigned *)(0x20E23084))          /*FIFO���ռ���Ĵ�����ֻ��*/
#define HTX3        (*(volatile unsigned *)(0x20E230A4))          /*UART�쳣TX�Ĵ�������д*/
#define DMASA3        (*(volatile unsigned *)(0x20E230A8))        /*DAM���Ӧ��Ĵ�����ֻд*/
#define CKSR3        (*(volatile unsigned *)(0x20E23100))          /*UARTʱ��ѡ��Ĵ�������д*/

#endif
