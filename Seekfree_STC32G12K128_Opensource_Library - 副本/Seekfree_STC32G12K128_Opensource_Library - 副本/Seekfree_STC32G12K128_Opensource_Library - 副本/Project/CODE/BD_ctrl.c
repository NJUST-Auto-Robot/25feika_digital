/*********************************************************************************************************************
 * @author     		Niko
 * @Target core		STC32G12K128
 * @date       		2025-3-6
 * @brief           此库为元素识别库，后续控制在主函数中进行
 * @Last editor     Niko
 ********************************************************************************************************************/

#include "headfile.h"
#include "BD_ctrl.h"


int flag = 0;
/************************************************
 函数名：Nelement_recogniz
 功 能：元素识别函数
 参 数：void
 返回值：void
************************************************/
void Nelement_recogniz(void)
{
    Nadc_normalization_once();
    int error_11 = dg_state.L_l11_once - dg_state.L_r11_once;
    int error_21 = dg_state.L_l21_once - dg_state.L_r21_once;
    int error_12 = dg_state.L_l12_once - dg_state.L_r12_once;
    /*以下为直线识别部分*/
    int stra = error_11 + error_12 + error_21;
    int stra = stra / 3;
    if (0 < dg_state.L_r13_once < 2 && 0 < stra < 2)
    {
        flag = STRIAGHT;
    }
    /*以下为十字路口识别部分*/
    if (90<dg_state.L_r13_once<100&&90<dg_state.L_l13_once<100&&-2 <error_11 < 2 && -2 <error_12 < 2&&-2 <error_21 < 2)
    {
        flag = Crossroads;
    }
    /*以下为直角弯道识别部分*/
    if ( dg_state.L_l13_once >85&& dg_state.L_r13_once > 85)
    {
        if (error_11 > 90 && error_21 > 90 && error_12 > 80)
        {
            flag = TurnLeft;
        }
        else if (error_11 <-90 && error_21 <-90 && error_12 <-80)
        {
            flag = TurnRight;
        }
        
}
/*以下为锐角弯道识别部分*/
    if ( 5<dg_state.L_l13_once <90&& dg_state.L_r13_once > 90)
    {
    if (5<error_11 < 90 && 5<error_21 < 90 && 5<error_12 <80)
    {
        flag = AngleLeft;
    }
    else  if (-90<error_11 < -5 && -90<error_21 < -5 && -80<error_12 <-5)
    {
        flag = AngleRight;
    }
}

/*以下为环岛识别部分*/
if (dg_state.L_r13_once > 180 && dg_state.L_l13_once > 50&&)//接近环岛出入点
{
int temp_r11 = dg_state.L_r11_once;
int temp_r12 = dg_state.L_r12_once;
int temp_r21 = dg_state.L_r21_once;
int temp_l11 = dg_state.L_l11_once;
int temp_l12 = dg_state.L_l12_once;
int temp_l21 = dg_state.L_l21_once;
Nadc_normalization_once();
//进入环岛
if (temp_l11-=dg_state.l11_once>30&&temp_l12-=dg_state.l12_once>20&&temp_l21-=dg_state.l21_once>10)
{
    flag = InRoundaboutL;
}
if (temp_r11-=dg_state.r11_once>30&&temp_r12-=dg_state.r12_once>20&&temp_r21-=dg_state.r21_once>10)
{
    flag = InRoundaboutR;
}
//离开环岛
// if (temp_l11-=dg_state.l11_once<-30&&temp_l12-=dg_state.l12_once<-20&&temp_l21-=dg_state.l21_once<-10)
// {
//     flag = OutRoundaboutL;
// }
// if (temp_r11-=dg_state.r11_once<-30&&temp_r12-=dg_state.r12_once<-20&&temp_r21-=dg_state.r21_once<-10)
// {
//     flag = OutRoundaboutR;
}
}



