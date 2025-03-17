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
    STRIAGHT,
    Crossroads,
    TurnLeft,
    TurnRight,
    AngleLeft,
    AngleRight,
    InRoundaboutL,
    InRoundaboutR,
}flag_enum;
 #endif