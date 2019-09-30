#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP
#include "Label.hpp"

namespace se
{
	class ProgressBar : public Widget
	{
	protected:
		static const double MIN_VALUE;
		double maxValue = 100;
		double value = 100;
		float maxSize;
		sf::Color maxColor = sf::Color::Green;
		sf::Color minColor = sf::Color::Red;
		Label *label = nullptr;
		void ajust();
	public:
		ProgressBar(float x, float y, float maxSize, float height, Application *root, double maxVal=100, double val=100);
		void addValue(double value);
		void setMaxValue(double maxValue);
		void setValue(double value);
		void setMaxColor(const sf::Color &c);
		void setMinColor(const sf::Color &c);
		void setMaxSize(float maxSize);
		void attachLabel(Label &label);
		double getMaxValue() const;
		double getValue() const;
		const sf::Color &getMaxColor() const;
		const sf::Color &getMinColor() const;
		float getMaxSize() const;
	};
}

#endif
