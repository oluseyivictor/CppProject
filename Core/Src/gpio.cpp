/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : gpio.cpp
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Victor.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "gpio.h"


GPIO::GPIO(GPIO_TypeDef* port, uint16_t Pin, Direction Dir) : gpio_port(port), gpio_pin(Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};


  /*Configure GPIO pin : PC8 */
    GPIO_InitStruct.Pin = Pin;
    if (Dir == IN)
    {
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    }
    else
    {
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    }
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);

}

void GPIO::digitalWrite(const bool state)
{
    if (state == LOW)
   HAL_GPIO_WritePin(gpio_port,gpio_pin, GPIO_PIN_RESET);
   else{
    HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_SET);
   }
}

const bool GPIO::digitalRead(void)
{
	bool readValue;
	readValue = HAL_GPIO_ReadPin(gpio_port, gpio_pin);
	return readValue;
}

GPIO::~GPIO()
{
}
