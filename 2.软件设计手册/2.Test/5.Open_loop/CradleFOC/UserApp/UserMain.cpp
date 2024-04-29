//
// Created by User on 2024/4/29.
//

#include "UserMain.h"

void setup() {
    log_DMA_TX("c++ test\r\n");
}

void loop() {
    float shaftAngle = mt6701.GetRawAngle();
    float fullAngle = mt6701.GetFullAngle();
    float vel = mt6701.GetVelocity();
//    log_DMA_TX("[angle,fullAngle]:%f,%f\r\n", shaftAngle, fullAngle);
    log_DMA_TX("vel:%f\r\n", vel);
}
