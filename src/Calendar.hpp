#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"

struct TimeAndDate
{
	uint8_t seconds;
	uint8_t hours;
	uint8_t minutes;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

class Calendar
{
	private:
		uint16_t dataPin;
		uint16_t dataPinSource;
		uint16_t clockPin;
		uint16_t clockPinSource;
		uint8_t chipAddress;
		void initRCC();
		void initGPIO();
		void initI2C();
		uint8_t decimalToBCD(uint8_t decimalNumber);
		uint8_t bcdToDecimal(uint8_t bcdNumber);
		void sendTimeAndDate(TimeAndDate timeAndDate);
		TimeAndDate receiveTimeAndDate();
	public:
		Calendar();
		void init();
		TimeAndDate getTimeAndDate();
		void setTimeAndDate(TimeAndDate timeAndDate);
};
