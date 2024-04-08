#include <stdio.h>
#include "usart.h"
#include <string.h>
#include <stdarg.h>

/*
 * @brief 轮询阻塞方式发送数据
 */
void log_block_TX(const char *format, ...)
{
    va_list args;           // 定义参数列表变量
    va_start(args, format); // 从format位置开始接收参数表，放在arg里面

    char strBuf[256];               // 定义输出的字符串
    vsprintf(strBuf, format, args); // 使用vsprintf将格式化的数据写入缓冲区
    va_end(args);                   // 结束可变参数的使用

    // 使用LL库逐个发送字符串中的每个字符
    uint16_t index = 0;
    while (strBuf[index] != '\0')
    {
        LL_USART_TransmitData8(USART1, (uint8_t)strBuf[index]);
        index++;
        while (!LL_USART_IsActiveFlag_TXE(USART1))
        {
            // 等待发送数据完成
        }
    }
    while (!LL_USART_IsActiveFlag_TC(USART1))
        ; // 等待传输完成
}

///////////////////////////////////////////////////////////////////////////////////
void debug_init(void)
{
    // DMA发送配置
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&(USART1->TDR));
    LL_USART_EnableDMAReq_TX(USART1);           // 使能DMA串口发送
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1); // 使能DMA发送完成中断
}

void UART_DMA_Send(USART_TypeDef *USARTx, uint8_t *str, uint16_t size)
{
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)str); // 配置内存地址
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, size);             // 配置数据长度
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);                   // 使能DMA通道，也就是发送数据
}

// DMA发送函数封装
void log_DMA_TX(const char *format, ...)
{
    va_list args;           // 定义参数列表变量
    va_start(args, format); // 从format位置开始接收参数表，放在arg里面

    char strBuf[256];               // 定义输出的字符串
    vsprintf(strBuf, format, args); // 使用vsprintf将格式化的数据写入缓冲区
    va_end(args);                   // 结束可变参数的使用

    UART_DMA_Send(USART1, (uint8_t *)strBuf, strlen(strBuf));
}
