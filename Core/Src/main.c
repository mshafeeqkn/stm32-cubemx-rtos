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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include <stddef.h>
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void Task1_Entry(void* argument);
void Task2_Entry(void* argument);

int main(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                     // Enable GPIOC
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);      // Clear MODE13, CNF13
    GPIOC->CRH |=  GPIO_CRH_MODE13_1;                       // Output mode 2 MHz

    xTaskCreate(Task2_Entry, "LEDOFF", 128, NULL, 1, NULL);
    xTaskCreate(Task1_Entry, "LEDON", 128, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1)
    {
    }
}

void Task1_Entry(void* argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  vTaskDelay(pdMS_TO_TICKS(1));
  for(;;)
  {
    GPIOC->ODR &= ~GPIO_ODR_ODR13;
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
  /* USER CODE END 5 */
}

void Task2_Entry(void* argument)
{
  /* USER CODE BEGIN Task2_Entry */
  /* Infinite loop */
  for(;;)
  {
    GPIOC->ODR |= GPIO_ODR_ODR13;
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  /* USER CODE END Task2_Entry */
}
