#include "LabeledSlider.hpp"

using namespace se;


LabeledSlider::LabeledSlider(int x, int y, int w, int h, Application *root, float maxValue, sf::Font*font,const sf::Color &color) : Slider(x,y,w,h,root,maxValue,color)
{
	Label *minLabel = new Label(0, 0, "0", font, root, color);
	minLabel->setSize(15);
	minLabel->setFillColor(sf::Color::Transparent);
	minLabel->getText().setOutlineColor(sf::Color::Black);
	minLabel->getText().setOutlineThickness(1);
	minLabel->setTLPosition(getTLPosition().x, getTLPosition().y - 25);
	Label *maxLabel = new Label(0, 0, std::to_string((unsigned)maxValue), font, root, color);
	maxLabel->setSize(15);
	maxLabel->setFillColor(sf::Color::Transparent);
	maxLabel->getText().setOutlineColor(sf::Color::Black);
	maxLabel->getText().setOutlineThickness(1);
	maxLabel->setTLPosition(getTLPosition().x+getSize().x, getTLPosition().y - 25);
	Label *currentLabel = new Label(0, 0, std::to_string(getValue()), font, root, color);
	currentLabel->setSize(15);
	currentLabel->setFillColor(sf::Color::Transparent);
	currentLabel->getText().setOutlineColor(sf::Color::Black);
	currentLabel->getText().setOutlineThickness(1);
	currentLabel->setPosition(getPosition().x, getTLPosition().y + getSize().y + 25);
	link("minLabel", *minLabel, true, true);
	link("maxLabel", *maxLabel, true, true);
	link("currentLabel", *currentLabel, true, true);
	setAtChange([this](Slider *s)
	{
		linkedList["currentLabel"]->linked->setPosition(linkedList["cursor"]->linked->getPosition().x, getTLPosition().y + getSize().y + 25);
		dynamic_cast<Label*>(linkedList["currentLabel"]->linked)->setText(std::to_string(getValue()));
	});
}
