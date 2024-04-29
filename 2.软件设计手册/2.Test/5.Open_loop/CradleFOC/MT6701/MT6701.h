//
// Created by User on 2024/4/29.
//

#ifndef CRADLEFOC_MT6701_H
#define CRADLEFOC_MT6701_H

#include "stdint.h"

class MT6701 {
private:
    uint64_t angle_prev_ts;
    uint64_t vel_angle_prev_ts;
    int rotationCount; // 转过的圈数
    int rotationCount_last;
    float angle_last; // 上一时刻的机械角度
    float full_angle; // 转过的总角度
    float full_angle_last;
public:

    float GetRawAngle();
    float GetFullAngle();
    float GetElAngle();
    float GetVelocity();
};

extern MT6701 mt6701;
#endif //CRADLEFOC_MT6701_H
