//
// Created by User on 2024/4/28.
//

#ifndef CRADLEFOC_SERIAL_H
#define CRADLEFOC_SERIAL_H

#include "stdint.h"
void log_DMA_TX(const char *format, ...);
void log_JustFloat_TX(uint8_t *txData, uint16_t size);

#endif //CRADLEFOC_SERIAL_H
