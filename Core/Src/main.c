/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "cmsis_os.h"

osThreadId Task1Handle;
osThreadId Task2Handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void Task1_Entry(void const * argument);
void Task2_Entry(void const * argument);

int main(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                     // Enable GPIOC
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);      // Clear MODE13, CNF13
    GPIOC->CRH |=  GPIO_CRH_MODE13_1;                       // Output mode 2 MHz

    osThreadDef(Task2, Task2_Entry, osPriorityNormal, 0, 128);
    Task2Handle = osThreadCreate(osThread(Task2), NULL);

    osThreadDef(Task1, Task1_Entry, osPriorityNormal, 0, 128);
    Task1Handle = osThreadCreate(osThread(Task1), NULL);

    osKernelStart();

    while (1)
    {
    }
}

void Task1_Entry(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  osDelay(1);
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    osDelay(3000);
  }
  /* USER CODE END 5 */
}

void Task2_Entry(void const * argument)
{
  /* USER CODE BEGIN Task2_Entry */
  /* Infinite loop */
  for(;;)
  {
    GPIOC->ODR |= GPIO_ODR_ODR13;
    osDelay(50);
  }
  /* USER CODE END Task2_Entry */
}
