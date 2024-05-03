//
// Created by User on 2024/5/3.
//

#ifndef CRADLEFOC_OS_TIME_UTILS_H
#define CRADLEFOC_OS_TIME_UTILS_H

#include "stdint.h"

void delay(uint32_t ms);

void delayMicroseconds(uint32_t us);

uint64_t micros();

uint32_t millis();

#endif //CRADLEFOC_OS_TIME_UTILS_H
