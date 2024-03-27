# 项目开发LOG

- [ ] 20224年3月23日：立项，起名为“摇篮FOC”，英文“CradleFOC”。
- [ ] 2024年3月24日：开始设计CradleFOC硬件原理图

# 1. CradleFOC简介

添加主控的渲染图

- 主控：STM32G431CBU6，晶振24MHz，通过时钟分频倍频配置，设置MCU的工作频率为170MHz。

- 电流采样电阻0.01Ω，1206封装，功率1W，最大电流10A，所以工作电流要小于10A。
- 三相电流采样，采用MCU内部的OPA运放，进一步减小设计成本。

# 2. 工作电源



# 3. GPIO分配

STM32CubeMX引脚配置图：



## 3.1 SWD&USART引脚

| SWDIO | SWCLK | USART1_TX | USART1_RX |
| ----- | ----- | --------- | --------- |
| PA13  | PA14  | PB6       | PB7       |

## 3.2 PWM输出引脚

| Pin Label | Pin Name | Alternate Function(s) |
| --------- | -------- | --------------------- |
| IN1       | PA8      | TIM1_CH1              |
| IN2       | PA9      | TIM1_CH2              |
| IN3       | PA10     | TIM1_CH3              |

