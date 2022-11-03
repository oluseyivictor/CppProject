/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : gpio.h
  * @brief          : Header for gpio.c file.
  *                   This file contains the common defines of the gpio application.
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

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l4xx_hal.h"
#include "stdint.h"

   enum Direction {IN, OUT};
   enum LOGIC {LOW, HIGH};

class GPIO
{

protected:
    /* data */
	   GPIO_TypeDef* gpio_port;
	   uint16_t gpio_pin;
public:

    GPIO(GPIO_TypeDef* port, uint16_t Pin, Direction Dir = OUT);
    ~GPIO();

    //Public function
    void digitalWrite(const bool state = LOW);
    const bool digitalRead(void);

};

#endif
