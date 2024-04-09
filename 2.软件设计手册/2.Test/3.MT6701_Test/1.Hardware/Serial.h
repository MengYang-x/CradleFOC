#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdint.h>

void log_DMA_TX(const char *format, ...);
void log_JustFloat_TX(uint8_t *txData, uint16_t size);

#endif
