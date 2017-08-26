#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"
#include "math.h"
#include <string>

class Graphics{
	private:
		Oled screen;
		void drawVerticalLine(uint8_t startX, uint8_t startY, uint8_t endY);
		void drawDiagonalLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
		int sign(int number);

	public:
		Graphics();
		Graphics(Oled screen);
		void drawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
};
