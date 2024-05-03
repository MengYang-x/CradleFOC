//
// Created by User on 2024/5/3.
//

#include "math_utils.h"
#include "cmath"

/**
 * @brief 角度归一化
 * @param angle 原始角度
 * @retval 0~2pi
 */
float _normalizeAngle(float angle) {
    float a = fmod(angle, _2PI); // fmod()函数用于浮点数的取余运算
    return a >= 0.0f ? a : (a + _2PI);
}

/*
 * @brief 返回三个数中的最大值
 */
float findMax(const float *a, const float *b, const float *c) {
    float max = *a; // 假设第一个数是最大的

    if (*b > max) {
        max = *b;
    }

    if (*c > max) {
        max = *c;
    }

    return max;
}

/*
 * @brief 返回三个数中的最小值
 */
float findMin(const float *a, const float *b, const float *c) {
    float min = *a; // 假设第一个数是最小的

    if (*b < min) {
        min = *b;
    }

    if (*c < min) {
        min = *c;
    }

    return min;
}

/*
 * @brief 将取值范围为[-1,1]的变量，映射到[0,1]
 */
void map_constraint(float *a) {
    *a = (*a + 1.0f) / 2.0f;
}
