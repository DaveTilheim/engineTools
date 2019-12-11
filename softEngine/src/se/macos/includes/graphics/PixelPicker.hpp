#ifndef PIXEL_PICKER_HPP
#define PIXEL_PICKER_HPP
#include "RectEntity.hpp"

namespace se
{
	class PixelPicker
	{
	protected:
		sf::Color pickedValue;
		sf::Texture *colorPickerTxtr;
		RectEntity *host;
		sf::Vector2i getCoordinates(int x, int y);
	public:
		PixelPicker(sf::Texture *, int w, int h, RectEntity *host);
		sf::Color getPickedValue() const;
		sf::Color getColorAt(sf::Vector2i);
		sf::Color getColorAt(int x, int y);
		void setPickedValue(sf::Vector2i);
		void setPickedValue(int x, int y);
	};
}

#endif
