/*********************************************************************************************************************
 * @author     		Niko
 * @Target core		STC32G12K128
 * @date       		2025-3-6
 * @brief           此库为元素识别库，后续控制在主函数中进行
 * @Last editor     Niko
 ********************************************************************************************************************/

 #ifndef _BD_CTRL_H
 #define _BD_CTRL_H

#include "headfile.h"


typedef enum 
{    
    NO_FLAG,
    STRIAGHT,
    Crossroads,
    TurnLeft,
    TurnRight,
    AngleLeft,
    AngleRight,
    InRoundaboutL,
    InRoundaboutR,
    OutRoundaboutL,
    OutRoundaboutR
}flag_enum;
extern int flag;
extern int error_11;
extern int error_12;
extern int error_13;
extern int error_21;
extern int l12_21;
extern int r12_21;
extern int stra;
void Nelement_recogniz(void);
 #endif