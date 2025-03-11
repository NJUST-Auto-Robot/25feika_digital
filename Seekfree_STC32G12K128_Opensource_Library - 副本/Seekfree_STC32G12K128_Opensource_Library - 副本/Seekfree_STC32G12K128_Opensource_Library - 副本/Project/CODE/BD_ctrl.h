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
#include "ADC.h"
typedef enum __mode
{
    _MODE_NONE = 0,
    STRIAGHT,
    //十字路口
    Crossroads,
    //直角弯道(左侧，右侧)
    TurnLeft,
    TurnRight,
    //锐角弯道(左侧，右侧)
    AngleLeft,
    AngleRight,
    //进环岛(左侧，右侧)
    InRoundaboutL,
    InRoundaboutR,
    //出环岛(左侧，右侧)
    OutRoundaboutL,
    OutRoundaboutR,
} Track_MODE_enum;
extern Track_MODE_enum Track;
extern int flag;

#endif