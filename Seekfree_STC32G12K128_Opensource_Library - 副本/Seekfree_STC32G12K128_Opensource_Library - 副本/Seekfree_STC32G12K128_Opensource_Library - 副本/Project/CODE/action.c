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
int  left_speed;
int  right_speed; 
void motor(void)
{
    if(flag == NO_FLAG)
    {
        DRV8701_loop_ctrl(0,0);
    }
    if(flag == STRIAGHT)
    {  
       left_speed = 30;
       right_speed = 30;
       stra=stra*0.5;
       if (dg_state.L_l11_once<8&&dg_state.L_r11_once<8)
       {
        left_speed = left_speed + stra;
        right_speed = right_speed;
       }
       DRV8701_loop_ctrl(left_speed,right_speed);
    }
    // if(flag == Crossroads)
    // {
    //     DRV8701_loop_ctrl(100,100);
    // }
    if(flag == TurnLeft)
    {  
      left_speed = 50;
      right_speed = 10; 
      DRV8701_loop_ctrl(left_speed,right_speed);
    }

    
    if(flag == TurnRight)
    {
      left_speed = 10;
      right_speed = 60; 
      DRV8701_loop_ctrl(left_speed,right_speed);
    
    }
    if(flag == AngleLeft)
    {
        DRV8701_loop_ctrl(0,0);
    }
    if(flag == AngleRight)
    {
        DRV8701_loop_ctrl(0,0);
    }
    if(flag == InRoundaboutL)
    {
       DRV8701_loop_ctrl(0,0);
    }
    if(flag == InRoundaboutR)
    {
       DRV8701_loop_ctrl(0,0);
    }
    if(flag == OutRoundaboutL)
    {
       DRV8701_loop_ctrl(0,0); 
    } 
}