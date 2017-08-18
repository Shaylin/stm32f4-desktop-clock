#include "VectorText.hpp"
#include "VectorFontDefinition.hpp"
#include "math.h"

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
//TODO: cleanup and sort out case where there are vertices to the end of the array
//TODO: vertex count and vertex index is not the same damn thing
//TODO: these damn things also come out vertically flipped
void VectorText::drawGlyph(uint8_t xPos, uint8_t yPos, uint8_t glyphIndex)
{
	int* glyph = vectorFont[glyphIndex];
	uint8_t numberOfVertices = glyph[0];

	uint8_t vertexIndex = 2;
	uint8_t vertexCount = 0;
	while (vertexIndex - 2 < numberOfVertices)
	{
		int startX = glyph[vertexIndex];
		int startY = glyph[vertexIndex + 1];
		int endX = glyph[vertexIndex + 2];
		int endY = glyph[vertexIndex + 3];

		if (startX != -1 && endX != -1)
		{
			if (endX != -1 && endY != -1)
			{
				drawLine(startX, startY, endX, endY);
			}
			else
			{
				drawLine(startX, startY, startX, startY);
			}
		}
		vertexIndex += 2;
	}
}

void VectorText::drawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	int deltaX = endX - startX;

	if (deltaX == 0)
	{
		drawVerticalLine(startX, startY, endY);
	}
	else
	{
		drawDiagonalLine(startX, startY, endX, endY);
	}
}

void VectorText::drawDiagonalLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{

	int deltaX = abs(endX - startX);
	int signX = sign(endX - startX);
	int deltaY = abs(endY - startY);
	int signY = sign(endY - startY);
	int swapped = 0;

	int x = startX;
	int y = startY;

	if (deltaY > deltaX)
	{
		std::swap(deltaX, deltaY);
		swapped = 1;
	}

	int D = 2 * deltaY - deltaX;

	for (int i = 0; i < deltaX; i++)
	{
		screen.setPixel(x, y);
		while (D >= 0)
		{
			D -= 2 * deltaX;
			if (swapped)
			{
				x += signX;
			}
			else
			{
				y += signY;
			}
		}

		D += 2 * deltaY;
		if (swapped)
		{
			y += signY;
		}
		else
		{
			x += signX;
		}
	}
}

void VectorText::drawVerticalLine(uint8_t startX, uint8_t startY, uint8_t endY)
{
	if (endY - startY < 0)
	{
		uint8_t tempY = startY;
		startY = endY;
		endY = tempY;
	}
	for (uint8_t y = startY; y <= endY; y++)
	{
		screen.setPixel(startX, y);
	}
}

int VectorText::sign(int number)
{
	if (number > 0) return 1;
	if (number < 0) return -1;
	return 0;
}
