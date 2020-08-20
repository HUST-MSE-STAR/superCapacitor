/* 
 * uartFinshCharIO.h - The C head file of RT-Thread Finsh IO
 * NOTE: This file is based on HAL library of stm32 platform
 *
 * Copyright (c) 2020-, FOSH cap buffer Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes           mail
 * 2020-08-11     江榕煜       first version   2373180028@qq.com
 */
#ifndef _UART_FINSH_CHAR_IO_H_

#define _UART_FINSH_CHAR_IO_H_

/******使用前请适配以下内容******/
#define FinshUartHandle huart5   //适配为使用的UART句柄
#define FinshUartIRQHandler  UART5_IRQHandler //相应的UART中断
#define FinshUartRxBufLen 16  //适配为需要的缓存空间大小


#include "stm32g4xx_it.h"       //适配为相应的芯片中断头文件
/******用户适配结束******/

#include "usart.h"
#include "main.h"

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

/*
 * @brief 初始化控制台IO
*/
void FinshIoInit(void);

/*
 * @brief 控制台获取字符接口（RTT标准）
 * @retn  返回字符
*/
char rt_hw_console_getchar(void);

/*
 * @brief 控制台输出字符接口（RTT标准）
 * @arg1  输出的字符串
*/
void rt_hw_console_output(const char *str);

#endif
