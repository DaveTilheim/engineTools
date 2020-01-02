#include "TextProgressBar.hpp"



TextProgressBar::TextProgressBar(float maxValue, float currentValue, float w, float h, TextEntity* text, Origin origin)
: ProgressBar(maxValue, currentValue, w, h, origin), text(text)
{
	text->setString(to_string((int)currentValue) + " / " + to_string((int)maxValue));
	text->setSideOrigin(MIDDLE_CENTER);
}

void TextProgressBar::view(sf::RenderWindow& window)
{
	ProgressBar::view(window);
	text->setPosition(getSidePosition(MIDDLE_CENTER));
	text->setRotation(getRotation());
	window.draw(*text);
}

TextProgressBar::~TextProgressBar()
{
	if(text)
	{
		delete text;
	}
}

void TextProgressBar::setCurrentValue(float cv)
{
	ProgressBar::setCurrentValue(cv);
	text->setString(to_string((int)currentValue) + " / " + to_string((int)maxValue));
	text->setSideOrigin(MIDDLE_CENTER);
}
