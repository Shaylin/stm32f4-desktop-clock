#include "VectorText.hpp"

VectorText::VectorText(Oled screen)
{
	this -> screen = screen;
}

void VectorText::setText(std::string text)
{
	this -> text = text;
}

void VectorText::drawAt(uint8_t xPos, uint8_t yPos, uint8_t fontScale = 1)
{
	for (uint8_t characterIndex = 0; characterIndex < text.length(); characterIndex++)
	{
		char character = text[characterIndex];
		uint8_t glyphIndex = character - 32;

		drawGlyph(xPos, yPos, glyphIndex);

		uint8_t glyphWidth = vectorFont[glyphIndex][1];
		xPos += glyphWidth;
	}
}

void VectorText::drawGlyph(uint8_t xPos, uint8_t yPos, uint8_t glyphIndex)
{
	uint8_t numberOfVertices = vectorFont[glyphIndex][0];

	uint8_t vertexIndex = 2;
	while (vertexIndex - 2 < numberOfVertices)
	{
		int vertexXPos = vectorFont[glyphIndex][vertexIndex];
		int vertexYPos = vectorFont[glyphIndex][vertexIndex + 1];

		if (vertexXPos != -1 && vertexYPos != -1)
		{
			uint8_t pixelX = xPos + vertexXPos;
			uint8_t pixelY = yPos + vertexYPos;

		}

		vertexIndex += 2;
	}
}

void drawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{

}
