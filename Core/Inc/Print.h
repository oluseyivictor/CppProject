/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Print.h
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

#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#include "stdint.h"
#include "stdio.h"
#include <string>
#include <string.h>

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

using namespace std;

namespace ngtech {

class Print
{
	private:
		int write_error;
		size_t printNumber(unsigned long, uint8_t);
		size_t printFloat(double, int);
	protected:
		void setWriteError(int err = 1) {write_error = err; }
	public:
		Print() {setWriteError(0); }     //Note the use of the constructor

		int getWriteError() {return write_error;}
		void clearWriteError() {setWriteError(0); }

		size_t write(uint8_t);    //pure virtual function ABC
		size_t write(const char *str) {
			if (str == NULL) return 0;
			return (write((const uint8_t*)str, strlen(str) ));
		}
		size_t write(const uint8_t* buffer, size_t size);
		size_t write(const char* buffer, size_t size) {
			return ( write ((const uint8_t*)buffer, size ) );
		}


	    size_t print(const string &);
	    size_t print(const char[]);
	    size_t print(char);
	    size_t print(unsigned char, int = DEC);
	    size_t print(int, int = DEC);
	    size_t print(unsigned int, int = DEC);
	    size_t print(long, int = DEC);
	    size_t print(unsigned long, int = DEC);
	    size_t print(long long, int = DEC);
	    size_t print(unsigned long long, int = DEC);
	    size_t print(double, int = 2);

	    size_t println(const string &s);
	    size_t println(const char[]);
	    size_t println(char);
	    size_t println(unsigned char, int = DEC);
	    size_t println(int, int = DEC);
	    size_t println(unsigned int, int = DEC);
	    size_t println(long, int = DEC);
	    size_t println(unsigned long, int = DEC);
	    size_t println(long long, int = DEC);
	    size_t println(unsigned long long, int = DEC);
	    size_t println(double, int = 2);
	    size_t println(void);
};

}




#endif /* INC_PRINT_H_ */
