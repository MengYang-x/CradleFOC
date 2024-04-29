//
// Created by User on 2024/4/29.
//
#include "MT6701.h"
#include "spi.h"
#include "math_utils.h"
#include "time_utils.h"

#define MT6701_CS_Enable() HAL_GPIO_WritePin(MT6701_CS_GPIO_Port, MT6701_CS_Pin, GPIO_PIN_RESET)
#define MT6701_CS_Disable() HAL_GPIO_WritePin(MT6701_CS_GPIO_Port, MT6701_CS_Pin, GPIO_PIN_SET)

MT6701 mt6701;
const uint8_t pole_pairs = 7; // 电机的极对数

inline float abs(float _v) {
    return _v >= 0.0f ? _v : -_v;
}

/**
 * @brief 计算机械角度，单位：rad
 * @retval 返回值范围：0~2pi
 * */
float MT6701::GetRawAngle() {
    uint16_t rawData;

    MT6701_CS_Enable();
    HAL_SPI_Receive(&hspi1, (uint8_t *) &rawData, 1, HAL_MAX_DELAY);
    MT6701_CS_Disable();

    return (float) (rawData >> 2) / 16384.0f * _2PI;
}

/**
 * @brief 计算电角度
 * */
float MT6701::GetElAngle() {
    return GetRawAngle() * pole_pairs;
}

/**
 * @brief 计算转过的总角度，单位：rad
 * */
float MT6701::GetFullAngle() {
    float angle_current = GetRawAngle(); // 当前机械角度

    angle_prev_ts = micros();

    float delta_angle = angle_current - angle_last;

    if (abs(delta_angle) > (0.8f * _2PI)) {
        rotationCount += (delta_angle > 0.0f) ? -1 : 1; // 当前时间内转过的圈数
    }
    angle_last = angle_current;
    full_angle = rotationCount * _2PI + angle_last;
    return full_angle;
}

/**
 * @brief 计算转速，单位：rad/s
 * */
float MT6701::GetVelocity() {
    float Ts = (float) (angle_prev_ts - vel_angle_prev_ts) * 1e-6f;
    if (Ts <= 0) Ts = 1e-3f;

    full_angle = GetFullAngle();

    float delta_angle = (rotationCount - rotationCount_last) * _2PI + (full_angle - full_angle_last);
    float vel = delta_angle / Ts;

    rotationCount_last = rotationCount;
    full_angle_last = full_angle;
    vel_angle_prev_ts = angle_prev_ts;

    return vel;
}
