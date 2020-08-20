/* 
 * controlServer.c - The C source file of system comunicating server for control
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
 
#define _system_Data_transmit_use_UART_
#define _system_Data_transmit_use_CAN_
 
/******32外设头文件引入******/
#include "mcuHWInit.h"
#include "threadInit.h"
 
 /*****RT-Thread系统文件引入**/
#include <rthw.h>
#include <rtthread.h>

/*--------BSP文件引入----------*/
#include "superCapBSP.h"

/*********通信专用数据********/
uint8_t errorCode = 0x1c;   //错误状态码
struct systemStatus systemADCdata;  //定义位于superCapBSP头文件

/*--------------线程定义-----------------*/

/*  @brief  系统报错线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.11）
 *  @param  none
 *  @retval none
 */
void threadEntry_systemWarn(void *parameter)
{
    while(1)
    {
        if(errorCode == 0x1c)
        {   //若无错误发生
            rt_thread_suspend(thread_sysWarn);  //挂起线程
            rt_schedule();  //让出CPU
        }
        else{
            //TODO：CAN和UART发送数据
            
            rt_thread_mdelay(100);  //以10Hz的频率发送警告
        }
    }
}
/*  @brief  数据采集线程
 *  @note   声明位于threadInit头文件
 *          该线程需要使用信号量控制数据的获取
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_dataAcquis(void *parameter)
{
    while(1)
    {
        /*---------输出质量读取---------*/
        if(HAL_GPIO_ReadPin(BST_PGOD_GPIO_Port,BST_PGOD_Pin))   //如果输出质量差信号消失
            errorCode |= 0x04;  //拉高标志位
        else
            errorCode &= 0xfb;  //拉低标志位
        
        /*---------系统核心温度ADC读取-----------*/
        beginTempADC();
    }
}

/*  @brief  数据回传线程
 *  @note   声明位于threadInit头文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_dataSendBack(void *parameter)
{}

/*  @brief  用户命令处理线程
 *  @note   声明位于threadInit头文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_commandHandle(void *parameter)
{}

/*  @brief  阈值设置线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_thresholdFix(void *parameter)
{}

/*  @brief  电感电流模式调整线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_indCurrMode(void *parameter)
{}
