/* 
 * mcuHWInit.c - The C source file of MCU chip's peripheral Initialization
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
#include "mcuHWInit.h"

extern void SystemClock_Config(void);

/*  @brief  初始化芯片时钟和外设
 *  @note   必须在操作系统开始工作前调用
 *  @author 江榕煜（2020.8.11）
 *  @param  无
 *  @retval 无
 */
void mcuHWInit(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    
    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_HRTIM1_Init();
    
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_ADC3_Init();
    MX_ADC4_Init();
    MX_ADC5_Init();
    
    MX_COMP2_Init();
    MX_COMP3_Init();
    MX_COMP6_Init();
    MX_COMP7_Init();
    
    MX_DAC1_Init();
    MX_DAC3_Init();
    MX_DAC4_Init();
    
    MX_FDCAN2_Init();
    
    MX_OPAMP1_Init();
    MX_OPAMP3_Init();
    MX_OPAMP6_Init();
    
    MX_TIM1_Init();
    
    MX_UART5_Init();
    MX_USART3_UART_Init();
}
