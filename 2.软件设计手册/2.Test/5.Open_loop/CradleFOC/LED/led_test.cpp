//
// Created by User on 2024/4/29.
//

#include "led_test.h"
#include "main.h"

void LED::led_toggle() {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    HAL_Delay(1000);
}

LED led1;
