/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"
#include <action.h>



/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 */

void main()
{
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
	
	// �˴���д�û�����(���磺�����ʼ�������)
    pit_timer_ms(TIM_4, 5);
    Dir_encoder_init();
    DRV8701_init();
    delay_init();
    Nadc_init();
    while(1)
	{   Nelement_recogniz();
        printf("%d,%d,%d,%d\n",dg_state.L_l11_once,dg_state.L_l12_once,dg_state.L_l13_once,dg_state.L_l21_once);
        printf("%d,%d,%d,%d\n",dg_state.L_r11_once,dg_state.L_r12_once,dg_state.L_r13_once,dg_state.L_r21_once);
        printf("%d\n",flag);
        delay_ms(200);
		 // �˴���д��Ҫѭ��ִ�еĴ���

    }
}

