# SuperCapDriverV2
 2020年第二版本超级电容驱动程序

> 为了减小工程体积，上传的代码省略了STM32的HAL库，若要使用，需先进入CubeMX工程，生成依赖环境

## 工程说明

一级文件(夹) | 文件 | 说明
:---| :---: | ---:
Algorithm | | 算法库文件夹
--- | PID.c | PID算法定义源文件
--- | PID.h | PID算法接口头文件
BSP |   | 底层封装库文件夹
--- | HRPWMcontrol.c | 高精度PWM驱动文件
--- | HRPWMcontrol.h | 高精度PWM驱动接口文件
--- | mcuHWInit.c | 主控芯片外设初始化源文件
--- | mcuHWInit.h | 主控芯片外设初始化接口文件
--- | uartFinshCharIO.c | 控制台驱动源文件
--- | uartFinshCharIO.h | 控制台驱动适配文件
--- | superCapBSP.h | 系统BSP总体接口文件
Task |  | RT-Thread线程任务文件夹
--- | boost.c | boost任务相关线程源文件
--- | buck.c | buck任务相关线程源文件
--- | controlServer.c | 系统辅助控制线程源文件
--- | threadInit.c | 系统线程初始化源文件
--- | threadInit.h | 系统线程初始化接口文件
--- | UI.c | 用户接口任务源文件
superCapDriverV2.ioc | | CubeMX工程文件
readme.md | | 工程说明文件
