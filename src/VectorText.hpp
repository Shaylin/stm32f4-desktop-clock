#pragma once

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"
#include <string>

//TODO: The line drawing functionality must be its own class
class VectorText{
	private:
		uint8_t xPos;
		uint8_t yPos;
		uint8_t fontScale;
		std::string text;
		Oled screen;
		void drawGlyph(uint8_t xPos, uint8_t yPos, uint8_t glyphIndex, float fontScale);
		void drawVerticalLine(uint8_t startX, uint8_t startY, uint8_t endY);
		void drawDiagonalLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
		int sign(int number);

	public:
		VectorText(Oled screen);
		void setText(std::string text);
		void drawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
		void drawAt(uint8_t xPos, uint8_t yPos, float fontScale);
};
