#pragma once

#include "VectorFontDefinition.hpp"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"
#include <string>

class VectorText{
	private:
		uint8_t xPos;
		uint8_t yPos;
		uint8_t fontScale;
		std::string text;
		Oled screen;
		void drawGlyph(uint8_t xPos, uint8_t yPos, uint8_t glyphIndex);
		void drawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
		void drawVerticalLine(uint8_t startX, uint8_t startY, uint8_t endY);
	public:
		VectorText(Oled screen);
		void setText(std::string text);
		void drawAt(uint8_t xPos, uint8_t yPos, uint8_t fontScale);
};
