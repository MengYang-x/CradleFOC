//
// Created by User on 2024/5/3.
//

#include "adc_utils.h"
#include "stdint.h"
#include "tim.h"
#include "adc.h"
#include "Serial.h"
#include "opamp.h"

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


uint16_t ia_offset, ib_offset, ic_offset; // 电流采样偏置值
float gain_current; // 电流增益系数
const float shunt = 0.01f;    // 采样电阻
const float gain_OPA = 17.5f; // OPA增益系数
float ia, ib, ic; // 三相工作电流

// 计算增益系数
void calculate_gain(void) {
    gain_current = VDDA_3V3 / 4095.0f / shunt / gain_OPA;
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

    // 使能内部OPA
    HAL_OPAMP_Start(&hopamp1);
    HAL_OPAMP_Start(&hopamp2);
    HAL_OPAMP_Start(&hopamp3);

    // 开启ADC自校准
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);

    // 启动DMA搬运ADC规则组数据
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc1_value, 3);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *) adc2_value, 3);

    HAL_ADCEx_InjectedStart_IT(&hadc1); // 需要先开启ADC注入组中断，再启动ADC注入组转换
    HAL_ADCEx_InjectedStart_IT(&hadc2);
    HAL_ADCEx_InjectedStart(&hadc1);
    HAL_ADCEx_InjectedStart(&hadc2);
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

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) {
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hadc);

    static uint16_t cnt;
    static uint8_t flag_adc_offset = 0;
    static uint32_t ia_offset_sum, ib_offset_sum, ic_offset_sum;

    if (hadc == &hadc1) {
        uint16_t ia_adc = hadc1.Instance->JDR1;
        uint16_t ib_adc = hadc2.Instance->JDR1;
        uint16_t ic_adc = hadc1.Instance->JDR2;

        if (flag_adc_offset == 0) {
            cnt++;
            ia_offset_sum += ia_adc;
            ib_offset_sum += ib_adc;
            ic_offset_sum += ic_adc;
        }

        if (cnt >= 1000) // 计算ADC转换偏置值
        {
            flag_adc_offset = 1;
            ia_offset = ia_offset_sum / cnt;
            ib_offset = ib_offset_sum / cnt;
            ic_offset = ic_offset_sum / cnt;
        }
        ia = (ia_adc - ia_offset) * gain_current;
        ib = (ib_adc - ib_offset) * gain_current;
        ic = (ic_adc - ic_offset) * gain_current;
    }
}

void adc_log() {
//    log_DMA_TX("[pot,,Udc,Uv,Uv,Uw]:%d,%f,%f,%f,%f\r\n", pot_value, Ubus, Uu, Uv, Uw);
//    log_DMA_TX("[ia_offset, ib_offset, ic_offset]:%d,%d,%d\r\n", ia_offset, ib_offset, ic_offset);
    log_DMA_TX("[ia,ib,ic]:%f,%f,%f\r\n", ia, ib, ic);

//    float Ua_offset = ia_offset * VDDA_3V3 / 4095.0f;
//    float Ub_offset = ib_offset * VDDA_3V3 / 4095.0f;
//    float Uc_offset = ic_offset * VDDA_3V3 / 4095.0f;
//    log_DMA_TX("%f,%f,%f\r\n", Ua_offset, Ub_offset, Uc_offset);

}
