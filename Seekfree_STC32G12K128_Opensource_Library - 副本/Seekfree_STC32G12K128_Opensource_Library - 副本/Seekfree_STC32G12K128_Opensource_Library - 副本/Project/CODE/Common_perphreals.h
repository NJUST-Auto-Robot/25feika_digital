

//定义脉冲引脚
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04
//定义方向引脚
#define SPEEDL_DIR     P35
#define SPEEDR_DIR     P53

//定义DRV8701引脚
#define DIR_1 P64
#define DIR_2 P60
#define PWM_1 PWMA_CH4P_P66
#define PWM_2 PWMA_CH2P_P62

extern int16 templ_pluse;
extern int16 tempr_pluse;


void Encoder_init(void);
void Dir_encoder_get(void);

void DRV8701_init(void);
void DRV8701_ctrl(int32 L_speed,int32 R_speed);
void DRV8701_loop_ctrl(float L_speed,float R_speed);