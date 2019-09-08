#ifndef __LINE_HPP__
#define __LINE_HPP__
#include "RectEntity.hpp"

namespace se
{
	class Line : public RectEntity
	{
	protected:
		sf::Vector2f start;
		sf::Vector2f end;
		float weight = 1;
	public:
		Line(sf::Vector2f start, sf::Vector2f end, float weight, Application *root, sf::Color bgColor=sf::Color::White);
		void setStart(sf::Vector2f pos);
		void setEnd(sf::Vector2f pos);
		void setWeight(float weight=1);
		virtual float getDistance(sf::Vector2f point, float metreAsPixel=1) override;
		virtual float getDistance(Entity& other, float metreAsPixel=1) override;
	};
}

#endif
