//
// Created by User on 2024/5/3.
//

#include "UserAPP.h"
#include "Serial.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "SVPWM.h"
#include "motor.h"


extern osThreadId myTask02_LOGHandle;
extern osThreadId myTask03_KEYHandle;
extern osThreadId myTask04_FOCHandle;

extern uint8_t flag_button;
extern float Ta, Tb, Tc; // 三相占空比：0~1

void setup() {
    log_DMA_TX("Init Start....\r\n");
    start_TIM_CHx();
    log_DMA_TX("Init Finish....\r\n");
    HAL_Delay(100);
}

// 输出串口信息
void task_log() {

#if LOG_Stack
    // 计算各任务所需栈大小，经过测试创建线程时需要25Words左右
    static uint16_t task_log;
    static uint16_t task_key;
    static uint16_t task_foc;

    task_log = uxTaskGetStackHighWaterMark(myTask02_LOGHandle);
    task_key = uxTaskGetStackHighWaterMark(myTask03_KEYHandle);
    task_foc = uxTaskGetStackHighWaterMark(myTask04_FOCHandle);

    log_DMA_TX("[log,key,foc]:%d,%d,%d\r\n", task_log, task_key, task_foc);
#endif

#if LOG_Duty
    log_DMA_TX("[Ta,Tb,Tc]:%f,%f,%f\r\n", Ta, Tb, Tc);
#endif

}

// 按键控制
void task_key() {
    switch (flag_button) {
        case 0:
            vTaskSuspend(myTask04_FOCHandle);
            stop_TIM_CHx();
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
            break;
        case 1:
            vTaskResume(myTask04_FOCHandle);
            start_TIM_CHx();
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
            break;
    }
}

// FOC电机运行控制
void task_FOC() {
    open_velocity_test1(50);
}



