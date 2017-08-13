#include "Oled.hpp"

Oled::Oled()
{
	dataPin = GPIO_Pin_0;
	dataPinSource = GPIO_PinSource0;
	clockPin = GPIO_Pin_0;
	clockPinSource = GPIO_PinSource0;
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
	initGPIO();
	initSPI();
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

void Oled::delayMS()
{

}

void Oled::startupSequence()
{

}
