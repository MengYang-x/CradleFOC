/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "UserAPP.h"
#include "Serial.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02_LOGHandle;
osThreadId myTask03_KEYHandle;
osThreadId myTask04_FOCHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void FOC_LOG(void const * argument);
void KEY_USER(void const * argument);
void FOC(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    setup();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 64);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02_LOG */
  osThreadDef(myTask02_LOG, FOC_LOG, osPriorityLow, 0, 300);
  myTask02_LOGHandle = osThreadCreate(osThread(myTask02_LOG), NULL);

  /* definition and creation of myTask03_KEY */
  osThreadDef(myTask03_KEY, KEY_USER, osPriorityLow, 0, 64);
  myTask03_KEYHandle = osThreadCreate(osThread(myTask03_KEY), NULL);

  /* definition and creation of myTask04_FOC */
  osThreadDef(myTask04_FOC, FOC, osPriorityBelowNormal, 0, 200);
  myTask04_FOCHandle = osThreadCreate(osThread(myTask04_FOC), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_FOC_LOG */
/**
* @brief Function implementing the myTask02_LOG thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FOC_LOG */
void FOC_LOG(void const * argument)
{
  /* USER CODE BEGIN FOC_LOG */
    /* Infinite loop */
    for (;;) {
        task_log();
        osDelay(1);
    }
  /* USER CODE END FOC_LOG */
}

/* USER CODE BEGIN Header_KEY_USER */
/**
* @brief Function implementing the myTask03_KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KEY_USER */
void KEY_USER(void const * argument)
{
  /* USER CODE BEGIN KEY_USER */
    /* Infinite loop */
    for (;;) {
        task_key();
        osDelay(1);
    }
  /* USER CODE END KEY_USER */
}

/* USER CODE BEGIN Header_FOC */
/**
* @brief Function implementing the myTask04_FOC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FOC */
void FOC(void const * argument)
{
  /* USER CODE BEGIN FOC */
    /* Infinite loop */
    for (;;) {
        task_FOC();
        osDelay(1);
    }
  /* USER CODE END FOC */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

