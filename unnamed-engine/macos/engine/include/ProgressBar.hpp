#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP
#include "RectEntity.hpp"


class ProgressBar : public RectEntity
{
protected:
	float currentValue;
	float maxValue;
	sf::Color maxColor = sf::Color::Green;
	sf::Color minColor = sf::Color::Red;
public:
	ProgressBar(float maxValue, float currentValue, float w, float h, Origin origin=TOP_LEFT);
	virtual ~ProgressBar();
	virtual void view(sf::RenderWindow& window) override;
	float getCurrentValue() const;
	float getMaxValue() const;
	float getPercent() const;
	virtual void setCurrentValue(float cv);
	void setMaxValue(float mv);
	void setPercent(float p);
};

#endif
