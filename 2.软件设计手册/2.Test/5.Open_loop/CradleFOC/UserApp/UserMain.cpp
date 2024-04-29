//
// Created by User on 2024/4/29.
//

#include "UserMain.h"
#include "main.h"
#include "arm_math.h"

void setup() {
    HAL_Delay(1000);
    log_DMA_TX("sin cos test\r\n");
}

void loop() {
//    float shaftAngle = mt6701.GetRawAngle();
//    float fullAngle = mt6701.GetFullAngle();
//    float vel = mt6701.GetVelocity();
////    log_DMA_TX("[angle,fullAngle]:%f,%f\r\n", shaftAngle, fullAngle);
//    log_DMA_TX("vel:%f\r\n", vel);
    float a = arm_sin_f32(PI / 3);
    float b = arm_cos_f32(PI / 4);
    log_DMA_TX("[a,b]:%f,%f\r\n", a, b);
}
