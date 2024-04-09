#include "spi.h"
#include <stdint.h>
#include "Serial.h"

#define MT6701_CS_Enable() HAL_GPIO_WritePin(MT6701_CS_GPIO_Port, MT6701_CS_Pin, GPIO_PIN_RESET)
#define MT6701_CS_Disable() HAL_GPIO_WritePin(MT6701_CS_GPIO_Port, MT6701_CS_Pin, GPIO_PIN_SET)

/**
 * @brief MT6701编码器绝对值角度读取
 * @retval 机械角度
 */
float MT6701_GetRawAngle(void)
{
    uint16_t rawData;

    MT6701_CS_Enable();

    HAL_StatusTypeDef spiStatus = HAL_SPI_Receive(&hspi1, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);
    if (spiStatus != HAL_OK)
    {
        MT6701_CS_Disable();
        log_DMA_TX("MT6701 read data error!\r\n");
        return 0; // 在SPI传输错误时直接返回，避免继续执行后续代码
    }

    MT6701_CS_Disable();

    float angle = (float)(rawData >> 2) / 16384.0f * 6.283185308f;
    return angle; // 绝对值角度数据：0~2Π
}
