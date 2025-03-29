/*********************************************************************************************************************
 * @author     		Niko
 * @Target core		STC32G12K128
 * @date       		2025-3-6
 * @brief           此库只负责ADC初始化、数据读取以及数据处理，后续控制请参考BD_ctrl
 * @Last editor     Niko
 ********************************************************************************************************************/
#include "headfile.h"
#include "ADC.h"
adc_state dg_state;
uint32 temp=100;
int temp_r11;
int temp_r12;
int temp_r13;
int temp_r21;
int temp_l11;
int temp_l12;
int temp_l13;
int temp_l21;
/************************************************
函数名：Nadc_init
功  能：一键式初始化adc引脚,默认adc时钟频率为sysclk/2
参  数：void
返回值：void
************************************************/
void Nadc_init(void){
    adc_init(ADC_P10,ADC_SYSclk_DIV_2);
    adc_init(ADC_P11,ADC_SYSclk_DIV_2);
    // adc_init(ADC_P12,ADC_SYSclk_DIV_2);
    adc_init(ADC_P13,ADC_SYSclk_DIV_2);
    adc_init(ADC_P14,ADC_SYSclk_DIV_2);
    adc_init(ADC_P15,ADC_SYSclk_DIV_2);
    adc_init(ADC_P16,ADC_SYSclk_DIV_2);
    adc_init(ADC_P17,ADC_SYSclk_DIV_2);
	//IO口需要设置为高阻输入
	ADC_CONTR &= (0xF0);			//清除ADC_CHS[3:0] ： ADC 模拟通道选择位
	ADC_CONTR |= ADC_P12;
	P5M0 &= ~(1 << (4 & 0x07));
	P5M1 |= (1 << (4 & 0x07));	
}
/************************************************
函数名：Nadc_mean_filter_remove_max_min
功  能：adc均值滤波去除最大值和最小值
参  数：adcn 选择adc通道;count 采集次数;resolution 分辨率
返回值：adc_value 去除最大值和最小值之后的adc均值
************************************************/
uint32 Nadc_mean_filter_remove_max_min(ADCN_enum adcn, uint8 count,ADCRES_enum resolution)
{
	uint8 i;
	uint32 adc_value = 0;
	uint32 max = 0,min = 0;
	uint32 dat = 0;
	for (i = 0;i < count + 2;i++)
	{
		dat = adc_once(adcn,resolution);//使用变量dat读取一次ADC即可，避免多次读取ADC
		min = dat;
		max = dat;
		adc_value += dat;
		if(max < dat)
			max = dat;
		if(min > dat)
			min = dat;
	}
	adc_value = (adc_value - max - min)/ count;
	return adc_value;
}
/************************************************
函数名：Nadc_getmax
功  能：adc读取最大值，以便后面归一化处理
参  数：adcn 选择adc通道;count 采集次数;resolution 分辨率
返回值：max adc读取到的最大值
************************************************/
uint32 Nadc_getmax(ADCN_enum adcn, uint8 count,ADCRES_enum resolution)
{
	uint8 i;
	uint32 max;
	uint32 dat;
	for (i = 0;i < count + 2;i++)
	{
		dat = adc_once(adcn,resolution);//使用变量dat读取一次ADC即可，避免多次读取ADC
		if(max < dat)
			max = dat;
    }
    return max+1;
}
/************************************************
函数名：Nget_ADC_values_mean_filter
功  能：用均值滤波法一键读取所有所需电感值，adc分辨率默认12bit
参  数：void
返回值：void
************************************************/
void Nget_ADC_values_mean_filter(void){
    dg_state.L_r11_real=Nadc_mean_filter_remove_max_min(ADC_P10,10,ADC_12BIT);
    dg_state.L_r12_real=Nadc_mean_filter_remove_max_min(ADC_P15,10,ADC_12BIT);
    dg_state.L_r13_real=Nadc_mean_filter_remove_max_min(ADC_P14,10,ADC_12BIT);
    dg_state.L_r21_real=Nadc_mean_filter_remove_max_min(ADC_P11,10,ADC_12BIT);
    dg_state.L_l12_real=Nadc_mean_filter_remove_max_min(ADC_P16,10,ADC_12BIT);
    dg_state.L_l11_real=Nadc_mean_filter_remove_max_min(ADC_P12,10,ADC_12BIT);
    dg_state.L_l21_real=Nadc_mean_filter_remove_max_min(ADC_P13,10,ADC_12BIT);
    dg_state.L_l13_real=Nadc_mean_filter_remove_max_min(ADC_P17,10,ADC_12BIT);
}
/************************************************
函数名：Nadc_normalization_max
功  能：读取场地最大电感值以便后续归一化
参  数：void
返回值：void
************************************************/
void Nadc_normalization_max(void){
	dg_state.L_r13_max=adc_once(ADC_P14,ADC_12BIT);
	dg_state.L_l11_max=dg_state.L_r13_max;
    dg_state.L_l12_max=dg_state.L_r13_max;
    dg_state.L_l21_max=dg_state.L_r13_max;
    dg_state.L_r11_max=dg_state.L_r13_max;
    dg_state.L_r12_max=dg_state.L_r13_max;
    dg_state.L_l13_max=dg_state.L_r13_max;
    dg_state.L_r21_max=dg_state.L_r13_max;
}
/************************************************
函数名：Nadc_normalization_once
功  能：将所得电感值进行第一次归一化
参  数：void
返回值：void
************************************************/
void Nadc_normalization_once(void){
    Nget_ADC_values_mean_filter();
    dg_state.L_l11_once = (dg_state.L_l11_real * temp) / dg_state.L_l11_max;
	dg_state.L_l12_once = (dg_state.L_l12_real * temp) / dg_state.L_l12_max;
	dg_state.L_l13_once = (dg_state.L_l13_real * temp) / dg_state.L_l13_max;
	dg_state.L_l21_once = (dg_state.L_l21_real * temp) / dg_state.L_l21_max;
	dg_state.L_r11_once = (dg_state.L_r11_real * temp) / dg_state.L_r11_max;
	dg_state.L_r12_once = (dg_state.L_r12_real * temp) / dg_state.L_r12_max;
	dg_state.L_r13_once = (dg_state.L_r13_real * temp) / dg_state.L_r13_max;
	dg_state.L_r21_once = (dg_state.L_r21_real * temp) / dg_state.L_r21_max;

	dg_state.L_l11_once = constrain_float(dg_state.L_l11_once,0,210);//限幅0-100
	dg_state.L_l12_once = constrain_float(dg_state.L_l12_once,0,210);//限幅0-100
	dg_state.L_l13_once = constrain_float(dg_state.L_l13_once,0,210);//限幅0-100
	dg_state.L_l21_once = constrain_float(dg_state.L_l21_once,0,210);//限幅0-100
	dg_state.L_r11_once = constrain_float(dg_state.L_r11_once,0,210);//限幅0-100
	dg_state.L_r12_once = constrain_float(dg_state.L_r12_once,0,210);//限幅0-100
	dg_state.L_r13_once = constrain_float(dg_state.L_r13_once,0,210);//限幅0-100
    dg_state.L_r21_once = constrain_float(dg_state.L_r21_once,0,210);//限幅0-100
}


























































































































































