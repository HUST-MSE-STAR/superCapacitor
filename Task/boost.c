/* 
 * boost.c - The C source file of tasks of the boost circuit
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
#include "threadInit.h"
#include "superCapBSP.h"

#define GPIO_PIN_BoostPowerGood GPIO_PIN_1  //电源质量引脚号定义
#define BOOST_OUTPUT_QUALITY_IRQ EXTI1_IRQHandler   //电源质量引脚对应外部中断服务接口

/*  @brief  输出端Boost电压质量差中断
 *  @note   当输出波动大于10%时，将会产生改中断
 *  @author 江榕煜（2020.8.17）
 *  @param 
 *  @retval
 */

void BOOST_OUTPUT_QUALITY_IRQ(void)
{   
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_BoostPowerGood) != 0x00u)    //确认中断
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_BoostPowerGood);      //删除中断标志位
        
        extern uint8_t errorCode;   //引用controlServer.c文件中的错误状态码变量
        errorCode &= 0xfb;  //拉低标志位
        
        //TODO：处理线程启动
    }
}

#define BOOST_OUTPUT_COMP hcomp2
#define BOOST_OUTPUT_ADC hadc2

/*  @brief  比较器触发中断回调函数
 *  @note   多个比较器共同使用
 *  @author 江榕煜（2020.8.16）
 *  @param  比较器句柄
 *  @retval 无
 */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
    if(hcomp == &BOOST_OUTPUT_COMP)    //如果是输出比较器（COMP2）
    {
        HAL_ADC_Start(&BOOST_OUTPUT_ADC);  //启动ADC转换
        uint16_t adcData = HAL_ADC_GetValue(&BOOST_OUTPUT_ADC);    //获取转换结果
        
        float voltage = adcData * 0.014379882; //0.014379882 =  58.9 /4096;     //数值映射
        
        if(voltage > 30)
        {
            HAL_GPIO_WritePin(BST_EN_GPIO_Port,BST_EN_Pin,GPIO_PIN_RESET);  //关闭输出
            rt_thread_resume(thread_outputOver);    //启动恢复输出线程
        }
        
    }

}

/*  @brief  总输出恢复线程
 *  @note   定义位于boost文件
 *  @author 江榕煜（2020.8.16）
 *  @param  none
 *  @retval none
 */
void threadEntry_outputOver(void *parameter)
{
    uint16_t adcData;
    while(1)
    {
        HAL_ADC_Start(&BOOST_OUTPUT_ADC);  //启动ADC转换
        adcData = HAL_ADC_GetValue(&BOOST_OUTPUT_ADC);    //获取转换结果
        
        float voltage = adcData * 0.014379882; //0.014379882 =  58.9 /4096;     //数值映射
            
        if(voltage < 30)    //若电压已经小于阈值
        {
            HAL_GPIO_WritePin(BST_EN_GPIO_Port,BST_EN_Pin,GPIO_PIN_SET);  //启动输出
            rt_thread_suspend(thread_outputOver);    //挂起恢复输出线程
            rt_schedule();  //交出CPU
        }
        else
            rt_thread_delay(100);   //以10Hz的频率检测输出口电压
    }
}


/*  @brief  软件启动Boost电路输出
 *  @note   该函数定义位于superCapBSP头文件中
            注意先启动Buck输出
 *  @author 江榕煜（2020.8.18）
 *  @param  无
 *  @retval 无
 */
void beginBoost(void)
{
    
}
