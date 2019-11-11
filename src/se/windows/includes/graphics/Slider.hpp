#ifndef SLIDER_HPP
#define SLIDER_HPP
#include <functional>
#include "Widget.hpp"
#include "LinkedEntity.hpp"

namespace se
{
	class Slider : public LinkedEntity<Widget>
	{
	protected:
		static Slider *changeAble;
		float maxValue = 100;
		int precision = 1;
		std::function<void(Slider *)> atChange = [](Slider *){};
	public:
		Slider(int x, int y, int w, int h, Application *root, float maxValue=100,const sf::Color &color=sf::Color::White);
		float getValue();
		void setValue(float v);
		Widget& getCursor();
		void setAtChange(std::function<void(Slider *)>);
		bool isOnChange() const;
		void setPrecision(int v=0);
	};
}

#endif
