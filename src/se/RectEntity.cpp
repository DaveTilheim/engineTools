#include "RectEntity.hpp"

using namespace se;

RectEntity::RectEntity(float x, float y, float width, float height, Application *root, sf::Color bgColor)
: Entity(x, y, width, height, root, bgColor)
{

}

sf::RectangleShape& RectEntity::getShape()
{
	return *dynamic_cast<sf::RectangleShape*>(this->shape);
}

sf::Vector2f RectEntity::getMiddle()
{
	const sf::Vector2f& pos = this->getPosition();
	const sf::Vector2f& size = this->getShape().getSize();
	return sf::Vector2f(pos.x + size.x / 2.0, pos.y + size.y / 2.0);
}

sf::Vector2f RectEntity::getSize()
{
	return this->getShape().getSize();
}


