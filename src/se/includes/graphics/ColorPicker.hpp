#ifndef COLOR_PICKER_HPP
#define COLOR_PICKER_HPP
#include "Widget.hpp"
#include "LinkedEntity.hpp"
#include "CircleEntity.hpp"
#include "PolymorphEntity.hpp"
#include "Label.hpp"
#include "PixelPicker.hpp"

namespace se
{
	class ColorPicker : public LinkedEntity<Widget>, public PixelPicker
	{
	protected:
		Poly<CircleEntity> viewRect;
		Label *textColorValue = nullptr;
		bool onChange = false;
	public:
		ColorPicker(float x, float y, float w, float h, Application *root, const sf::Color&color=sf::Color(255,0,0), sf::Font*font=nullptr);
		virtual ~ColorPicker();
		void setMainColor(const sf::Color&);
	};
}

#endif
