/* 
 * UI.c - The C source file of the system User Interface
 * NOTE: This file is based on HAL library of stm32 platform
 *
 * Copyright (c) 2020-, super cap buffer Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes           mail
 * 2020-08-11     江榕煜       first version   2373180028@qq.com
 */
  
 /*****RT-Thread系统文件引入**/
#include <rthw.h>
#include <rtthread.h>

/*--------BSP文件引入----------*/
#include "superCapBSP.h"


/*--------全局变量定义--------*/
struct energyLevel{
    uint16_t L1,L2,L3,L4;
} capEnergyLevelData;
/*--------变量定义结束--------*/
 

/*  @brief  超级电容能量指示灯
 *  @note   声明位于threadInit头文件
            该线程使用前需调用capEnergyLEDInit函数进行初始化
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_capEnergyLED(void *parameter)
{
    extern struct systemStatus systemADCdata;
    while(1)
    {
        if(systemADCdata.capVoltADC > capEnergyLevelData.L4)
            capLED_4();
        else if(systemADCdata.capVoltADC >capEnergyLevelData.L3)
            capLED_3();
        
        else if(systemADCdata.capVoltADC >capEnergyLevelData.L2)
            capLED_2();
        
        else if(systemADCdata.capVoltADC >capEnergyLevelData.L1)
            capLED_1();
        
        else if(systemADCdata.capVoltADC <capEnergyLevelData.L1)
            capLED_0();
        
        rt_thread_mdelay(500);  //更新频率为2Hz
    }
}

/*  @brief  超级电容能量显示初始化
 *  @note   该函数只需调用一次，且必须被调用！
            初始化会读取FLASH中存储的电容设置参数
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void capEnergyLEDInit()
{
    //TODO：读取FLASH内容，计算LED灯阈值
}

