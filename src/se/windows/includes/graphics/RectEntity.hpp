#ifndef RECT_ENTITY_HPP
#define RECT_ENTITY_HPP

#include "Entity.hpp"
#include <cmath>

namespace se
{
	class RectEntity : public Entity
	{
	public:
		RectEntity(float x, float y, float width, float height, Application *root, sf::Color bgColor=sf::Color::White);
		RectEntity(float x, float y, std::string image, Application *root, sf::Color bgColor=sf::Color::White);
		RectEntity(const RectEntity&);
		sf::RectangleShape& getShape();
		virtual sf::Vector2f getSize() override;
		virtual void setSize(sf::Vector2f size);
		virtual sf::Vector2f getMiddle() override final;
		//virtual void update() override abstract;
		virtual void setMiddleOrigin() override;
		virtual void setScale(float vx, float vy) override;
	};
}

#endif
