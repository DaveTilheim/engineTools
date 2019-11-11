#ifndef LABELED_SLIDER_HPP
#define LABELED_SLIDER_HPP
#include "Slider.hpp"
#include "Label.hpp"

namespace se
{
	class LabeledSlider : public Slider
	{
	protected:
		bool integerView = false;
	public:
		LabeledSlider(int x, int y, int w, int h, Application *root, float maxValue=100, sf::Font*font=nullptr, const sf::Color &color=sf::Color::White);
		void setIntegerView(bool);
	};
}

#endif
