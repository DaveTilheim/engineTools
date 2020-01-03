#include "ProgressBar.hpp"


ProgressBar::ProgressBar(float maxValue, float currentValue, float w, float h, Origin origin) : RectEntity(0,0,w,h,origin),
currentValue(currentValue), maxValue(maxValue)
{

}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::view(sf::RenderWindow& window)
{
	float fill = currentValue / maxValue;
	auto size = getSize();
	auto bgc = getFillColor();
	window.draw(*this);
	setSize(sf::Vector2f(size.x * fill, size.y));
	setFillColor(sf::Color(
		maxColor.r * fill + minColor.r * (1 - fill),
		maxColor.g * fill + minColor.g * (1 - fill),
		maxColor.b * fill + minColor.b * (1 - fill)
	));
	window.draw(*this);
	setSize(size);
	setFillColor(bgc);
}

float ProgressBar::getCurrentValue() const
{
	return currentValue;
}

float ProgressBar::getMaxValue() const
{
	return maxValue;
}

float ProgressBar::getPercent() const
{
	return currentValue / maxValue;
}

void ProgressBar::setCurrentValue(float cv)
{
	if(cv > maxValue)
		currentValue = maxValue;
	else if(cv < 0)
		currentValue = 0;
	else
		currentValue = cv;
}

void ProgressBar::setMaxValue(float mv)
{
	maxValue = mv;
	setCurrentValue(currentValue);
}

void ProgressBar::setPercent(float p)
{
	setCurrentValue(maxValue * p);
}


