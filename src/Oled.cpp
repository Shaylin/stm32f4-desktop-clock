#include "Oled.hpp"

Oled::Oled()
{
	dataPin = GPIO_Pin_7;
	dataPinSource = GPIO_PinSource7;
	clockPin = GPIO_Pin_5;
	clockPinSource = GPIO_PinSource5;
	dataCommandPin = GPIO_Pin_1;
	chipSelectPin = GPIO_Pin_0;
	resetPin = GPIO_Pin_3;

	gpioPort = GPIOA;

	screenWidth = 128;
	screenHeight = 64;
	screenBuffer = new uint8_t[screenWidth * screenHeight / 8];
}

Oled::~Oled()
{
	delete[] screenBuffer;
}

void Oled::init()
{
	initRCC();
	initGPIO();
	initSPI();
	runStartupSequence();
}

void Oled::initRCC()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI1EN, ENABLE);
}

void Oled::initGPIO()
{
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Pin = dataCommandPin | resetPin | chipSelectPin;
	GPIOStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOStruct.GPIO_OType = GPIO_OType_PP;
	GPIOStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(gpioPort, &GPIOStruct);

	GPIOStruct.GPIO_Pin = dataPin | clockPin;
	GPIOStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(gpioPort, &GPIOStruct);
	GPIO_PinAFConfig(gpioPort, dataPinSource, GPIO_AF_SPI1);
	GPIO_PinAFConfig(gpioPort, clockPinSource, GPIO_AF_SPI1);
}

void Oled::initSPI()
{
	SPI_InitTypeDef SPIStruct;
	SPIStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPIStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPIStruct.SPI_CPOL = SPI_CPOL_Low;
	SPIStruct.SPI_DataSize = SPI_DataSize_8b;
	SPIStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPIStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPIStruct.SPI_Mode = SPI_Mode_Master;
	SPIStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &SPIStruct);
	SPI_Cmd(SPI1, ENABLE);
}

void Oled::sendDataByte(uint8_t data)
{
	GPIO_SetBits(gpioPort, dataCommandPin);
	GPIO_ResetBits(gpioPort, chipSelectPin);

	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	GPIO_SetBits(gpioPort, chipSelectPin);
}

void Oled::sendCommandByte(uint8_t command)
{
	GPIO_ResetBits(gpioPort, dataCommandPin);
	GPIO_ResetBits(gpioPort, chipSelectPin);

	SPI_I2S_SendData(SPI1, command);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	GPIO_SetBits(gpioPort, chipSelectPin);
}

void Oled::refresh()
{
	for (int byteIndex = 0; byteIndex < screenWidth * screenHeight / 8; byteIndex++)
	{
		sendDataByte(screenBuffer[byteIndex]);
	}
}

void Oled::clear()
{
	for (int byteIndex = 0; byteIndex < screenWidth * screenHeight / 8; byteIndex++)
	{
		screenBuffer[byteIndex] = 0x00;
	}
}

void Oled::setPixel(uint8_t x, uint8_t y)
{
	screenBuffer[x + (y / 8 * screenWidth)] |= 1 << (y % 8);
}

void Oled::clearPixel(uint8_t x, uint8_t y)
{

}

void Oled::runStartupSequence()
{
	GPIO_ResetBits(gpioPort, dataCommandPin | chipSelectPin | resetPin);
	delayMS(1);
	GPIO_SetBits(gpioPort, resetPin);
	delayMS(1);
	GPIO_ResetBits(gpioPort, resetPin);
	delayMS(1);
	GPIO_SetBits(gpioPort, dataCommandPin | chipSelectPin | resetPin);

	sendCommandByte(0xA8);
	sendCommandByte(0x3F);
	sendCommandByte(0xD3);
	sendCommandByte(0x00);
	sendCommandByte(0x40);
	sendCommandByte(0xA1);
	sendCommandByte(0xDA);
	sendCommandByte(0x12);
	sendCommandByte(0xC8);
	sendCommandByte(0x81);
	sendCommandByte(0xFF);
	sendCommandByte(0x20);
	sendCommandByte(0x00);
	sendCommandByte(0x21);
	sendCommandByte(0x00);
	sendCommandByte(0x7F);
	sendCommandByte(0x22);
	sendCommandByte(0x00);
	sendCommandByte(0x07);
	sendCommandByte(0xA6);
	sendCommandByte(0xDB);
	sendCommandByte(0x40);
	sendCommandByte(0xA4);
	sendCommandByte(0xD5);
	sendCommandByte(0x80);
	sendCommandByte(0x8D);
	sendCommandByte(0x14);
	sendCommandByte(0xAF);
}

uint8_t Oled::getScreenWidth()
{
	return screenWidth;
}

uint8_t Oled::getScreenHeight()
{
	return screenHeight;
}
