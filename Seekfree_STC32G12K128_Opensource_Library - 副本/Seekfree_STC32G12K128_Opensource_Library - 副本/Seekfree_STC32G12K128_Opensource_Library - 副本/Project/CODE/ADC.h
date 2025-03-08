/*********************************************************************************************************************
 * @author     		Niko
 * @Target core		STC32G12K128
 * @date       		2025-3-6
 * @brief           此库只负责ADC初始化、数据读取以及数据处理，后续控制请参考BD_ctrl
 * @Last editor     Niko
 ********************************************************************************************************************/
#ifndef _ADC_H
#define _ADC_H
#include <common.h>
typedef struct 
{
	uint16 L_l11_real; //左11电感实际值
    uint16 L_l12_real; //左12电感实际值
    uint16 L_l13_real; //左13电感实际值
	uint16 L_l21_real; //左21电感实际值
    uint16 L_r11_real; //右11电感实际值
    uint16 L_r12_real; //右12电感实际值
    uint16 L_r13_real; //右13电感实际值
    uint16 L_r21_real; //右21电感实际值
 
	uint16 L_l11_max; //左11电感最大值
    uint16 L_l12_max; //左12电感最大值
    uint16 L_l13_max; //左13电感最大值
	uint16 L_l21_max; //左21电感最大值
    uint16 L_r11_max; //右11电感最大值
    uint16 L_r12_max; //右12电感最大值
    uint16 L_r13_max; //右13电感最大值
    uint16 L_r21_max; //右21电感最大值
 
	float L_l11_once; //左11电感一次归一化后
    float L_l12_once; //左12电感一次归一化后
    float L_l13_once; //左13电感一次归一化后
	float L_l21_once; //左21电感一次归一化后
    float L_r11_once; //右11电感一次归一化后
    float L_r12_once; //右12电感一次归一化后
    float L_r13_once; //右13电感一次归一化后
    float L_r21_once; //右21电感一次归一化后

	float L_l11_twice; //左11电感二次归一化后
    float L_l12_twice; //左12电感二次归一化后
    float L_l13_twice; //左13电感二次归一化后
	float L_l21_twice; //左21电感二次归一化后
    float L_r11_twice; //右11电感二次归一化后
    float L_r12_twice; //右12电感二次归一化后
    float L_r13_twice; //右13电感二次归一化后
    float L_r21_twice; //右21电感二次归一化后

}adc_state;	
extern adc_state dg_state;
extern uint16  m;
void Nadc_init(void);
uint16 Nadc_mean_filter_remove_max_min(ADCN_enum adcn, uint8 count,ADCRES_enum resolution);
uint16 Nadc_getmax(ADCN_enum adcn, uint8 count,ADCRES_enum resolution);
#endif

