#include "headfile.h"
//===================================================带方向编码器===================================================

void Dir_encoder_init(void)
{
	ctimer_count_init(SPEEDL_PLUSE);	//初始化定时器0作为外部计数
	ctimer_count_init(SPEEDR_PLUSE);	//初始化定时器3作为外部计数

}

int16 templ_pluse = 0;
int16 tempr_pluse = 0;

void Dir_encoder_get(void)
{
		//读取采集到的编码器脉冲数
		templ_pluse = ctimer_count_read(SPEEDL_PLUSE);
		tempr_pluse = ctimer_count_read(SPEEDR_PLUSE);

		//计数器清零
		ctimer_count_clean(SPEEDL_PLUSE);
		ctimer_count_clean(SPEEDR_PLUSE);
	
		//采集方向信息
		if(1 == SPEEDL_DIR)    
        {
            templ_pluse = -templ_pluse;
        }

		if(1 == SPEEDR_DIR)    
        {
            tempr_pluse = -tempr_pluse;
        }
}


//===================================================带方向编码器===================================================

//===================================================DRV8701===================================================

void DRV8701_init(void)
{
	pwm_init(PWM_1, 17000, 0); 	//初始化PWM1  使用P60引脚  初始化频率为17Khz
	pwm_init(PWM_2, 17000, 0); 	//初始化PWM2  使用P62引脚  初始化频率为17Khz
	
	gpio_mode(P6_4, GPO_PP);	// P64引脚设置为推挽输出
	gpio_mode(P6_0, GPO_PP);	// P60引脚设置为推挽输出

}

void DRV8701_ctrl(int32 L_speed,int32 R_speed)
{
	constrain_float(L_speed,8000,-8000);
	constrain_float(R_speed,8000,-8000);
	if(L_speed>=0)
	{
			DIR_1 = 0;
			pwm_duty(PWM_1, L_speed);
	}
	else
	{
			DIR_1 = 1;
			pwm_duty(PWM_1, -L_speed);
	
	}
	
	if(R_speed>=0)
	{
			DIR_2 = 0;
			pwm_duty(PWM_2, R_speed);
	}
	else
	{
			DIR_2 = 1;
			pwm_duty(PWM_2, -R_speed);
	
	}

}

//===================================================DRV8701===================================================
