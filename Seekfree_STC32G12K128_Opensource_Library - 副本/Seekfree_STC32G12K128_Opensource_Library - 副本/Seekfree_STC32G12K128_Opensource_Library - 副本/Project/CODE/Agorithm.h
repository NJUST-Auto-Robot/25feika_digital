



typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //�����޷�

    float                out_p;  //KP���
    float                out_i;  //KI���
    float                out_d;  //KD���
    float                out;    //pid���

    float                integrator; //< ����ֵ
    float                last_error; //< �ϴ����
    float                last_derivative;//< �ϴ���������ϴ����֮��
    unsigned long        last_t;     //< �ϴ�ʱ��
}pid_param_t;

extern int32 TIM_0_flag;
extern int32 TIM_1_flag;

extern pid_param_t Nomal_PID;
extern pid_param_t DJr_PID;
extern pid_param_t DJl_PID;
extern pid_param_t CS_PID;
extern int16 L_OUT,R_OUT;

float constrain_float(float amt, float low, float high);
float PidLocCtrl(pid_param_t * pid, float error);
float PidIncCtrl_L(pid_param_t * pid, float error);
float PidIncCtrl_R(pid_param_t * pid, float error);



