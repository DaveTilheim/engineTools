#include "PixelPicker.hpp"

using namespace se;


PixelPicker::PixelPicker(sf::Texture *txtr, int w, int h, RectEntity *host) : colorPickerTxtr(txtr), host(host)
{
	trace("PixelPicker creation");
	colorPickerTxtr->create(w, h);
}

sf::Vector2i PixelPicker::getCoordinates(int x, int y)
{
	auto pos = host->getTLPosition();
	x -= pos.x;
	y -= pos.y;
	sf::Image tmp = colorPickerTxtr->copyToImage();
	auto size = tmp.getSize();
	auto hsize = host->getSize();
	x *= (float)size.x / hsize.x;
	y *= (float)size.y / hsize.y;
	if(x < 0)
	{
		x = 0;
	}
	if(x >= size.x)
	{
		x = size.x-1;
	}
	if(y < 0)
	{
		y = 0;
	}
	if(y >= size.y)
	{
		y = size.y-1;
	}
	return sf::Vector2i(x, y);
}

sf::Color PixelPicker::getPickedValue() const
{
	return pickedValue;
}

void PixelPicker::setPickedValue(sf::Vector2i coo)
{
	pickedValue = getColorAt(coo);
}

void PixelPicker::setPickedValue(int x, int y)
{
	pickedValue = getColorAt(x, y);
}

sf::Color PixelPicker::getColorAt(sf::Vector2i mp)
{
	return getColorAt(mp.x, mp.y);
}

sf::Color PixelPicker::getColorAt(int x, int y)
{
	auto c = getCoordinates(x, y);
	return colorPickerTxtr->copyToImage().getPixel(c.x, c.y);
}
