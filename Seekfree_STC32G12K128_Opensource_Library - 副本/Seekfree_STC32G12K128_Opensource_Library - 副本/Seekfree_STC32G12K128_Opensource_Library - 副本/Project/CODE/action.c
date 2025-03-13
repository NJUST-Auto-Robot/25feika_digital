#include "headfile.h"

gyro_param_t Gyro_Offset;
IMU_param_t  IMU_Data;

int IMU_1_Open_flag = 0;//����IMU��־λ

float Yaw_1 = 0;
float Roll_1 = 0;
float Picth_1 = 0;

void IMU_init(void)//IMU��ʼ��
{
    imu660ra_init();   //IMU660�ߵ���ʼ��

    IMU_gyro_Offset_Init();// ��������Ư��ʼ��
}

uint16 i;
void IMU_gyro_Offset_Init(void)
{
    Gyro_Offset.Xdata = 0;
    Gyro_Offset.Ydata = 0;
    Gyro_Offset.Zdata = 0;

		 
    for (i = 0; i < 1000; i++)
    {
        Gyro_Offset.Xdata += imu660ra_gyro_x;
        Gyro_Offset.Ydata += imu660ra_gyro_y;
        Gyro_Offset.Zdata += imu660ra_gyro_z;
        delay_ms(5);   // ��� 1Khz
    }

    Gyro_Offset.Xdata /= 1000;
    Gyro_Offset.Ydata /= 1000;
    Gyro_Offset.Zdata /= 1000;
}

void IMU_GetValues(void)//���ɼ�����ֵת��Ϊʵ������ֵ, ���������ǽ���ȥ��Ư����
{
    IMU_Data.gyro_x = ((float) imu660ra_gyro_x - Gyro_Offset.Xdata)* PI / 180/ 16.384f;
    IMU_Data.gyro_y = ((float) imu660ra_gyro_y - Gyro_Offset.Ydata)* PI / 180/ 16.384f;
    IMU_Data.gyro_z = ((float) imu660ra_gyro_z - Gyro_Offset.Zdata)* PI / 180/ 16.384f;

    if(IMU_Data.gyro_z<0.015&&IMU_Data.gyro_z>-0.015)//�˲�
    {
        Yaw_1-=0;
    }
    else
    {
        IMU_Handle_180();
     }

}

void IMU_Handle_180(void)
{

    Yaw_1-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(���ֹ���)��������ʱ��Ϊ��,���ڸ�Ϊ˳ʱ��Ϊ��

   if(Yaw_1>180 && Yaw_1<=360)
    {
        Yaw_1-=360;
    }
    else if(Yaw_1<(-180) && Yaw_1>=(-360))
    {
        Yaw_1+=360;
    }

}

void IMU_data_get(void)
{
    imu660ra_get_gyro();

    if(IMU_1_Open_flag==1)
    {
        IMU_GetValues();
    }
}

void IMU_text(void)
{
    IMU_1_Open_flag=1;
//    while(1)
//    {
//        ips200_show_string(8*0, 16*0, "Yaw:");      ips200_show_float(8*5,16*0,Yaw_1,3,6);
//    }
}