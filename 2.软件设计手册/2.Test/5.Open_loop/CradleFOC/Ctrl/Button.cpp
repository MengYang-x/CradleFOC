//
// Created by User on 2024/4/30.
//

#include "Button.h"
#include "main.h"
#include "SVPWM.h"

enum State {
    stop,
    start
} tim_state;

void tim_CHx_Ctrl(State state) {
    switch (state) {
        case stop:
            stop_TIM_CHx();
            state = start; // 再次按下按键时，切换为启动状态
            break;
        case start:
            start_TIM_CHx();
            state = stop;
            break;
    }
}

// 自定义us延时函数
void delay_us(uint32_t us) {
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 24000000 * us); // 数值与选用的晶振有关，24MHz无源晶振
    while (delay--); // 循环delay次，达到1us延时
}

// 按键扫描函数
uint8_t key_scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    uint8_t flag = 0;      // 按键未按下
    uint16_t time = 30000; // 按键消抖时间，30ms
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0) {
        delay_us(time);
        if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0) {
            flag = 1; // 确定按键被按下
        }
    }
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0); // 等待按键松开
    delay_us(time);
    return flag;
}

/**
 * @brief  EXTI line detection callback.
 * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    /* Prevent unused argument(s) compilation warning */
    UNUSED(GPIO_Pin);

    // 中断源判断
    switch (GPIO_Pin) {
        case KEY1_Pin: // PC10，抢占优先级0，响应优先级0
            if (key_scan(KEY1_GPIO_Port, KEY1_Pin)) {
                HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
                tim_CHx_Ctrl(tim_state);
            }
            break;
        case KEY2_Pin: // PC11，抢占优先级0，响应优先级0
            if (key_scan(KEY2_GPIO_Port, KEY2_Pin)) {
                HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
            }
            break;

        default:
            break;
    }
}