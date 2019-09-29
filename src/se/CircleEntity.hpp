#ifndef CIRCLE_ENTITY_HPP
#define CIRCLE_ENTITY_HPP

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
		virtual void setRadius(float radius);
		virtual sf::Vector2f getMiddle() override final;
		virtual void update() override abstract;
		virtual void setMiddleOrigin() override;
		virtual void setScale(float sx, float sy) override;
	};
}

#endif
