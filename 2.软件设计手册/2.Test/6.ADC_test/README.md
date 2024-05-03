引入FreeRTOS系统进行任务管理。

# 1. 定时器触发规则组+DMA采集电压

母线电压Udc、三相工作电压、MOS管温度、电位器调速，配置ADC的工作模式为：规则组+DMA。

ADC1：

| Pin Label | Pin Name | Alternate Function(s) |
| --------- | -------- | --------------------- |
| POT       | PA0      | ADC1_IN1              |
| MC        | PB12     | ADC1_IN11             |
| MA        | PB11     | ADC1_IN14             |

ADC2：

| Pin Label | Pin Name | Alternate Function(s) |
| --------- | -------- | --------------------- |
| Udc       | PC4      | ADC2_IN5              |
| NTC       | PB2      | ADC2_IN12             |
| MB        | PA4      | ADC2_IN17             |

## 1.1 STM32CubeMX配置



## 1.2 业务代码

# 2.定时器触发注入组采集相电流



## 2.1 STM32CubeMX配置

## 2.2 业务代码
