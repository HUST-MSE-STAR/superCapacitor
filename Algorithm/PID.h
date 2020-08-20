/* 
 * PID.h - The C head file of PID controller
 * NOTE: This file is based on C11
 *
 * Copyright (c) 2020-, FOSH Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes           mail
 * 2020-07-28     江榕煜       first version   2373180028@qq.com
 */
 /********** 用前请适配 **************/
#define PID_use_integral  //若使用位置式PID则开启该预编译选项

#define PID_DATA_TYPE float //定义使用的PID数据类型

/*********** 适配结束 ***************/

#ifndef _PID_H_
#define _PID_H_

struct PID
{       //PID数据结构体

/************ 内部参数 *************/
    PID_DATA_TYPE K_p;  //比例增益
    PID_DATA_TYPE K_i;  //积分增益
    PID_DATA_TYPE K_d;  //微分增益

    PID_DATA_TYPE target_;   //输出目标值

    PID_DATA_TYPE error_Pre;    //上一次误差
    PID_DATA_TYPE error_PPre;   //上上次误差

#ifdef PID_use_integral
    PID_DATA_TYPE output_pre;   //上次输出值
#endif

    PID_DATA_TYPE max_;  //PID输出最大值
    PID_DATA_TYPE min_;  //PID输出最小值
};


/*********** 模块接口 ***********/
typedef struct PID * PIDptr;   //模块指针

/*  @brief  计算PID增量
 *  @note   本增量算法有输出限幅
 *  @author 江榕煜（2020.7.28）
 *  @param  PIDhandler（PID句柄），status（当前测量状态）
 *  @retval 增量值
 */
PID_DATA_TYPE PID_updateDelta(PIDptr PIDhandler, PID_DATA_TYPE status);

#ifdef PID_use_integral

/*  @brief  计算PID位置输出
 *  @note   该算法实质上调用增量式算法
 *  @author 江榕煜（2020.7.28）
 *  @param  PIDhandler（PID句柄），status（当前测量状态）
 *  @retval 新（位置）状态值
 */
PID_DATA_TYPE PID_updateStatus(PIDptr PIDhandler, PID_DATA_TYPE status);
#endif

#endif
