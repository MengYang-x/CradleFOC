#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdint.h>

void log_block_TX(const char *format, ...);
void debug_init(void);
void log_DMA_TX(const char *format, ...);
#endif
