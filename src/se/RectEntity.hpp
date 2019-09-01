#ifndef __RECT_ENTITY_HPP__
#define __RECT_ENTITY_HPP__

#include "Entity.hpp"
#include <cmath>

namespace se
{
	class RectEntity : public Entity
	{
	public:
		RectEntity(float x, float y, float width, float height, Application *root, sf::Color bgColor=sf::Color::White);
		RectEntity(float x, float y, std::string image, Application *root, sf::Color bgColor=sf::Color::White);
		sf::RectangleShape& getShape();
		sf::Vector2f getSize();
		void setSize(sf::Vector2f size);
		virtual sf::Vector2f getMiddle();
		virtual void update() abstract;
		virtual void setMiddleOrigin();
		virtual void setScale(float vx, float vy);
	};
}

#endif
