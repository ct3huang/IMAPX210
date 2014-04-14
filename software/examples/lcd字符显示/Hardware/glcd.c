#include "glcd.h"
/************************************************************************************
*�ļ���  ��glcd.c																	                                  *
*�ļ����ã�lcd����Դ�ļ�													                                    *
*����    ��ũ����																	                                  *
*����QQ  ��382421307																                                  *
*�ļ�����ʱ�䣺2013/05/9			  												                              *	
*************************************************************************************/

/*LCD���ò���*/
#define  LCD_HFP		134		   /*LCDˮƽͬ��ǰ�� */
#define  LCD_HSW		32		   /* LCDˮƽͬ�������� */
#define  LCD_HBP		250		   /*LCDˮƽͬ�����*/
#define  LCD_VFP		10		   /*LCD��ֱͬ��ǰ�� */
#define  LCD_VSW		4		     /*LCD��ֱͬ��������*/
#define  LCD_VBP		14		   /*LCD��ֱͬ�����*/
#define  LCD_HRES		1024	   /*LCDˮƽ���ص�*/
#define  LCD_VRES		600		   /*LCD��ֱ���ص�*/
#define  LCD_RGB		0x6		   /* RGB��� */
//#define  LCD_PIXEL_CLOCK	18519 /* 1000,000,000,000 / vclk */
//#define  LCD_IDS_CFG	0x1e1e	/* this value will be put in DIV_CFG4 */
#define  LCD_CLK_DIV	0	/* this value will be put in DIV_CFG4 */


#define  LCD_VFRAME_FREQ	60		  /*ˢ��Ƶ��*/
#define  LCD_HRES_OSD	 LCD_HRES		/* ˮƽ���ص�*/
#define  LCD_VRES_OSD	 LCD_VRES		/*��ֱ���ص�*/
#define  LCD_HRES_OSD_VIRTUAL	LCD_HRES	/*����ˮƽ���ص�*/
#define  LCD_VRES_OSD_VIRTUAL	LCD_VRES		/* ���ⴹֱ���ص�*/


#define LCD_XSIZE   LCD_HRES
#define LCD_YSIZE   LCD_HRES

unsigned long *glcd_index;

  /*Һ����������*/
static sFONT *LCD_Currentfonts;

  /*Һ������ǰ��ɫ�ͱ���ɫ*/
static uint32_t TextColor = 0xFFFFFF, BackColor = 0x000000;

#define CONFIG_FB_IMAP_BPP24

/**************************************************************************************************************
 * ��������glcd_gpio_config()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD�ܽ����ú���
 * ����  ����ʼ��ʱ����        
 *****************************************************************************************************************/
static void glcd_gpio_config(void)
{
 /*����GPM0~GPM15���Ӷ�VD0��VD15*/
 GPMCON=0xaaaaaaaa;
	GPMPUD=0x00000000;
 /*����GPN���ӵ�LCD*/
 GPNCON=0x2aaaaaa;
	GPNPUD=0x00000000;
	//���ñ�����Ϊ���
  GPACON&=~(0x3<<12);
  GPACON|=(0x01<<12);
	//��LCD��Դ
  GPADAT|=(0x01<<6);
 
} 
/**************************************************************************************************************
 * ��������glcd_init()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD��ʼ������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_init(void )
{
   
	glcd_gpio_config();
	/* 2. ��ʼ��display controller 
	 * 2.1 hsync,vsync,vclk,vden�ļ��Ժ�ʱ�����
	 * 2.2 ����������(�ֱ���),������ɫ�ĸ�ʽ
	 * 2.3 �����Դ�(frame buffer),д��display controller
	 */

	LCDCON1 = IMAP_LCDCON1_PNRMODE_TFTLCD | IMAP_LCDCON1_ENVID_DISABLE |IMAP_LCDCON1_CLKVAL(LCD_CLK_DIV);
	LCDCON2 = IMAP_LCDCON2_VBPD(LCD_VBP - 1) | IMAP_LCDCON2_LINEVAL(LCD_VRES - 1) | IMAP_LCDCON2_VFPD(LCD_VFP - 1) | IMAP_LCDCON2_VSPW(LCD_VSW - 1);
	LCDCON3 = IMAP_LCDCON3_HBPD(LCD_HBP - 1) | IMAP_LCDCON3_HOZVAL(LCD_HRES - 1) | IMAP_LCDCON3_HFPD(LCD_HFP - 1);
	LCDCON4 = IMAP_LCDCON4_HSPW(LCD_HSW - 1);
	LCDCON5 = (LCD_RGB << 24) | IMAP_LCDCON5_INVVCLK_FALLING_EDGE | IMAP_LCDCON5_INVVLINE_INVERTED | IMAP_LCDCON5_INVVFRAME_INVERTED | IMAP_LCDCON5_INVVD_NORMAL| IMAP_LCDCON5_INVVDEN_NORMAL | IMAP_LCDCON5_INVPWREN_NORMAL | IMAP_LCDCON5_PWREN_ENABLE;
  
	OVCDCR = IMAP_OVCDCR_IFTYPE_RGB,

