//
// Created by User on 2024/5/3.
//

#include "adc_utils.h"
#include "stdint.h"
#include "tim.h"
#include "adc.h"

uint16_t adc1_value[3]; // 0：电位器，1：C相电压，2：A相电压
uint16_t adc2_value[3]; // 0：母线电压Udc，1：NTC，2：B相电压

// ADC初始化配置
void init_adc() {
    TIM1->CCR4 = 8500 - 5; // 用于触发ADC注入组转换
    TIM2->CCR2 = 17000 - 5; // 用于触发ADC规则组转换
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

    // 开启ADC自校准
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);

    // 启动DMA搬运ADC规则组数据
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_value, 3);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc2_value, 3);
}
