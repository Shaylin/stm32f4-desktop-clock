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
	GPIOStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIOStruct);

	GPIO_PinAFConfig(GPIOB, clockPinSource, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, dataPinSource, GPIO_AF_I2C1);
}

void Calendar::initI2C()
{
	I2C_InitTypeDef I2CStruct;
	I2CStruct.I2C_ClockSpeed = 400000;
	I2CStruct.I2C_Mode = I2C_Mode_I2C;
	I2CStruct.I2C_OwnAddress1 = 0x01;
	I2CStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2CStruct.I2C_Ack = I2C_Ack_Enable;
	I2CStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2CStruct);
	I2C_Cmd(I2C1, ENABLE);
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
	TimeAndDate timeAndDate;

	startTransmission();

	I2C_SendData(I2C1 ,0x00);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, chipAddress, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	timeAndDate = receiveTimeAndDate();

	stopTransmission();

	return timeAndDate;
}

TimeAndDate Calendar::receiveTimeAndDate()
{
	TimeAndDate timeAndDate;

	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.seconds = bcdToDecimal(I2C_ReceiveData(I2C1));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.minutes = bcdToDecimal(I2C_ReceiveData(I2C1));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.hours = bcdToDecimal(I2C_ReceiveData(I2C1));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.dayOfWeek = bcdToDecimal(I2C_ReceiveData(I2C1));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.date = bcdToDecimal(I2C_ReceiveData(I2C1));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.month = bcdToDecimal(I2C_ReceiveData(I2C1));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	timeAndDate.year = bcdToDecimal(I2C_ReceiveData(I2C1));

	return timeAndDate;
}

void Calendar::setTimeAndDate(TimeAndDate timeAndDate)
{
	startTransmission();

	I2C_SendData(I2C1, 0x00);
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	sendTimeAndDate(timeAndDate);

	stopTransmission();
}

void Calendar::sendTimeAndDate(TimeAndDate timeAndDate)
{
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.seconds));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.minutes));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.hours));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.dayOfWeek));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.date));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.month));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, decimalToBCD(timeAndDate.year));
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

void Calendar::startTransmission()
{
	I2C_AcknowledgeConfig(I2C1,ENABLE);

	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, chipAddress, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}


void Calendar::stopTransmission()
{
	I2C_AcknowledgeConfig(I2C1 ,DISABLE);

	I2C_GenerateSTOP(I2C1, ENABLE);
}

uint8_t Calendar::getTemperature()
{
	startTransmission();

	I2C_SendData(I2C1, 0x11);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, chipAddress, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	uint8_t temperature = I2C_ReceiveData(I2C1);

	stopTransmission();

	return temperature;
}

