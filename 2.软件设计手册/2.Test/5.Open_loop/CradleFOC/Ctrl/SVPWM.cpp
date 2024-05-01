//
// Created by User on 2024/4/29.
//

#include "SVPWM.h"
#include "Serial.h"
#include "tim.h"
#include "arm_math.h"
#include "math_utils.h"

const float Udc = 12.123f; // 母线电压，12V电源适配器
const uint16_t PWM_ARR = 8500;
float Ta, Tb, Tc; // 三相占空比：0~1

/**
 * @brief 使能TIMx的PWM输出通道
 * @note  TIM1
 * @retval 无
 */
void start_TIM_CHx() {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // PA8
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // PA9
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); // PA10
}

void stop_TIM_CHx() {
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1); // PA8
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2); // PA9
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3); // PA10
}

/**
 * @brief SVPWM生成函数
 * @param Uq Q轴电压
 * @param Ud D轴电压
 * @param el_angle 电角度
 * @retval 无
 * @note 基于均值零序分量注入的SVPWM调制
 */
void setPhaseVoltage(float Uq, float Ud, float el_angle) {
    el_angle = _normalizeAngle(el_angle);

    // Ud、Uq最大值等于Udc/sqrt(3)
    Uq = _constrain(Uq, -6.0f, 6.0f);
    Ud = _constrain(Ud, -6.0f, 6.0f);

    // Park逆变换
    float U_alpha = -Uq * arm_sin_f32(el_angle) + Ud * arm_cos_f32(el_angle);
    float U_beta = Uq * arm_cos_f32(el_angle) + Ud * arm_sin_f32(el_angle);

    // 将电压转换为百分比，便于PWM占空比计算
    U_alpha = U_alpha / Udc;
    U_beta = U_beta / Udc;

    // Clark逆变换
    float Ua = U_alpha;
    float Ub = -0.5f * U_alpha + 0.8660254f * U_beta;
    float Uc = -0.5f * U_alpha - 0.8660254f * U_beta;

    // 基于均值零序分量注入的SVPWM调制
    float Umax = findMax(&Ua, &Ub, &Uc);
    float Umin = findMin(&Ua, &Ub, &Uc);
    float Umid = -0.5f * (Umax + Umin);

    Ta = Ua + Umid;
    Tb = Ub + Umid;
    Tc = Uc + Umid;

    map_constraint(&Ta);
    map_constraint(&Tb);
    map_constraint(&Tc);

    // PWM输出
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Ta * PWM_ARR);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Tb * PWM_ARR);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Tc * PWM_ARR);
    TIM1->CCR1 = Ta * PWM_ARR;
    TIM1->CCR2 = Tb * PWM_ARR;
    TIM1->CCR3 = Tc * PWM_ARR;
}
