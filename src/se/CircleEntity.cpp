#include "CircleEntity.hpp"

using namespace se;

CircleEntity::CircleEntity(float x, float y, float radius, Application *root, sf::Color bgColor)
: Entity(x, y, radius, root, bgColor)
{
	this->setMiddleOrigin();
	trace("CircleEntity creation");
}

CircleEntity::CircleEntity(float x, float y, std::string image, Application *root, sf::Color bgColor)
: Entity(x, y, 1, root, bgColor)
{
	this->addTexture("default", image);
	this->setTexture("default");
	sf::Vector2f size = static_cast<sf::Vector2f>(this->textures["default"]->getSize());
	this->setRadius((size.x + size.y) / 2.0);
	this->setMiddleOrigin();
	trace("CircleEntity creation");
}


CircleEntity::CircleEntity(const CircleEntity& other)
: Entity(0,0, 1,1, other.root, other.bgColor)
{
	*this->shape = *other.shape;
	this->setRadius(dynamic_cast<sf::CircleShape*>(other.shape)->getRadius());
	this->setMiddleOrigin();
	this->setFillColor(other.bgColor);
	for(auto txtr : other.textures)
	{
		this->textures[txtr.first] = new sf::Texture(*txtr.second);
	}
	this->currentTexture = other.currentTexture;
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

float CircleEntity::getRadius()
{
	return this->getShape().getRadius();
}

void CircleEntity::setRadius(float radius)
{
	this->getShape().setRadius(radius);
}

void CircleEntity::setMiddleOrigin()
{
	float r = this->getRadius();
	this->setOrigin(r,r);
}

void CircleEntity::setScale(float sx, float sy)
{
	float radius = this->getRadius();
	this->setRadius(radius * sx);
	this->getShape().setScale(sf::Vector2f(sx < 0 ? -1 : 1, sy < 0 ? -1 : 0));
}
