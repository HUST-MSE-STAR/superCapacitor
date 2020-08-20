/* 
 * HRPWMcontrol.c - The C head file of the HRTIME PWM driver
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
#include "HRPWMcontrol.h"

void enablePWMofBuck(void)
{
    HAL_HRTIM_WaveformOutputStart(&hhrtim1,HRTIM_OUTPUT_TA1);   //使能通道1输出
    HAL_HRTIM_WaveformOutputStart(&hhrtim1,HRTIM_OUTPUT_TA2);   //使能通道2输出
    HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_A); //启动定时器A计数器
    HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_MASTER);  //启动主定时器计数器
    
}

void disablePWMofBuck(void)
{
    HAL_HRTIM_WaveformOutputStop(&hhrtim1,HRTIM_OUTPUT_TA1);    //关闭通道1输出
    HAL_HRTIM_WaveformOutputStop(&hhrtim1,HRTIM_OUTPUT_TA2);    //关闭通道2输出
    HAL_HRTIM_WaveformCounterStop(&hhrtim1,HRTIM_TIMERID_TIMER_A);  //暂停定时器A计数器
    HAL_HRTIM_WaveformCounterStop(&hhrtim1,HRTIM_TIMERID_MASTER);   //暂停主定时器计数器
}

