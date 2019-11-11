#include "BGProgressBar.hpp"

using namespace se;

void BGProgressBar::render()
{
	this->setSize(sf::Vector2f(this->maxSize, this->getSize().y));
	this->setFillColor(this->bgColorPG);
	this->ProgressBar::render();
	this->ajust();
	this->ProgressBar::render();
	this->setSize(sf::Vector2f(this->maxSize, this->getSize().y));
}

void BGProgressBar::setBgColor(const sf::Color &color)
{
	this->bgColorPG = color;
}
