//
// Created by User on 2024/5/3.
//

#ifndef CRADLEFOC_OS_SVPWM_H
#define CRADLEFOC_OS_SVPWM_H

void start_TIM_CHx();
void stop_TIM_CHx();
void setPhaseVoltage(float Uq, float Ud, float el_angle);

#endif //CRADLEFOC_OS_SVPWM_H
