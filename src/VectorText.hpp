#pragma once

#include "Oled.hpp"
#include "Graphics.hpp"
#include "math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <string>

//TODO: VectorText should extend graphics maybe
class VectorText{
	private:
		uint8_t xPos;
		uint8_t yPos;
		uint8_t fontScale;
		std::string text;
		Graphics graphics;
		Oled screen;
		void drawGlyph(uint8_t xPos, uint8_t yPos, uint8_t glyphIndex, float fontScale);

	public:
		VectorText(Oled screen);
		void setText(std::string text);
		void drawAt(uint8_t xPos, uint8_t yPos, float fontScale);
};
