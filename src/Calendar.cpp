#include "Calendar.hpp"


Calendar::Calendar()
{
	dataPin = GPIO_Pin_7;
	dataPinSource = GPIO_PinSource7;
	clockPin = GPIO_Pin_6;
	clockPinSource = GPIO_PinSource6;
	chipAddress = 0xD0;
	init();
}

void Calendar::init()
{
	initRCC();
	initGPIO();
	initI2C();
}

void Calendar::initRCC()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
}

void Calendar::initGPIO()
{
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Pin = clockPin | dataPin;
	GPIOStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIOStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIOStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIOStruct);

	GPIO_PinAFConfig(GPIOB, clockPinSource, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, dataPinSource, GPIO_AF_I2C1);
}

void Calendar::initI2C()
{
	I2C_InitTypeDef I2CStruct;
	I2CStruct.I2C_ClockSpeed = 100000;
	I2CStruct.I2C_Mode = I2C_Mode_I2C;
	I2CStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2CStruct.I2C_Ack = I2C_Ack_Disable;
	I2CStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2CStruct);

	I2C_Cmd(I2C1, ENABLE);
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}

uint8_t Calendar::decimalToBCD(uint8_t decimalNumber)
{
	return ((decimalNumber / 10) << 4) + (decimalNumber % 10);;
}

uint8_t Calendar::bcdToDecimal(uint8_t bcdNumber)
{
	return ((bcdNumber >> 4) * 10) + (bcdNumber & 0x0F);
}

TimeAndDate Calendar::getTimeAndDate()
{

}


