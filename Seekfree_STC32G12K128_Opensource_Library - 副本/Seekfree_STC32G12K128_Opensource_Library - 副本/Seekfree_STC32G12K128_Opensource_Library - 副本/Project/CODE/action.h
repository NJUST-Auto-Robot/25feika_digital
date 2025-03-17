//�ṹ������
typedef struct{
    float Xdata;   //��Ʈ����X
    float Ydata;   //��Ʈ����Y
    float Zdata;   //��Ʈ����Z
}gyro_param_t ;//�ṹ������

typedef struct{
    float acc_x;   //x����ٶ�
    float acc_y;   //y����ٶ�
    float acc_z;   //z����ٶ�

    float gyro_x;  //x����ٶ�
    float gyro_y;  //y����ٶ�
    float gyro_z;  //z����ٶ�
}IMU_param_t; 


extern int IMU_1_Open_flag;
extern float Yaw_1;

void IMU_init(void);
void IMU_gyro_Offset_Init(void);
void IMU_GetValues(void);
void IMU_Handle_180(void);
void IMU_data_get(void);
void IMU_text(void);


