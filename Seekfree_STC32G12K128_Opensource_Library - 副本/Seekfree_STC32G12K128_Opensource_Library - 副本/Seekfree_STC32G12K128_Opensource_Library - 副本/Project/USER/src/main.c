/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"
#include <action.h>



/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 */

void main()
{
	board_init();			// 初始化寄存器,勿删除此句代码。
	
	// 此处编写用户代码(例如：外设初始化代码等)
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
		 // 此处编写需要循环执行的代码

    }
}

