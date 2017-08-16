#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"

class Oled{
	private:
		uint8_t screenWidth;
		uint8_t screenHeight;
		uint8_t* screenBuffer;
		uint16_t dataPin;
		uint16_t dataPinSource;
		uint16_t clockPin;
		uint16_t clockPinSource;
		uint16_t dataCommandPin;
		uint16_t chipSelectPin;
		uint16_t resetPin;
		GPIO_TypeDef* gpioPort;
		void initRCC();
		void initGPIO();
		void initSPI();
		void sendDataByte(uint8_t data);
		void sendCommandByte(uint8_t command);
		void runStartupSequence();
	public:
		Oled();
		~Oled();
		void init();
		void refresh();
		void clear();
		void setContrast(uint8_t contrast);
		void setPixel(uint8_t x, uint8_t y);
		void clearPixel(uint8_t x, uint8_t y);
		uint8_t getScreenWidth();
		uint8_t getScreenHeight();
};