#if defined (CONFIG_LCD_BPP8)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;

#elif defined (CONFIG_LCD_BPP16)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;

	
#elif defined (CONFIG_LCD_BPP18)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;


#elif defined (CONFIG_LCD_BPP19)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;

#elif defined (CONFIG_LCD_BPP24)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;


#elif defined (CONFIG_LCD_BPP25)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;

#elif defined (CONFIG_LCD_BPP28)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;


#elif defined (CONFIG_LCD_BPP32)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;

#endif

	OVCW0PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	
	OVCW0PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(LCD_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(LCD_VRES_OSD - 1),
	OVCW0CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,

#if (CONFIG_FB_IMAP_NUM > 1)
	OVCW1PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	OVCW1PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(IMAPFB_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(IMAPFB_VRES_OSD - 1),
	OVCW1PCCR = IMAP_OVCWxPCCR_ALPHA0_R(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA0_G(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA0_B(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_R(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA1_G(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_B(IMAPFB_MAX_ALPHA_LEVEL),
	OVCW1CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,
#endif

#if (CONFIG_FB_IMAP_NUM > 2)	
	OVCW2PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	OVCW2PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(IMAPFB_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(IMAPFB_VRES_OSD - 1),
	OVCW2PCCR = IMAP_OVCWxPCCR_ALPHA0_R(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA0_G(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA0_B(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_R(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA1_G(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_B(IMAPFB_MAX_ALPHA_LEVEL),
	OVCW2CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,
#endif

#if (CONFIG_FB_IMAP_NUM > 3)
	OVCW3PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	OVCW3PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(IMAPFB_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(IMAPFB_VRES_OSD - 1),
	OVCW3PCCR = IMAP_OVCWxPCCR_ALPHA0_R(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA0_G(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA0_B(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_R(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA1_G(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_B(IMAPFB_MAX_ALPHA_LEVEL),
	OVCW3CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,
#endif	
 //ѡ��window0��BUF0��ʹ������BUF��ʹ��24BPP_RGB888ģʽ
 OVCW0CR=IMAP_OVCWxCR_BUFSEL_BUF0|IMAP_OVCWxCR_BUFNUM_2BUFS	|IMAP_OVCWxCR_BPPMODE_24BPP_RGB888;
 //����window0��BUF0��framebuffer��ַ
 OVCW0B0SAR =FRAME_BUFFER;
	glcd_index=(unsigned long*)FRAME_BUFFER;
	glcd_clear(BLUE);
	glcd_display_on();
	glcd_set_font(&Font8x16);
}

/**************************************************************************************************************
 * ��������backlight_enable()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD����ʹ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void backlight_enable(void)
{
	//�򿪱���
	GPFDAT |= (1<<6);
}
/**************************************************************************************************************
 * ��������backlight_disable()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD����ʧ�ܺ���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void backlight_disable(void)
{
	//�رձ���
	GPFDAT &= ~(1<<6);
}

/**************************************************************************************************************
 * ��������lcd_power_on()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD��Դʹ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void lcd_power_on(void)
{
	//ʹ��LCD��PWR
uint32_t tmp;
	backlight_enable();
	tmp = LCDCON5;
	LCDCON5=tmp|IMAP_LCDCON5_PWREN_ENABLE;
}
/**************************************************************************************************************
 * ��������lcd_power_off()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD��Դ�ر�
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void lcd_power_off(void)
{ 
	//ʧ����LCD��PWR
   uint32_t tmp;
	backlight_disable();
	tmp = LCDCON5;
	LCDCON5=tmp&~IMAP_LCDCON5_PWREN_ENABLE;
}
/**************************************************************************************************************
 * ��������glcd_display_on()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD������ʾ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_display_on(void)
{
uint32_t tmp;
	tmp = LCDCON1;
	LCDCON1=tmp|IMAP_LCDCON1_ENVID_ENABLE;
 //��ʾwindow0
	tmp=OVCW0CR;
	OVCW0CR=tmp| IMAP_OVCWxCR_ENWIN_ENABLE;
}
/**************************************************************************************************************
 * ��������glcd_display_off()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD�ر���ʾ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_display_off(void)
{
	uint32_t tmp;
	tmp = LCDCON1;
  LCDCON1=tmp & ~IMAP_LCDCON1_ENVID_ENABLE;
	//����ʾwindow0
	tmp=OVCW0CR;
	OVCW0CR=tmp&~IMAP_OVCWxCR_ENWIN_ENABLE;
}

/**************************************************************************************************************
 * ��������glcd_clear()
 * ����  ��uint32_t color ˢ����ɫ
 * ���  ��void
 * ����  ��LCD��������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_clear(uint32_t color)
{
	volatile unsigned long *p = (volatile unsigned long*)FRAME_BUFFER;
	int x, y;
	
	for (y = 0; y < LCD_YSIZE; y++)
	{
		for (x = 0; x < LCD_XSIZE; x++)
		{
			*p++ =color;  /* red */
		}
	}
}
/**************************************************************************************************************
 * ��������glcd_set_cursor()
 * ����  ��uint16_t x, uint16_t y �趨����Ļ��Xֵ��Yֵ
 * ���  ��void
 * ����  ��LCD���ù��λ�ú���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_set_cursor(uint16_t x, uint16_t y)
{
 glcd_index = ((unsigned long*)FRAME_BUFFER) + x + y*LCD_XSIZE;
}
/**************************************************************************************************************
 * ��������glcd_set_window()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width �������㣬��͸�
 * ���  ��void
 * ����  ������ĳ���ض����������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_set_window(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  /*����ˮƽ����X��ʼ����*/
  glcd_index = ((unsigned long*)FRAME_BUFFER) + Xpos + (Ypos*LCD_XSIZE);
  // WindX_Size = Width;
  // WindY_Size = Height;
  // CurrX_Size = CurrY_Size = 0;
}
/**************************************************************************************************************
 * ��������glcd_set_colors()
 * ����  ��_TextColor ǰ��ɫ,_BackColor ����ɫ
 * ���  ��void
 * ����  ������LCD��ǰ��ɫ�ͱ���ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_set_colors(uint32_t _TextColor,uint32_t _BackColor)
{
  TextColor = _TextColor; 
  BackColor = _BackColor;
}
/**************************************************************************************************************
 * ��������glcd_get_colors()
 * ����  ��*_TextColor ǰ��ɫ��ָ��,*_BackColor ����ɫ��ָ��
 * ���  ��void
 * ����  ����ȡLCD��ǰ��ɫ�ͱ���ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_get_colors(uint32_t *_TextColor,uint32_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}
/**************************************************************************************************************
 * ��������glcd_set_textcolor()
 * ����  ��uint16_t Color ǰ��ɫ
 * ���  ��void
 * ����  ������LCD��ǰ��ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_set_textcolor(uint32_t Color)
{
  TextColor = Color;
}


/**************************************************************************************************************
 * ��������glcd_set_backcolor()
 * ����  ��uint16_t Color ����ɫ
 * ���  ��void
 * ����  ������LCD�ı���ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_set_backcolor(uint32_t Color)
{
  BackColor = Color;
}
/**************************************************************************************************************
 * ��������glcd_set_font()
 * ����  ��sFONT *fonts Ҫ���õ�����
 * ���  ��void
 * ����  ������LCD������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_set_font(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}
/**************************************************************************************************************
 * ��������glcd_get_font()
 * ����  ��void
 * ���  ��sFONT * ��ȡ����
 * ����  ������LCD������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
sFONT* glcd_get_font(void)
{
  return LCD_Currentfonts;
}
/**************************************************************************************************************
 * ��������glcd_draw_hline()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Length ���X��Y���꼰����
 * ���  ��void
 * ����  ����ˮƽ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_hline(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
   glcd_set_cursor(Xpos, Ypos);
    for(i = 0; i < Length; i++)
    {
      *glcd_index=TextColor;
	  glcd_index++;
    }
}
/**************************************************************************************************************
 * ��������glcd_draw_vline()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Length ���X��Y���꼰����
 * ���  ��void
 * ����  ������ֱ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_vline(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
    for(i = 0; i < Length; i++)
    { 
	  glcd_set_cursor(Xpos, Ypos);
      *glcd_index=TextColor;
      Ypos++; 
    }
}
/**************************************************************************************************************
 * ��������glcd_draw_rect()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height �������Ͻǵ�����꼰��͸�
 * ���  ��void
 * ����  �������κ���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_rect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  glcd_draw_hline(Xpos, Ypos, Width);
  glcd_draw_hline(Xpos, Ypos+ Height, Width); 
  glcd_draw_vline(Xpos, Ypos, Height);
  glcd_draw_vline(Xpos+ Width,Ypos, Height);
}
/**************************************************************************************************************
 * ��������glcd_draw_circle()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Radius Բ������㼰�뾶
 * ���  ��void
 * ����  ����Բ����
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    glcd_set_cursor(Xpos + CurX, Ypos + CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos + CurX, Ypos - CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurX, Ypos + CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurX, Ypos - CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos + CurY, Ypos + CurX);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos + CurY, Ypos - CurX);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurY, Ypos + CurX);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurY, Ypos - CurX);
    *glcd_index=TextColor;
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}
/**************************************************************************************************************
 * ��������glcd_draw_monobmp()
 * ����  ��const uint32_t *Pict ��һ��ȫ����ɫ��ȡĤ����
 * ���  ��void
 * ����  ����һ����ɫ��ȫ��ͼƬ����
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_monobmp(const uint32_t *Pict)
{
  uint32_t index = 0, i = 0;
  glcd_set_cursor(0, 0); 
  for(index = 0; index < (LCD_XSIZE*LCD_YSIZE)/32; index++)
  {
    for(i = 0; i < 32; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        *glcd_index++=BackColor;
      }
      else
      {
        *glcd_index++=TextColor;
      }
    }
  }
}
/**************************************************************************************************************
 * ��������glcd_fill_rect()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height ���������Ͻǵ㡢��͸�
 * ���  ��void
 * ����  ����һ�����ľ���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_fill_rect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{ 
	uint32_t tempcolor;
  glcd_set_textcolor(TextColor);
  glcd_draw_hline(Xpos, Ypos, Width);
  glcd_draw_hline(Xpos, Ypos+ Height, Width);
  
  glcd_draw_vline(Xpos, Ypos, Height);
  glcd_draw_vline(Xpos+Width, Ypos, Height);

  Width --;
  Height--;
  Xpos++;
  tempcolor=TextColor;
  glcd_set_textcolor(BackColor);

  while(Height--)
  {
    glcd_draw_hline(Xpos, ++Ypos, Width);    
  }

  glcd_set_textcolor(tempcolor);
}
/**************************************************************************************************************
 * ��������glcd_fill_circle()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Radius ���Բ��Բ�ĺͰ뾶
 * ���  ��void
 * ����  ����һ�����Բ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_fill_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  uint32_t tempcolor;
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  tempcolor=TextColor;
  glcd_set_textcolor(BackColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      glcd_draw_hline(Xpos - CurY, Ypos - CurX, 2*CurY);
      glcd_draw_hline(Xpos - CurY, Ypos + CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      glcd_draw_hline(Xpos - CurX, Ypos -CurY, 2*CurX);
      glcd_draw_hline(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  glcd_set_textcolor(tempcolor);
  glcd_draw_circle(Xpos, Ypos, Radius);
}
/**************************************************************************************************************
 * ��������glcd_draw_uniline()
 * ����  ��uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ��ʼ��������յ�����
 * ���  ��void
 * ����  �������ⷽ���ֱ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_uniline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    glcd_draw_pixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}
/**************************************************************************************************************
 * ��������glcd_draw_pixel()
 * ����  ��int16_t x, int16_t y  �������
 * ���  ��void
 * ����  ����һ�����ص�
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_pixel(uint16_t x, uint16_t y)
{ 
  if( x > LCD_XSIZE ||  y > LCD_YSIZE)
  {
    return;  
  }
  glcd_draw_hline(x, y, 1);
}
/**************************************************************************************************************
 * ��������glcd_draw_char()
 * ����  ��const uint16_t *c   �ַ�����
 * ���  ��void
 * ����  ��LCD��һ���ַ�
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_char(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, i = 0;
  uint16_t  x = 0,y=0;
  y = Ypos;
  
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  { 
	 x=Xpos;
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
  
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))

      {
				glcd_set_cursor(x++,y);
				*glcd_index=BackColor;
      }
      else
      {
        glcd_set_cursor(x++,y);
				*glcd_index=TextColor;
      } 
    }
    y++;
   
  }

}
/**************************************************************************************************************
 * ��������glcd_display_char()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint8_t Ascii ��ʾ��λ�ú��ַ�
 * ���  ��void
 * ����  ��LCD��ʾһ���ַ�
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_display_char(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  Ascii -= 32;
  glcd_draw_char(Xpos, Ypos, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}
/**************************************************************************************************************
 * ��������glcd_draw_string()
 * ����  ��u16 xpos, u16 ypos, u8 *ptr ��ʾ��λ�ú��ַ���
 * ���  ��void
 * ����  ��LCD��ʾһ���ַ�
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void glcd_draw_string(uint16_t xpos, uint16_t ypos, uint8_t *ptr)
{
  	uint16_t refypos=xpos;
  	while(*ptr!=0)
  	{
    	glcd_display_char(refypos,ypos,*ptr);
    	refypos+=LCD_Currentfonts->Width;
    	ptr++;
  	}
}

//m^n����
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}			 
/**************************************************************************************************************
 * ��������glcd_draw_num()
 * ����  ��u16 x, u16 y, s32 num, u8 len   ��ʾ��λ�ã����ּ�����
 * ���  ��void
 * ����  ��LCD��ʾһ������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/	 
void glcd_draw_num(uint16_t x, uint16_t y, int32_t num, uint8_t len)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	t=0;
	if(num<0)
	{
		glcd_display_char(x+(LCD_Currentfonts->Width)*t,y,'-');
		num=-num;
		t++;
	}						   
	for(;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				glcd_display_char(x+(LCD_Currentfonts->Width)*t,y,' ');
				continue;
			}else enshow=1; 		 	 
		}
	 	glcd_display_char(x+(LCD_Currentfonts->Width)*t,y,temp+'0'); 
	}
} 


/**************************************************************************************************************
 * ��������glcd_clear_aera()
 * ����  ��uint16_t x,uint16_t y,uint16_t w,uint16_t h   �����λ�ã����ȺͿ��
 * ���  ��void
 * ����  ��LCD���ĳ������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/	
void glcd_clear_aera(uint16_t x,uint16_t y,uint16_t w,uint16_t h)
{
	uint32_t tempcolor;
  tempcolor=TextColor;
  glcd_set_textcolor(BackColor);
  while(h--)
  {
    glcd_draw_hline(x, y++, w);    
  }
  glcd_set_textcolor(tempcolor);
}
void glcd_debug(char* fmt, ...)
{  
	 static uint16_t debug_x=0,debug_y=0;
    char* pArg= (void*)0;//�ȼ���ԭ����va_list
    char c;
	  char buf[64];
    pArg = (char*) &fmt;//ע�ⲻҪд�� p=fmt !! ��Ϊ����Ҫ�Բ���ȡַ��������ȡֵ
    pArg += sizeof(fmt);//�ȼ���ԭ����va_start        
    TextColor = 0xFFFFFF; BackColor = 0x000000;
    do
    {
        c =*fmt;
        if (c != '%')
        {   
					  if(c=='\r')
							{
               debug_y+=12;
              }
						 else	if(c=='\n')
						{
							debug_x=0;
							debug_y+=12;
							if(debug_y>(LCD_YSIZE-12))
									{
                   glcd_clear(BLACK);
										debug_x=0;
                    debug_y=0;
                  }
            }else {
            glcd_display_char(debug_x,debug_y,c);//��ԭ������ַ�
					  debug_x+=8;
					  if(debug_x>(LCD_XSIZE-8))
							{
								debug_x=0;
               debug_y+=12;
								if(debug_y>(LCD_YSIZE-12))
									{
                   glcd_clear(BLACK);
										debug_x=0;
                    debug_y=0;
                  }
              }
						}
							
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
           glcd_draw_string(debug_x,debug_y,(uint8_t *)buf);
					 debug_x+=strlen(buf)*8;
        }
        ++fmt;
    }while (*fmt != '\0');
    pArg = (void*)0; //�ȼ���va_end
    return;
}
