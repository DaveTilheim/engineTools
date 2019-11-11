#include "LabeledProgressBar.hpp"

using namespace se;

LabeledProgressBar::LabeledProgressBar(float x, float y, float maxSize, float height, Application *root, std::string text, sf::Font *font,double maxVal, double val)
: BGProgressBar(x, y, maxSize, height, root, maxVal, val),
  label(x, y, text, font, root, sf::Color::White), descr(text)
{
	this->label.setFillColor(sf::Color::Transparent);
	trace("LabeledProgressBar created");
}

Label& LabeledProgressBar::getLabel()
{
	return this->label;
}

void LabeledProgressBar::ajust() 
{
	this->ProgressBar::ajust();
	sf::Rect<float> rect = this->shape->getGlobalBounds();
	sf::Vector2f size = this->getSize();
	this->label.setPosition(rect.left + this->maxSize/2, rect.top + size.y/2);
	this->label.setText(this->descr + " " +std::to_string(static_cast<unsigned long>(this->value)) + " / " + std::to_string(static_cast<unsigned long>(this->maxValue)));
}

void LabeledProgressBar::setDescription(std::string descr)
{
	this->descr = descr;
}

void LabeledProgressBar::render()
{
	this->BGProgressBar::render();
	this->label.render();
}
