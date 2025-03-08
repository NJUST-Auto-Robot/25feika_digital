#include "headfile.h"
//===================================================�����������===================================================

void Dir_encoder_init(void)
{
	ctimer_count_init(SPEEDL_PLUSE);	//��ʼ����ʱ��0��Ϊ�ⲿ����
	ctimer_count_init(SPEEDR_PLUSE);	//��ʼ����ʱ��3��Ϊ�ⲿ����

}

int16 templ_pluse = 0;
int16 tempr_pluse = 0;

void Dir_encoder_get(void)
{
		//��ȡ�ɼ����ı�����������
		templ_pluse = ctimer_count_read(SPEEDL_PLUSE);
		tempr_pluse = ctimer_count_read(SPEEDR_PLUSE);

		//����������
		ctimer_count_clean(SPEEDL_PLUSE);
		ctimer_count_clean(SPEEDR_PLUSE);
	
		//�ɼ�������Ϣ
		if(1 == SPEEDL_DIR)    
        {
            templ_pluse = -templ_pluse;
        }

		if(1 == SPEEDR_DIR)    
        {
            tempr_pluse = -tempr_pluse;
        }
}


//===================================================�����������===================================================

//===================================================DRV8701===================================================

void DRV8701_init(void)
{
	pwm_init(PWM_1, 17000, 0); 	//��ʼ��PWM1  ʹ��P60����  ��ʼ��Ƶ��Ϊ17Khz
	pwm_init(PWM_2, 17000, 0); 	//��ʼ��PWM2  ʹ��P62����  ��ʼ��Ƶ��Ϊ17Khz
	
	gpio_mode(P6_4, GPO_PP);	// P64��������Ϊ�������
	gpio_mode(P6_0, GPO_PP);	// P60��������Ϊ�������

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
