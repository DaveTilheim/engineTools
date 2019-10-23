#include "ColorPicker.hpp"

using namespace se;

ColorPicker::ColorPicker(float x, float y, Application *root, const sf::Color& color)
: Widget(x, y, 255, 255, root)
{
	colorPickerTxtr = new sf::Texture();
	colorPickerTxtr->create(256, 256);
	addTexture("_basic_color_picker0x0", colorPickerTxtr);
	setTexture("_basic_color_picker0x0");
	trace("ColorPicker created");
	setMainColor(color);
}

ColorPicker::~ColorPicker()
{
	trace("ColorPicker deleted");
}

sf::Color ColorPicker::getColorAt(sf::Vector2i mp)
{
	return getColorAt(mp.x, mp.y);
}

sf::Color ColorPicker::getColorAt(int x, int y)
{
	auto pos = getTLPosition();
	x -= pos.x;
	y -= pos.y;
	sf::Image tmp = colorPickerTxtr->copyToImage();
	x *= (float)tmp.getSize().x / getSize().x;
	y *= (float)tmp.getSize().y / getSize().y;
	if(x < 0 or x > 255) return sf::Color(0,0,0);
	if(y < 0 or y > 255) return sf::Color(0,0,0);
	return colorPickerTxtr->copyToImage().getPixel(x, y);
}

void ColorPicker::setMainColor(const sf::Color& color)
{
	sf::Image img = colorPickerTxtr->copyToImage();
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			int r, g, b;
			r = color.r + (255 - j);
			if(r > 255) r = 255;
			r *= ((255 - i) / 255.0);
			g = color.g + (255 - j);
			if(g > 255) g = 255;
			g *= ((255 - i) / 255.0);
			b = color.b + (255 - j);
			if(b > 255) b = 255;
			b *= ((255 - i) / 255.0);
			img.setPixel(j, i, sf::Color(r, g, b));
		}
	}
	colorPickerTxtr->update(img);
}

sf::Color ColorPicker::getPickedValue() const
{
	return pickedValue;
}
