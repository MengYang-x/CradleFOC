//
// Created by User on 2024/4/30.
//

#include "motor.h"
#include "SVPWM.h"
#include "stdint.h"

const uint8_t polePairs =7; // 无刷电机的极对数

/**
 * @brief 开环运行测试
 * @note 虚拟一个电角度累加器
 * @param velocity 目标转速(rad/s)
 * @retval 无
 */
void open_velocity_test1(float velocity)
{
    static const float Uq = 2.0f;
    static const float Ud = 0.0f;

    static const float deltaT = 0.00625f;
    static float el_angle = 0.0f;

    el_angle = el_angle + velocity * deltaT; // 电角度累加器

    setPhaseVoltage(Uq, Ud, el_angle);
}