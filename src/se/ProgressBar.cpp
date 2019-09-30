#include "ProgressBar.hpp"

using namespace se;

const double ProgressBar::MIN_VALUE = 0;

ProgressBar::ProgressBar(float x, float y, float maxSize, float height, Application *root, double maxVal, double val)
: Widget(x, y, maxSize, height, root)
{
	this->maxSize = maxSize;
	if(maxVal > ProgressBar::MIN_VALUE)
	{
		this->maxValue = maxVal;
	}
	if(val >= ProgressBar::MIN_VALUE and val <= this->maxValue)
	{
		this->value = val;
	}
	this->ajust();
	trace("ProgressBar created");
}

void ProgressBar::ajust()
{
	this->setSize(sf::Vector2f(this->maxSize * (this->value / this->maxValue), this->getSize().y));
	unsigned char r, g, b;
	float perc = this->value/this->maxValue;
	r = this->maxColor.r * perc + this->minColor.r * (1 - perc);
	g = this->maxColor.g * perc + this->minColor.g * (1 - perc);
	b = this->maxColor.b * perc + this->minColor.b * (1 - perc);
	this->setFillColor(sf::Color(r, g, b));
	if(this->label)
	{
		sf::Rect<float> rect = this->shape->getGlobalBounds();
		sf::Vector2f size = this->getSize();
		this->label->setPosition(rect.left + size.x/2, rect.top + size.y/2);
		this->label->setText(std::to_string(static_cast<unsigned long>(this->value)) + " / " + std::to_string(static_cast<unsigned long>(this->maxValue)));
	}
}

void ProgressBar::addValue(double value)
{
	this->value += value;
	if(this->value < 0)
	{
		this->value = 0;
	}
	else
	{
		if(this->value > this->maxValue)
		{
			this->value = this->maxValue;
		}
	}
	this->ajust();
}

void ProgressBar::setMaxValue(double maxValue)
{
	if(maxValue > ProgressBar::MIN_VALUE)
	{
		this->maxValue = maxValue;
		this->ajust();
	}
}

void ProgressBar::setValue(double value)
{
	if(value >= ProgressBar::MIN_VALUE and value <= this->maxValue)
	{
		this->value = value;
		this->ajust();
	}
}

void ProgressBar::setMaxColor(const sf::Color &c)
{
	this->maxColor = c;
	this->ajust();
}

void ProgressBar::setMinColor(const sf::Color &c)
{
	this->minColor = c;
	this->ajust();
}

void ProgressBar::setMaxSize(float maxSize)
{
	if(maxSize > 0)
	{
		this->maxSize = maxSize;
		this->ajust();
	}
}

void ProgressBar::attachLabel(Label &label)
{
	this->label = &label;
	sf::Rect<float> rect = this->shape->getGlobalBounds();
	sf::Vector2f size = this->getSize();
	label.setPosition(rect.left + size.x/2, rect.top + size.y/2);
	label.setText(std::to_string(static_cast<unsigned long>(this->value)) + " / " + std::to_string(static_cast<unsigned long>(this->maxValue)));
	label.setFillColor(sf::Color::Transparent);
}

double ProgressBar::getMaxValue() const
{
	return this->maxValue;
}

double ProgressBar::getValue() const
{
	return this->value;
}

const sf::Color &ProgressBar::getMaxColor() const
{
	return this->maxColor;
}

const sf::Color &ProgressBar::getMinColor() const
{
	return this->minColor;
}

float ProgressBar::getMaxSize() const
{
	return this->maxSize;
}
