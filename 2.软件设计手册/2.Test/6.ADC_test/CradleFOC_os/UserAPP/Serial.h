//
// Created by User on 2024/5/3.
//

#ifndef CRADLEFOC_OS_SERIAL_H
#define CRADLEFOC_OS_SERIAL_H

#include "stdint.h"

/*
 * 条件编译指令
 * 1; 开启串口输出; 0; 关闭串口输出
 * 注意: 只能有一个为1
 */
#define LOG_Stack 0
#define LOG_Duty 0
#define LOG_Current 0
#define LOG_ADC 1
#define LOG_FOC 0
#define LOG_MT6701 0

void log_DMA_TX(const char *format, ...);

void log_JustFloat_TX(uint8_t *txData, uint16_t size);



#endif //CRADLEFOC_OS_SERIAL_H
