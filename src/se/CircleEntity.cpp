#include "CircleEntity.hpp"

using namespace se;

CircleEntity::CircleEntity(float x, float y, float radius, Application *root, sf::Color bgColor)
: Entity(x, y, radius, root, bgColor)
{

}

sf::CircleShape& CircleEntity::getShape()
{
	return *dynamic_cast<sf::CircleShape*>(this->shape);
}

sf::Vector2f CircleEntity::getMiddle()
{
	const sf::Vector2f& origin = this->getShape().getOrigin();
	const sf::Vector2f& pos = this->getPosition();
	const float& radius = this->getShape().getRadius();
	return sf::Vector2f(pos.x + radius - origin.x, pos.y + radius - origin.y);
}
