#ifndef __CIRCLE_ENTITY_HPP__
#define __CIRCLE_ENTITY_HPP__

#include "Entity.hpp"
#include <cmath>

namespace se
{
	class CircleEntity : public Entity
	{
	public:
		CircleEntity(float x, float y, float radius, Application *root, sf::Color bgColor=sf::Color::Red);
		sf::CircleShape& getShape();
		virtual sf::Vector2f getMiddle();
		virtual void update() abstract;
	};
}

#endif
