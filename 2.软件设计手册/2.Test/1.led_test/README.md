# 功能

LL库输出高低电平：

```c
 LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);  // 输出低电平
 LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);  // 输出高电平
```

板载自定义LED闪烁：

```c
    LL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    LL_mDelay(100);
    LL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    LL_mDelay(100);
```

