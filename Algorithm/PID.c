/* 
 * PID.c - The C source file of PID controller
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
#include "PID.h"

/*  @brief  计算PID增量
 *  @note   本增量算法有输出限幅
 *  @author 江榕煜（2020.7.28）
 *  @param  PIDhandler（PID句柄），status（当前测量状态）
 *  @retval 增量值
 */
PID_DATA_TYPE PID_updateDelta(PIDptr PIDhandler, PID_DATA_TYPE status){
    PID_DATA_TYPE errNow = PIDhandler->target_ - status;  //目前误差值

    PID_DATA_TYPE delta =   //输出增量
        PIDhandler->K_p * (errNow - PIDhandler->error_Pre) +    //比例P
        PIDhandler->K_i * errNow +                  //积分I
        PIDhandler->K_d * (errNow - 2*PIDhandler->error_Pre + PIDhandler->error_PPre);  //微分D

    if(delta > PIDhandler->max_) delta = PIDhandler->max_;  //输出限幅
    else if(delta < PIDhandler->min_) delta = PIDhandler->min_;

    PIDhandler->error_PPre = PIDhandler->error_Pre; //误差记忆
    PIDhandler->error_Pre = errNow;

    return delta;  //返回结果
}

#ifdef PID_use_integral     //位置式PID

/*  @brief  计算PID位置输出
 *  @note   该算法实质上调用增量式算法
 *  @author 江榕煜（2020.7.28）
 *  @param  PIDhandler（PID句柄），status（当前测量状态）
 *  @retval 新（位置）状态值
 */
PID_DATA_TYPE PID_updateStatus(PIDptr PIDhandler,PID_DATA_TYPE status){

    PIDhandler->output_pre += PID_updateDelta(PIDhandler,status);
    
    if(PIDhandler->output_pre > PIDhandler->max_) 
        PIDhandler->output_pre = PIDhandler->max_;  //输出限幅
    else 
        if(PIDhandler->output_pre < PIDhandler->min_) 
            PIDhandler->output_pre = PIDhandler->min_;

    return PIDhandler->output_pre;
}

#endif
