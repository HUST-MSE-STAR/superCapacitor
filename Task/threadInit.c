/* 
 * threadInit.c - The C source file of the system threads' Initialization
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

#include "threadInit.h"

#define _DEBUG_NOT_START_THREAD_    //调试硬件环境情况下，关闭所有线程

rt_thread_t thread_sysWarn;         //系统错误信息发送线程句柄
rt_thread_t thread_sysDataFB;       //系统数据回传线程
rt_thread_t thread_sysCmdHandle;    //上位机数据处理线程
rt_thread_t thread_thresholdFix;    //阈值适配线程
rt_thread_t thread_outputOver;      //总输出过压处理线程句柄
rt_thread_t thread_dataAcquisition; //数据采集线程
rt_thread_t thread_capEnergyLED;    //超级电容能量LED指示灯
rt_thread_t thread_indCurrMode;     //电感电流模式控制线程

//注意：芯片存储
//FLASH:512KB
//SRAM:96KB

/**************分配线程静态内存***********/
ALIGN(RT_ALIGN_SIZE)
static struct rt_thread thread_sysDataFBSource;
static char stack_sysDataFB[512];

static struct rt_thread thread_sysCmdHandleSource;
static char stack_sysCmdHandle[512];

static struct rt_thread thread_thresholdFixSource;
static char stack_thresholdFix[512];

static struct rt_thread thread_sysWarnSource;
static char stack_sysWarn[512];

static struct rt_thread thread_outputOverSource;
static char stack_outputOver[512];

static struct rt_thread thread_dataAcquistitionSource;
static char stack_dataAcquisition[512];

static struct rt_thread thread_capEnergyLEDSource;
static char stack_capEnergyLED[128];

static struct rt_thread thread_indCurrModeSource;
static char stack_indCurrMode[512];
/************静态内存分配结束**************/

/*  @brief  系统线程总初始化函数
 *  @note   在系统底层初始化完成后，需要立即调用该函数以启用所有线程
 *  @author 江榕煜（2020.8.17）
 *  @param  无
 *  @retval 无
 */
void systemAllThreadInit(void)
{
    /*********初始化静态线程**********/
    
    thread_sysDataFB = &thread_sysDataFBSource;
    rt_thread_init(thread_sysDataFB,"dataSendBack",threadEntry_dataSendBack,RT_NULL,
        &stack_sysDataFB[0],sizeof(stack_sysDataFB),
            RT_THREAD_PRIORITY_MAX,2);  //数据回传线程
    
    thread_sysCmdHandle = &thread_sysCmdHandleSource;
    rt_thread_init(thread_sysCmdHandle,"commandHandle",threadEntry_commandHandle,RT_NULL,
        &stack_sysCmdHandle[0],sizeof(stack_sysCmdHandle),
            RT_THREAD_PRIORITY_MAX,2);  //命令处理线程
    
    thread_sysWarn = & thread_sysWarnSource;
    rt_thread_init(thread_sysWarn,"systemWarn",threadEntry_systemWarn,RT_NULL,
        stack_sysWarn,sizeof(stack_sysWarn),
            RT_THREAD_PRIORITY_MAX,2);    //输出警告线程，线程分配时间片2
    
    thread_outputOver = & thread_outputOverSource;
    rt_thread_init(thread_outputOver,"outputOver",threadEntry_outputOver,RT_NULL,
        stack_outputOver,sizeof(stack_outputOver),
            RT_THREAD_PRIORITY_MAX,2);  //输出恢复线程
    
    thread_dataAcquisition = &thread_dataAcquistitionSource;
    rt_thread_init(thread_dataAcquisition,"dataAcquis",threadEntry_dataAcquis,RT_NULL,
        stack_dataAcquisition,sizeof(stack_dataAcquisition),
            RT_THREAD_PRIORITY_MAX,2);  //数据采集线程
    
    thread_capEnergyLED = &thread_capEnergyLEDSource;
    rt_thread_init(thread_capEnergyLED,"capEnergyShow",threadEntry_capEnergyLED,RT_NULL,
        stack_capEnergyLED,sizeof(stack_capEnergyLED),
            RT_THREAD_PRIORITY_MAX,2);  //超级电容容量显示线程
        
    thread_thresholdFix = &thread_thresholdFixSource;
    rt_thread_init(thread_thresholdFix,"capEnergyShow",threadEntry_thresholdFix,RT_NULL,
        stack_thresholdFix,sizeof(stack_thresholdFix),
            RT_THREAD_PRIORITY_MAX,2);  //阈值适配线程
        
    thread_indCurrMode = &thread_indCurrModeSource;
    rt_thread_init(thread_indCurrMode,"capEnergyShow",threadEntry_indCurrMode,RT_NULL,
        stack_indCurrMode,sizeof(stack_indCurrMode),
            RT_THREAD_PRIORITY_MAX,2);  //阈值适配线程
        
    /********启动需要的线程******/
    #ifndef _DEBUG_NOT_START_THREAD_        
        rt_thread_startup(thread_sysCmdHandle);     //启动线程：外部命令处理
        rt_thread_startup(thread_sysDataFB);        //启动线程：数据回传线程
        rt_thread_startup(thread_dataAcquisition);  //启动线程：数据采集
        rt_thread_startup(thread_capEnergyLED);     //启动线程：超级电容能量显示
        rt_thread_startup(thread_thresholdFix);     //启动线程：阈值适配
        rt_thread_startup(thread_indCurrMode);      //启动线程：电感电流模式适配
    #endif
}

void showStackAddr(void)
{
    rt_kprintf("stack_sysDataFB:%p",stack_sysDataFB);
}

MSH_CMD_EXPORT(showStackAddr,show addr);
