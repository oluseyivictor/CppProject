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

#include <main.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Print.h"

extern UART_HandleTypeDef huart2;

using namespace ngtech;

size_t Print::write(const uint8_t *buffer, size_t size)
{
//	size_t n = 0;
//	while (size--) {
//		if (!HAL_UART_Transmit(&huart2, (uint8_t *)*buffer++, 1, 100)) n++;
//
//		else break;
//	}
//	return n;

	HAL_UART_Transmit(&huart2, buffer, size, 100);
	return 0;
}



size_t Print::print(const char buffer)
{
	return write(buffer);
}



size_t Print::print(const string & buffer)
{
	return write((uint8_t *)buffer.c_str(), buffer.length() );
}



size_t Print::print(const char buffer[])
{
	return write(buffer);
}


size_t Print::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

size_t Print::print(int n, int base)
{
  return print((long) n, base);
}



size_t Print::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}



size_t Print::print(long n, int base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}



size_t Print::print(unsigned long n, int base)
{
  if (base == 0) return write(n);
  else return printNumber(n, base);
}



//size_t Print::print(long long n, int base)
//{
//  if (base == 0) {
//    return write(n);
//  } else if (base == 10) {
//    if (n < 0) {
//      int t = print('-');
//      n = -n;
//      return printULLNumber(n, 10) + t;
//    }
//    return printULLNumber(n, 10);
//  } else {
//    return printULLNumber(n, base);
//  }
//}
//
//
//
//size_t Print::print(unsigned long long n, int base)
//{
//  if (base == 0) return write(n);
//  else return printULLNumber(n, base);
//}



size_t Print::print(double n, int digits)
{
  return printFloat(n, digits);
}


size_t Print::println(void)
{
  return write("\r\n");
}

size_t Print::println(const string &s)
{
  size_t n = print(s);
  n += println();
  return n;
}

size_t Print::println(const char c[])
{
  size_t n = print(c);
  n += println();
  return n;
}


size_t Print::println(char c)
{
  size_t n = print(c);
  n += println();
  return n;
}


size_t Print::println(unsigned char b, int base)
{
  size_t n = print(b, base);
  n += println();
  return n;
}


size_t Print::println(int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}


size_t Print::println(unsigned int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}


size_t Print::println(long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}


size_t Print::println(unsigned long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}


size_t Print::println(long long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}


size_t Print::println(unsigned long long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}


size_t Print::println(double num, int digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}


size_t Print::printFloat(double number, int digits)
{
  if (digits < 0)
    digits = 2;

  size_t n = 0;

  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically

  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print(".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)remainder;
    n += print(toPrint);
    remainder -= toPrint;
  }

  return n;
}


size_t Print::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return write(str);
}
