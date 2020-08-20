#ifndef _Thread_Init_H_
#define _Thread_Init_H_

#define THREAD_STACK_SIZE 100

/*****RT-Thread系统文件引入**/
#include <rthw.h>
#include <rtthread.h>

/*****RT-Thread系统线程句柄声明**/
extern rt_thread_t thread_sysWarn;      //发送系统警告线程
extern rt_thread_t thread_sysDataFB;   //系统数据回传线程
extern rt_thread_t thread_sysCmdHandle;    //上位机接收数据处理线程
extern rt_thread_t thread_thresholdFix;    //阈值适配线程
extern rt_thread_t thread_outputOver;  //总输出过压处理线程
extern rt_thread_t thread_dataAcquisition; //数据采集线程
extern rt_thread_t thread_capEnergyLED;      //超级电容能量LED指示灯
extern rt_thread_t thread_indCurrMode;     //电感电流模式控制线程

/*********线程句柄声明结束***********/

/*  @brief  系统线程总初始化函数
 *  @note   在系统底层初始化完成后，需要立即调用该函数以启用所有线程
 *  @author 江榕煜（2020.8.11）
 *  @param  无
 *  @retval 无
 */
void systemAllThreadInit(void);


/*  @brief  总输出恢复线程
 *  @note   定义位于boost文件
 *  @author 江榕煜（2020.8.16）
 *  @param  none
 *  @retval none
 */
void threadEntry_outputOver(void *parameter);

/*  @brief  系统报错线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.11）
 *  @param  none
 *  @retval none
 */
void threadEntry_systemWarn(void *parameter);

/*  @brief  数据采集线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_dataAcquis(void *parameter);

/*  @brief  数据回传线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_dataSendBack(void *parameter);

/*  @brief  用户命令处理线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_commandHandle(void *parameter);

/*  @brief  超级电容能量指示灯
 *  @note   定义位于UI文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_capEnergyLED(void *parameter);

/*  @brief  阈值设置线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_thresholdFix(void *parameter);

/*  @brief  电感电流模式调整线程
 *  @note   定义位于controlServer文件
 *  @author 江榕煜（2020.8.17）
 *  @param  none
 *  @retval none
 */
void threadEntry_indCurrMode(void *parameter);

#endif
