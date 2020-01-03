#ifndef TEXTPROGRESSBAR_HPP
#define TEXTPROGRESSBAR_HPP
#include "ProgressBar.hpp"
#include "TextEntity.hpp"

class TextProgressBar : public ProgressBar
{
protected:
	TextEntity *text = nullptr;
public:
	TextProgressBar(float maxValue, float currentValue, float w, float h, TextEntity* text, Origin origin=TOP_LEFT);
	virtual void view(sf::RenderWindow& window) override;
	virtual ~TextProgressBar();
	void setCurrentValue(float cv) override;
};

#endif
