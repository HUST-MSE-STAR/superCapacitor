/* 
 * LED_BSP.h - The C source file of the LED driver
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

#include "superCapBSP.h"


/*  @brief  能量指示灯全亮
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_4(void)
{
    HAL_GPIO_WritePin(LED_CAP_1_GPIO_Port,LED_CAP_1_Pin | LED_CAP_2_Pin | LED_CAP_3_Pin,GPIO_PIN_RESET);    //全亮
    HAL_GPIO_WritePin(LED_CAP_4_GPIO_Port,LED_CAP_4_Pin,GPIO_PIN_RESET);
}    

/*  @brief  能量指示灯显示3/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_3(void)
{
    HAL_GPIO_WritePin(LED_CAP_1_GPIO_Port,LED_CAP_1_Pin | LED_CAP_2_Pin | LED_CAP_3_Pin,GPIO_PIN_RESET);    //三个灯亮
    
    HAL_GPIO_WritePin(LED_CAP_4_GPIO_Port,LED_CAP_4_Pin,GPIO_PIN_SET);
}    

/*  @brief  能量指示灯显示2/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_2(void)
{
    HAL_GPIO_WritePin(LED_CAP_1_GPIO_Port,LED_CAP_1_Pin | LED_CAP_2_Pin,GPIO_PIN_RESET);    //两个灯亮
    
    HAL_GPIO_WritePin(LED_CAP_4_GPIO_Port,LED_CAP_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_CAP_3_GPIO_Port,LED_CAP_3_Pin,GPIO_PIN_SET);
}    

/*  @brief  能量指示灯显示1/4
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_1(void)
{
    HAL_GPIO_WritePin(LED_CAP_1_GPIO_Port,LED_CAP_1_Pin,GPIO_PIN_RESET);    //一个灯亮
    
    HAL_GPIO_WritePin(LED_CAP_4_GPIO_Port,LED_CAP_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_CAP_2_GPIO_Port,LED_CAP_2_Pin | LED_CAP_3_Pin,GPIO_PIN_SET);
}

/*  @brief  能量指示灯显示空
 *  @note   该函数只适用于该工程配置的外设情况！
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void capLED_0(void)
{
    HAL_GPIO_WritePin(LED_CAP_1_GPIO_Port,LED_CAP_1_Pin | LED_CAP_2_Pin | LED_CAP_3_Pin,GPIO_PIN_SET);  //全熄灭
    HAL_GPIO_WritePin(LED_CAP_4_GPIO_Port,LED_CAP_4_Pin,GPIO_PIN_SET);
}        
