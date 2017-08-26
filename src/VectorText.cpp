#include "VectorText.hpp"
#include "VectorFontDefinition.hpp"


VectorText::VectorText(Oled screen)
{
	this -> screen = screen;
	this -> graphics = Graphics(screen);
}

void VectorText::setText(std::string text)
{
	this -> text = text;
}

void VectorText::drawAt(uint8_t xPos, uint8_t yPos, float fontScale = 1)
{
	for (uint8_t characterIndex = 0; characterIndex < text.length(); characterIndex++)
	{
		char character = text[characterIndex];
		uint8_t glyphIndex = character - 32;

		drawGlyph(xPos, yPos, glyphIndex, fontScale);

		uint8_t glyphWidth = vectorFont[glyphIndex][1];
		xPos += glyphWidth * fontScale;
	}
}

void VectorText::drawGlyph(uint8_t xPos, uint8_t yPos, uint8_t glyphIndex, float fontScale)
{
	int* glyph = vectorFont[glyphIndex];
	int glpyhHeight = vectorFontHeight;
	int numberOfVertices = glyph[0];
	int vertexIndex = 2;
	int vertexCount = 0;

	while (vertexCount < numberOfVertices)
	{
		int startX = glyph[vertexIndex];
		int startY = glyph[vertexIndex + 1];
		int endX = glyph[vertexIndex + 2];
		int endY = glyph[vertexIndex + 3];

		if (startX != -1 && startY != -1 && endX != -1 && endY != -1)
		{

			startX = startX * fontScale + xPos;
			startY = (glpyhHeight - startY) * fontScale + yPos;
			endX = endX * fontScale + xPos;
			endY = (glpyhHeight - endY) * fontScale + yPos;

			graphics.drawLine(startX, startY, endX, endY);
		}

		vertexCount ++;
		vertexIndex += 2;
	}
}
