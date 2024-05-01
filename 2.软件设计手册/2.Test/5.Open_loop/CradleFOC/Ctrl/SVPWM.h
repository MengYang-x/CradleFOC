//
// Created by User on 2024/4/29.
//

#ifndef CRADLEFOC_SVPWM_H
#define CRADLEFOC_SVPWM_H

extern float Ta, Tb, Tc;

void start_TIM_CHx();
void stop_TIM_CHx();
void setPhaseVoltage(float Uq, float Ud, float el_angle);

#endif //CRADLEFOC_SVPWM_H
