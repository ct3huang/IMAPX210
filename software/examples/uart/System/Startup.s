********************************************************************************************************
;                                ������ARM S3C6410�����ļ�������
;
;                 ˵��������S3C6410��������ļ����ο�ARM�ٷ�S3C2440A����
;									 	                          ----nongxiaoming
;********************************************************************************************************


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10				;�û�ģʽ����������ִ��ģʽ������Ӧ�ó���
Mode_FIQ        EQU     0x11				;�����ж�ģʽ�����ڸ������ݴ����ͨ������
Mode_IRQ        EQU     0x12				;�ⲿ�ж�ģʽ������ͨ�õ��жϴ���
Mode_SVC        EQU     0x13				;����ģʽ��ʹ�õ�һ�ֱ���ģʽ��
Mode_ABT        EQU     0x17				;���ݷ�����ֹģʽ����������洢�ô洢����
Mode_UND        EQU     0x1B				;δ����ָ����ֹģʽ����δ����ָ��ִ��ʱ�����ģʽ��
Mode_SYS        EQU     0x1F				;ϵͳģʽ��������Ȩ���Ĳ���ϵͳ����

I_Bit           EQU     0x80            	; ���Iλ����1�����ⲿ�жϱ���ֹ(IRQ is disabled)
F_Bit           EQU     0x40            	; ���Fλ����1��������жϱ���ֹ(FIQ is disabled)	
			
;----------------------- Stack and Heap Definitions ----------------------------

UND_Stack_Size  EQU     0x00000100		 	;���ø���ģʽջ��С
SVC_Stack_Size  EQU     0x00000100
ABT_Stack_Size  EQU     0x00000100
FIQ_Stack_Size  EQU     0x00000100
IRQ_Stack_Size  EQU     0x00000100
USR_Stack_Size  EQU     0x00000100


											;��ջ�Ĵ�С��Ҳ����Ҳ��ģʽ��ջ���
ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)


											;����һ����ջ�Σ�������ΪSTACK������Ϊ�ɶ���д�����ڴ浥Ԫ��ʼ��Ϊ0,
                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size		;SPACE -- αָ����ڷ���һ���ڴ浥Ԫ������0��ʼ������%ͬ��
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top									;��ջ�����ݽ����� ������Ÿ����,������ö�ջ������ַ



Heap_Size       EQU     0x00001000		  	;����Ѵ�С��һ��������õ�malloc���õ���
											;����һ������ΪHEAP�ɶ���д������ʼ���ڴ浥���ڴ浥Ԫ��

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base									;�ѵĻ�ַ
Heap_Mem        SPACE   Heap_Size			;���ڴ���ʼ��ַ���
__heap_limit								;�ѽ���

;----------------------- ���Ź���ʱ������ ----------------------------
WDT_BASE         EQU     0x20d90000            ; ���Ź�����ַ
WDT_CR_OFS       EQU     0x00                  ; ���Ź����ƼĴ�����ַƫ��
WDT_TORR_OFS       EQU     0x04                ; ���Ź����ݼĴ�����ַƫ��
WDT_CCVR_OFS       EQU     0x08                ; ���Ź������Ĵ�����ַƫ��

;// <e> ���Ź��Ĵ�������
;//   <h> ���Ź����ƼĴ��� (WTCON)
;//     <o1.8..15>  Prescaler Value <0-255>
;//     <o1.5>      ���Ź��Ĵ���ʹ��
;//     <o1.3..4>   ���Ź�ʱ�ӷ�Ƶ
;//       <0=> 16   <1=> 32  <2=> 64  <3=> 128
;//     <o1.2>      ���Ź��ж�ʹ��
;//     <o1.0>      ���Ź���λʹ��
;//   </h>
;//   <h> ���Ź����ݼĴ��� (WTDAT)
;//     <o2.0..15>  ����ֵ <0-65535>
;//   </h>
;// </e> ���Ź��Ĵ�������
WT_SETUP        EQU     1                   ;�Ƿ����ÿ��Ź���1Ϊ���ã�0Ϊ������
WTCON_Val       EQU     0x00000000          ;WTCON������ֵ
WTDAT_Val       EQU     0x00008000          ;WTDAT������ֵ



                PRESERVE8					 ;PRESERVE8 -- αָ�ָʾ��ǰ�ļ������ջΪ8�ֽڶ��롣
                

;  Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY ;����һ����ΪRESET�Ĵ����,����Ϊֻ��
                ARM 
               mrs	r0, CPSR
               bic	r0, r0, #31	; 0x1f
               orr	r0, r0, #211	; 0xd3
               msr	CPSR_fc, r0
			   bl	cpu_init_crit
; ���ÿ��Ź�---------------------------------------------------------------

                IF      WT_SETUP != 0             ;���WT_SETUP��Ϊ0��Ĭ��Ϊ1
                LDR     R0, =WDT_BASE             ;�����Ź�����ַ����R0
                LDR     R1, =WTCON_Val            ;�����Ź����ƼĴ�������ֵ����R1
                LDR     R2, =WTDAT_Val            ;�����Ź����ݼĴ�������ֵ����R2
                STR     R2, [R0, #WDT_CCVR_OFS]   ;���������ݴ��뿴�Ź������Ĵ���
                STR     R2, [R0, #WDT_TORR_OFS]   ;���������ݴ��뿴�Ź����ݼĴ���
                STR     R1, [R0, #WDT_CR_OFS]     ;���������ݴ��뿴�Ź����ƼĴ����������ǹرտ��Ź�
                ENDIF
                

 ; Setup Stack for each mode ----------------------------------------------------

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SYS:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

;  Enter User Mode and set its Stack Pointer
;               MSR     CPSR_c, #Mode_USR
                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

                ENDIF

                ;LDR SP,=1024*4

                IMPORT  __main
                ;LDR     R0, =Main
                ;BX      R0
			    BL __main
cpu_init_crit
                mov	r0, #0	; 0x0
                MCR	p15, 0, r0, c7, c7, 0
                mcr	p15, 0, r0, c8, c7, 0
                mrc	p15, 0, r0, c1, c0, 0
                bic	r0, r0, #4	; 0x4
                bic	r0, r0, #4096	; 0x1000
                bic	r0, r0, #2048	; 0x800
                orr	r0, r0, #4194304	; 0x400000
                mcr	p15, 0, r0, c1, c0, 0
                mrc	p15, 0, r0, c1, c0, 2
                orr	r0, r0, #15728640	; 0xf00000
                mcr	p15, 0, r0, c1, c0, 2
                mov	ip, lr
				bl	lowlevel_init
                mov	lr, ip
                BX lr
lowlevel_init
                mov	r5, lr
                mov	r0, #549453824	; 0x20c00000
                orr	r0, r0, #19	; 0x13
                mcr	p15, 0, r0, c15, c2, 4
                mov	r1, #1	; 0x1
                str	r1, [r0, #264]
			   
            IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF


                END

