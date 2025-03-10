/*********************************************************************************************************************
 * @author     		Niko
 * @Target core		STC32G12K128
 * @date       		2025-3-6
 * @brief           此库为元素识别库，后续控制在主函数中进行
 * @Last editor     Niko
 ********************************************************************************************************************/

#include "headfile.h"
#include "BD_ctrl.h"

typedef enum __mode
{
    _MODE_NONE = 0,
    STRIAGHT,
    Roundabout,
} Track_MODE_enum;

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
    if (-2 < dg_state.L_r13_once < 2 && -2 < stra < 2)
    {
        flag = STRIAGHT;
    }
}
