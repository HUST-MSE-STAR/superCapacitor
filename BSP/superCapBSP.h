/* 
 * superCapBSP.h - The C head file of all superCap system BSP files
 * NOTE: This file is based on HAL library of stm32 platform
 *
 * Copyright (c) 2020-, super cap buffer Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes           mail
 * 2020-08-17     江榕煜       first version   2373180028@qq.com
 */

#ifndef _SUPERCAPBSP_H_
#define _SUPERCAPBSP_H_

#include "mcuHWInit.h"
#include "uartFinshCharIO.h"

/*----------结构体定义--------*/
struct systemStatus{
    uint16_t inputCurrentADC;   //输入线电流
    uint16_t capVoltADC;        //电容电压
    uint16_t sysTempADC;        //系统核心温度
    uint16_t inputVoltADC;      //输入电压
    uint16_t outputVoltADC;     //输出电压
};

/*  @brief  启动温度传感器ADC读取
 *  @note   本函数是宏定义函数
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
#define beginTempADC() HAL_ADC_Start_IT(&hadc5)

/*  @brief  软件启动Buck电路输出
 *  @note   该函数定义位于buck.c文件中
            为了防止Boost电路启动后报错，必须先启动Buck后Boost
 *  @author 江榕煜（2020.8.18）
 *  @param  无
 *  @retval 无
 */
void beginBuck(void);

/*  @brief  软件启动Boost电路输出
 *  @note   该函数定义位于boost.c文件中
            注意先启动Buck输出
 *  @author 江榕煜（2020.8.18）
 *  @param  无
 *  @retval 无
 */
void beginBoost(void);

/*  @brief  能量指示灯全亮
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_4(void);    

/*  @brief  能量指示灯显示3/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_3(void);    

/*  @brief  能量指示灯显示2/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_2(void);    

/*  @brief  能量指示灯显示1/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_1(void);

/*  @brief  能量指示灯显示1/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_0(void);    

#endif
