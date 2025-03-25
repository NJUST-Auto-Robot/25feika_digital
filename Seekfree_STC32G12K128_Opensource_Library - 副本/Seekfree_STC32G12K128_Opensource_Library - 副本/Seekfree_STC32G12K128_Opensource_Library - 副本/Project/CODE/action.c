/*********************************************************************************************************************
 * @author     		Niko
 * @Target core		STC32G12K128
 * @date       		2025-3-6
 * @brief           此库为元素识别库，后续控制在主函数中进行
 * @Last editor     Niko
 ********************************************************************************************************************/
#include "headfile.h"
#include  "action.h"
#include "BD_ctrl.h"
void motor(void)
{
    if(flag == NO_FLAG)
    {
        DRV8701_loop_ctrl(0,0);
    }
    if(flag == STRIAGHT)
    {
        DRV8701_loop_ctrl(100,100);
    }
    if(flag == Crossroads)
    {
        DRV8701_loop_ctrl(100,100);
    }
    if(flag == TurnLeft)
    {
        DRV8701_loop_ctrl(100,50);
    }
    if(flag == TurnRight)
    {
        DRV8701_loop_ctrl(50,100); 
    }
    if(flag == AngleLeft)
    {
        DRV8701_loop_ctrl(100,70);
    }
    if(flag == AngleRight)
    {
        DRV8701_loop_ctrl(70,100);
    }
    if(flag == InRoundaboutL)
    {
       DRV8701_loop_ctrl(100,30);
    }
    if(flag == InRoundaboutR)
    {
       DRV8701_loop_ctrl(30,100);
    }
    if(flag == OutRoundaboutL)
    {
       DRV8701_loop_ctrl(100,30); 
    }
    else{
        DRV8701_loop_ctrl(0,0);
    }

    
   
}