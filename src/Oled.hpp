#include "stm32f4xx.h"
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
		void delayMS();
		void startupSequence();
	public:
		Oled();
		~Oled();
		void init();
};
