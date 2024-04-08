# HAL库

DMA发送不定长数据：

```c
#include <stdio.h>
#include "usart.h"
#include <string.h>
#include <stdarg.h>

/*
 * @brief DMA方式发送数据
 */
void log_DMA_TX(const char *format, ...)
{
	va_list args;			// 定义参数列表变量
	va_start(args, format); // 从format位置开始接收参数表，放在arg里面

	char strBuf[256];				// 定义输出的字符串
	vsprintf(strBuf, format, args); // 使用vsprintf将格式化的数据写入缓冲区
	va_end(args);					// 结束可变参数的使用

	// 等待上次的数据发送完成，避免新的数据覆盖正在传输的数据，导致混乱
	while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX)
	{
		// Wait for DMA transfer to complete
	}

	HAL_UART_Transmit_DMA(&huart1, (uint8_t *)strBuf, strlen(strBuf));
}
```

封装`JustFloat`协议：

```
/*
 * @brief 使用JustFloat协议发送浮点数据
 * @param txData 数据缓冲区的指针
 * @param size 数据缓存区的大小，单位字节
 * @note 使用UART_DMA发送数据
 */
void log_JustFloat_TX(uint8_t *txData, uint16_t size)
{
	static uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f}; // 帧尾数据

	HAL_UART_Transmit_DMA(&huart1, txData, size); // 发送缓冲区的数据

	while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX)
	{
		// Wait for DMA transfer to complete
	}

	HAL_UART_Transmit_DMA(&huart1, (uint8_t *)tail, 4); // 发送帧尾数据
}
```

# LL库

```c
```

