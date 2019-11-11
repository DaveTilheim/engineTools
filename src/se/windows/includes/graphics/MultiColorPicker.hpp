#ifndef MULTI_COLOR_PICKER_HPP
#define MULTI_COLOR_PICKER_HPP
#include "ColorPicker.hpp"
#include "Slider.hpp"

namespace se
{
	class MultiColorPicker : public ColorPicker
	{
	protected:
		unsigned char redValue;
		unsigned char greenValue;
		unsigned char blueValue;
		unsigned char alphaValue;
		void updateColor();
	public:
		MultiColorPicker(float x, float y, float w, float h, Application *root, const sf::Color&color=sf::Color(255,0,0), sf::Font *font=nullptr);
		unsigned char getRedValue() const;
		unsigned char getGreenValue() const;
		unsigned char getBlueValue() const;
		unsigned char getAlphaValue() const;
		void setRedValue(unsigned char);
		void setGreenValue(unsigned char);
		void setBlueValue(unsigned char);
		void setAlphaValue(unsigned char);
	};
}

#endif
