#include "headfile.h"

int32 TIM_0_flag=0;
int32 TIM_1_flag=0;

pid_param_t Nomal_PID;//位置式PID
pid_param_t DJ_PID;//增量式PID
pid_param_t CS_PID;//差速



/************************************************
函数名：constrain_float
功  能：限幅函数，将输入值限制在指定范围内
参  数：float amt, float low, float high
返回值：float 限幅后的值
************************************************/
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}


/************************************************
函数名：PidLocCtrl
功  能：位置式PID控制
参  数：pid_param_t * pid, float error
返回值：float 控制输出
************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{

    Nomal_PID.kp=1.1;
    Nomal_PID.kd=5;

    CS_PID.kp=1;
    CS_PID.kd=0;

    /* 累积误差 */
    pid->integrator += error;

    /* 误差限幅 */
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
函数名：PidIncCtrl_L
功  能：增量式PID控制左
参  数：&DJ_PID, L_speed-templ_pluse 期待速度-当前速度
返回值：float 控制输出
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
函数名：PidIncCtrl_R
功  能：增量式PID控制右
参  数：&DJ_PID, R_speed-tempr_pluse 期待速度-当前速度
返回值：float 控制输出
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
 函数名：DRV8701_loop_ctrl
 功 能：驱动DRV8701电机控制器的闭环控制
 参 数：左期望速度, 右期望速度
 返回值：无
************************************************/
void DRV8701_loop_ctrl(float L_speed,float R_speed)//填入期望速度
{
	L_OUT=PidIncCtrl_L(&DJ_PID,L_speed-templ_pluse);
	R_OUT=PidIncCtrl_R(&DJ_PID,R_speed-tempr_pluse);

	DRV8701_ctrl(L_OUT,R_OUT);
}