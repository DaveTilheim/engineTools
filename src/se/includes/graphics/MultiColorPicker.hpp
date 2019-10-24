#ifndef MULTI_COLOR_PICKER_HPP
#define MULTI_COLOR_PICKER_HPP
#include "LinkedEntity.hpp"
#include "ColorPicker.hpp"
#include "Slider.hpp"

namespace se
{
	class MultiColorPicker : public LinkedEntity<ColorPicker>
	{
	protected:
		unsigned char redValue = 127;
		unsigned char greenValue = 127;
		unsigned char blueValue = 127;
		void updateColor();
	public:
		MultiColorPicker(float x, float y, Application *root, const sf::Color&color=sf::Color(255,0,0));
		unsigned char getRedValue() const;
		unsigned char getGreenValue() const;
		unsigned char getBlueValue() const;
		void setRedValue(unsigned char);
		void setGreenValue(unsigned char);
		void setBlueValue(unsigned char);
	};
}

#endif
