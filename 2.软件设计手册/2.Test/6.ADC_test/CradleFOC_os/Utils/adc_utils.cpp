//
// Created by User on 2024/5/3.
//

#include "adc_utils.h"
#include "stdint.h"
#include "tim.h"
#include "adc.h"
#include "Serial.h"

uint16_t adc1_value[3] = {0}; // 0：电位器，1：C相电压，2：A相电压
uint16_t adc2_value[3] = {0}; // 0：母线电压Udc，1：NTC，2：B相电压

uint16_t pot_value; // 电位器
float NTC_value; // 热敏电阻

const float VDDA_3V3 = 3.308f;
float Ubus, Uu, Uv, Uw; // 三相工作电压
float gain_Udc, gain_phase_U, gain_phase_V, gain_phase_W;// 电压增益系数 = VDDA * 分压电阻系数 / 4095 * 修正系数
float calibration_Udc = 1.0f;
float calibration_U = 1.0f;
float calibration_V = 1.0f;
float calibration_W = 1.0f;

// 计算增益系数
void calculate_gain(void) {
    gain_Udc = VDDA_3V3 * 11.0f / 4095.0f * calibration_Udc;
    gain_phase_U = VDDA_3V3 * 11.0f / 4095.0f * calibration_U;
    gain_phase_V = VDDA_3V3 * 11.0f / 4095.0f * calibration_V;
    gain_phase_W = VDDA_3V3 * 11.0f / 4095.0f * calibration_W;
}


// ADC初始化配置
void init_adc() {
    TIM1->CCR4 = 8500 - 10; // 用于触发ADC注入组转换
    TIM2->CCR2 = 1000 - 10; // 用于触发ADC规则组转换

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

    calculate_gain();

    // 开启ADC自校准
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);

    // 启动DMA搬运ADC规则组数据
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc1_value, 3);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *) adc2_value, 3);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hadc);
    if (hadc == &hadc1) {
        pot_value = adc1_value[0];
        Uu = adc1_value[1] * gain_phase_U;
        Uv = adc1_value[2] * gain_phase_V;
    }
    if (hadc == &hadc2) {
        Ubus = adc2_value[0] * gain_Udc;
        NTC_value = adc2_value[1];
        Uw = adc2_value[2] * gain_phase_W;
    }
}

//void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) {
//    /* Prevent unused argument(s) compilation warning */
//    UNUSED(hadc);
//    if (hadc == &hadc1) {
//
//    }
//    if (hadc == &hadc2) {
//
//    }
//}

void adc_log() {
    log_DMA_TX("[pot,,Udc,Uv,Uv,Uw]:%d,%f,%f,%f,%f\r\n", pot_value, Ubus, Uu, Uv, Uw);
}