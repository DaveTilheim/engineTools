#ifndef __RECT_ENTITY_HPP__
#define __RECT_ENTITY_HPP__

#include "Entity.hpp"
#include <cmath>

namespace se
{
	class RectEntity : public Entity
	{
	public:
		RectEntity(float x, float y, float width, float height, Application *root, sf::Color bgColor=sf::Color::Red);
		sf::RectangleShape& getShape();
		virtual sf::Vector2f getMiddle();
		virtual void update() abstract;
	};
}

#endif
