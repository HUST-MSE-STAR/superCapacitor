/* 
 * HRPWMcontrol.h - The C head file of the HRTIME PWM driver
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
#ifndef _HRPWM_CONTROL_H_

#define _HRPWM_CONTROL_H_

#include "main.h"
#include "hrtim.h"

/*  @brief  设置Buck驱动电路PWM占比
 *  @note   输入参数必须为无符号整数
 *  @author 江榕煜（2020.8.11）
 *  @param  占空比
 *  @retval 无
 */
#define setPWMofBuck(duty) (hhrtim1.Instance->sTimerxRegs[HRTIM_TIMERINDEX_TIMER_A].CMP1xR = (int)(duty));

/*  @brief  启动Buck驱动电路PWM输出
 *  @note   注意初始化好外设状态
 *  @author 江榕煜（2020.8.11）
 *  @param  无
 *  @retval 无
 */
void enablePWMofBuck(void);

/*  @brief  关闭Buck驱动电路PWM输出
 *  @note   暂无
 *  @author 江榕煜（2020.8.11）
 *  @param  无
 *  @retval 无
 */
void disablePWMofBuck(void);

#endif
