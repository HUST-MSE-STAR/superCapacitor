/* 
 * buck.h - The C head file of the synchronize buck circuit tasks
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
 
/******32外设头文件引入******/
#include "mcuHWInit.h"

/*******算法文件引入*********/
#include "PID.h"

/*******BSP驱动文件引入******/
#include "HRPWMcontrol.h"

/*****RT-Thread系统文件引入**/
#include <rthw.h>
#include <rtthread.h>

/*********C 标准库************/
#include <stdio.h>
#include <stdint.h>

/*******Buck电压反馈ADC定义*******/
#define BuckVolFeedBackADC hadc1

/*******全局变量声明*******/
struct PID buckPIDcontroller ={0};  //BUCK电路PID控制器
float buckVoltage = 0;              //BUCK输出电压
float buckFBvolK = 0.007;           //BUCK反馈ADC变换系数

/*  @brief  buck电路PID控制器初始化
 *  @note   在整体系统开始工作前必须调用该函数！
 *  @author 江榕煜（2020.8.11）
 *  @param  无
 *  @retval 无
 */
void buckPIDerInit(void)
{
    buckPIDcontroller.K_p = 8.56255285645567e-05;
    buckPIDcontroller.K_i = 4.23837081293142;
    buckPIDcontroller.K_d = 0;
    
    buckPIDcontroller.error_PPre = 0;   //误差记忆清零
    buckPIDcontroller.error_Pre = 0;
    
    buckPIDcontroller.max_ = 0.95;  //最大占空比95%
    buckPIDcontroller.min_ = 0.05;  //最小占空比5%
    
    buckPIDcontroller.output_pre = 0.1; //预先设置占空比10%
    
    buckPIDcontroller.target_ = 20; //目标电压值20V
}

/*  @brief  ADC采样结束回调函数
 *  @note   该采样由HRTIM硬件触发，系统自动调用
 *  @author 江榕煜（2020.8.11）
 *  @param  ADC句柄
 *  @retval 无
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint32_t adcData=0;
    if(hadc == &BuckVolFeedBackADC)
    {
        adcData=HAL_ADC_GetValue(hadc); //读取ADC转换数据
        buckVoltage = buckFBvolK * (float)adcData ;    //数值映射，25/4096=0.0061
        setPWMofBuck(PID_updateStatus(&buckPIDcontroller,buckVoltage) * 8000);   //PID计算和更新
    }
}

/*  @brief  软件启动Buck电路输出
 *  @note   该函数声明位于superCapBSP头文件中
            为了防止Boost电路启动后报错，必须先启动Buck后Boost
 *  @author 江榕煜（2020.8.18）
 *  @param  无
 *  @retval 无
 */
void beginBuck(void)
{
    
}

/*******************MSH命令导出***********************/

MSH_CMD_EXPORT(enablePWMofBuck,enable the PWM ouput of High-Res timer);   //使能PWM


MSH_CMD_EXPORT(disablePWMofBuck,disable the PWM ouput of High-Res timer); //失能PWM

int setPWM(int argc,char** argv)
{
    int duty ;
    sscanf(argv[1],"%d",&duty);
    setPWMofBuck(duty);
    return 0;
}

MSH_CMD_EXPORT(setPWM,set the duty of High-Res PWM);    //改变PWM占空比，实际参数为比较器数值！

int setPID_P(int argc,char** argv)
{
    float P;
    sscanf(argv[1],"%f",&P);
    buckPIDcontroller.K_p = P;
    return 0;
}

MSH_CMD_EXPORT(setPID_P,set P parameter of buck PID controller);

int setPID_I(int argc,char** argv)
{
    float I;
    sscanf(argv[1],"%f",&I);
    buckPIDcontroller.K_i = I;
    return 0;
}

MSH_CMD_EXPORT(setPID_I,set I parameter of buck PID controller);

int setPID_D(int argc,char** argv)
{
    float D;
    sscanf(argv[1],"%f",&D);
    buckPIDcontroller.K_d = D;
    return 0;
}

MSH_CMD_EXPORT(setPID_D,set D parameter of buck PID controller);

void showPID(void)
{
    char printCache [30];   //开辟缓存
    sprintf(printCache,"P:%8.6f,I:%6.4f,D:%6.4f\n",buckPIDcontroller.K_p,buckPIDcontroller.K_i,buckPIDcontroller.K_p);  //转换为字符串
    rt_kprintf("%s",printCache);    //打印字符串
}

MSH_CMD_EXPORT(showPID,print the parameter of buck PID controller);

void showVoltage(void)
{
    char printCache [11];
    sprintf(printCache,"Vol:%5.2f",buckVoltage);
    rt_kprintf("%s",printCache);    //打印字符串
}

MSH_CMD_EXPORT(showVoltage,print the voltage of buck output);

int modifyFBK(int argc,char ** argv)
{
    float K;
    sscanf(argv[1],"%f",&K);
    buckFBvolK = K;
    return 0;
    
}

MSH_CMD_EXPORT(modifyFBK,modify the ADC factor to Voltage);

/*******************MSH命令导出（END）***********************/

