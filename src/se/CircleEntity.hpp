#ifndef __CIRCLE_ENTITY_HPP__
#define __CIRCLE_ENTITY_HPP__

#include "Entity.hpp"
#include <cmath>

namespace se
{
	class CircleEntity : public Entity
	{
	public:
		CircleEntity(float x, float y, float radius, Application *root, sf::Color bgColor=sf::Color::White);
		CircleEntity(float x, float y, std::string image, Application *root, sf::Color bgColor=sf::Color::White);
		sf::CircleShape& getShape();
		float getRadius();
		void setRadius(float radius);
		virtual sf::Vector2f getMiddle();
		virtual void update() abstract;
		virtual void setMiddleOrigin();
		virtual void setScale(float sx, float sy);
	};
}

#endif
