#include "Graphics.hpp"

Graphics::Graphics() {}

Graphics::Graphics(Oled screen)
{
	this -> screen = screen;
}

void Graphics::drawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	if (endX - startX == 0)
	{
		drawVerticalLine(startX, startY, endY);
	}
	else
	{
		drawDiagonalLine(startX, startY, endX, endY);
	}
}

void Graphics::drawDiagonalLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	int deltaX = abs(endX - startX);
	int signX = sign(endX - startX);
	int deltaY = abs(endY - startY);
	int signY = sign(endY - startY);
	bool gradientGreaterThanOne = false;

	int x = startX;
	int y = startY;

	if (deltaY > deltaX)
	{
		std::swap(deltaX, deltaY);
		gradientGreaterThanOne = true;
	}

	int D = 2 * deltaY - deltaX;

	for (int i = 0; i < deltaX; i++)
	{
		screen.setPixel(x, y);
		while (D >= 0)
		{
			D -= 2 * deltaX;
			if (gradientGreaterThanOne)
			{
				x += signX;
			}
			else
			{
				y += signY;
			}
		}

		D += 2 * deltaY;
		if (gradientGreaterThanOne)
		{
			y += signY;
		}
		else
		{
			x += signX;
		}
	}
}

void Graphics::drawVerticalLine(uint8_t startX, uint8_t startY, uint8_t endY)
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

int Graphics::sign(int number)
{
	if (number > 0) return 1;
	if (number < 0) return -1;
	return 0;
}
