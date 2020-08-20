/* 
 * mcuHWInit.h - The C heade file of MCU chip's peripheral Initialization
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
 
#ifndef _mcuHWInit_H_
#define _mcuHWInit_H_

#include "main.h"
#include "adc.h"
#include "comp.h"
#include "dac.h"
#include "fdcan.h"
#include "hrtim.h"
#include "opamp.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/*  @brief  初始化芯片时钟和外设
 *  @note   必须在操作系统开始工作前调用
 *  @author 江榕煜（2020.8.11）
 *  @param  无
 *  @retval 无
 */
void mcuHWInit(void);

#endif
