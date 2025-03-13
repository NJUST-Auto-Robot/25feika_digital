#include "headfile.h"

int32 TIM_0_flag=0;
int32 TIM_1_flag=0;

pid_param_t Nomal_PID;//λ��ʽPID
pid_param_t DJ_PID;//����ʽPID
pid_param_t CS_PID;//����



/************************************************
��������constrain_float
��  �ܣ��޷�������������ֵ������ָ����Χ��
��  ����float amt, float low, float high
����ֵ��float �޷����ֵ
************************************************/
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}


/************************************************
��������PidLocCtrl
��  �ܣ�λ��ʽPID����
��  ����pid_param_t * pid, float error
����ֵ��float �������
************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{

    Nomal_PID.kp=1.1;
    Nomal_PID.kd=5;

    CS_PID.kp=1;
    CS_PID.kd=0;

    /* �ۻ���� */
    pid->integrator += error;

    /* ����޷� */
    constrain_float(pid->integrator, -pid->imax, pid->imax);


    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * pid->integrator;
    pid->out_d = pid->kd * (error - pid->last_error);

    pid->last_error = error;

    pid->out = pid->out_p + pid->out_i + pid->out_d;

//    if(pid->out>SERVO_MOTOR_LMAX)
//    {pid->out=SERVO_MOTOR_LMAX;}
//    if(pid->out<SERVO_MOTOR_RMIN)
//    {pid->out=SERVO_MOTOR_RMIN;}
    return pid->out;
//    printf("OUT:%d\n",pid->out);
}

/************************************************
��������PidIncCtrl_L
��  �ܣ�����ʽPID������
��  ����&DJ_PID, L_speed-templ_pluse �ڴ��ٶ�-��ǰ�ٶ�
����ֵ��float �������
************************************************/
float PidIncCtrl_L(pid_param_t * pid, float error)
{
    DJ_PID.kp=110;
    DJ_PID.ki=6;
    DJ_PID.kd=5;



    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;
    return pid->out;
}

/************************************************
��������PidIncCtrl_R
��  �ܣ�����ʽPID������
��  ����&DJ_PID, R_speed-tempr_pluse �ڴ��ٶ�-��ǰ�ٶ�
����ֵ��float �������
************************************************/
float PidIncCtrl_R(pid_param_t * pid, float error)
{
    DJ_PID.kp=110;
    DJ_PID.ki=6;
    DJ_PID.kd=5;



    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;
    return pid->out;
}

/************************************************
 ��������DRV8701_loop_ctrl
 �� �ܣ�����DRV8701����������ıջ�����
 �� �����������ٶ�, �������ٶ�
 ����ֵ����
************************************************/
void DRV8701_loop_ctrl(float L_speed,float R_speed)//���������ٶ�
{
	L_OUT=PidIncCtrl_L(&DJ_PID,L_speed-templ_pluse);
	R_OUT=PidIncCtrl_R(&DJ_PID,R_speed-tempr_pluse);

	DRV8701_ctrl(L_OUT,R_OUT);
}