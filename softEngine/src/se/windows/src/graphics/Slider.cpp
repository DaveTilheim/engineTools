#include <graphics/Slider.hpp>

using namespace se;

Slider *Slider::changeAble = nullptr;

Slider::Slider(int x, int y, int w, int h, Application *root, float maxValue, const sf::Color &color) :
	LinkedEntity<Widget>(x, y, w, h, root, color) ,  maxValue(maxValue)
{
	Widget *cursor = new Widget(x, y, w/20, h*1.5, root);
	onLeftClick([this](Widget *w)
	{
		linkedList["cursor"]->linked->setPosition(util::getMousePosition().x, getPosition().y);
	}, true);
	cursor->onLeftHoldClick([this](Widget* w)
	{
		if(not Slider::changeAble or Slider::changeAble == this)
		{
			auto m = util::getMousePosition();
			w->setPosition(m.x, w->getPosition().y);
			if(w->getTLPosition().x < getTLPosition().x)
			{
				w->setPosition(getTLPosition().x, w->getPosition().y);
			}
			else if(w->getTLPosition().x+w->getSize().x >= getTLPosition().x + getSize().x)
			{
				w->setPosition(getTLPosition().x + getSize().x, w->getPosition().y);
			}
			atChange(this);
			Slider::changeAble = this;
		}
	},
	[](Widget *w)
	{
		Slider::changeAble = nullptr;
	});
	link("cursor", *cursor, true, true);
}

void Slider::setAtChange(std::function<void(Slider *)> change)
{
	atChange = change;
}

float Slider::getValue()
{
	float value = maxValue * ((linkedList["cursor"]->linked->getPosition().x - getTLPosition().x) / (float)getSize().x);
	value = value - ((int)value % precision);
	return value;
}

void Slider::setValue(float v)
{
	getCursor().setPosition((v / maxValue) * (float)getSize().x + getTLPosition().x, getCursor().getPosition().y);
	atChange(this);
}

void Slider::setPrecision(int v)
{
	precision = v;
}

Widget& Slider::getCursor()
{
	return *dynamic_cast<Widget *>(linkedList["cursor"]->linked);
}
