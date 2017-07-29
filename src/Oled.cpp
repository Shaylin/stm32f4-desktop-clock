#include "Oled.hpp"

Oled::Oled()
{
	dataPin = GPIO_Pin_0;
	clockPin = GPIO_Pin_0;
	dataCommandPin = GPIO_Pin_0;
	chipSelectPin = GPIO_Pin_0;
	resetPin = GPIO_Pin_0;

	gpioPort = GPIOA;

	screenWidth = 128;
	screenHeight = 64;
	screenBuffer = new uint8_t[screenWidth * screenHeight];
}

Oled::~Oled()
{
	delete[] screenBuffer;
}

void Oled::init()
{
	initRCC();
}


void Oled::initRCC()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI1EN, ENABLE);
}

void Oled::initGPIO()
{
	GPIO_InitTypeDef GPIOStruct;
}
