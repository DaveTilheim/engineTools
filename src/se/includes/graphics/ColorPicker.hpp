#ifndef COLOR_PICKER_HPP
#define COLOR_PICKER_HPP
#include "Widget.hpp"

namespace se
{
	class ColorPicker : public Widget
	{
	protected:
		sf::Color pickedValue;
		sf::Texture *colorPickerTxtr;
	public:
		ColorPicker(float x, float y, Application *root, const sf::Color&color=sf::Color(255,0,0));
		virtual ~ColorPicker();
		sf::Color getPickedValue() const;
		void setMainColor(const sf::Color&);
		sf::Color getColorAt(sf::Vector2i);
		sf::Color getColorAt(int x, int y);
	};
}

#endif
