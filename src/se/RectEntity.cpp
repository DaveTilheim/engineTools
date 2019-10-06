#include "RectEntity.hpp"

using namespace se;

RectEntity::RectEntity(float x, float y, float width, float height, Application *root, sf::Color bgColor)
: Entity(x, y, width, height, root, bgColor)
{
	trace("RectEntity creation");
}

RectEntity::RectEntity(float x, float y, std::string image, Application *root, sf::Color bgColor)
: Entity(x, y, 1,1, root, bgColor)
{
	std::string txtId = image.substr(0, image.find("."));
	this->addTexture(txtId, image);
	this->setTexture(txtId);
	this->setSize(static_cast<sf::Vector2f>(this->textures[txtId]->getSize()));
	this->setMiddleOrigin();
	trace("RectEntity creation");
}

sf::RectangleShape& RectEntity::getShape()
{
	return *dynamic_cast<sf::RectangleShape*>(this->shape);
}

sf::Vector2f RectEntity::getMiddle()
{
	sf::Vector2f pos = this->shape->getPosition();
	/*pos.x -= getOrigin().x;
	pos.y -= getOrigin().y;*/
	const sf::Vector2f& size = this->getShape().getSize();
	return sf::Vector2f(this->getShape().getGlobalBounds().left + size.x / 2.0, this->getShape().getGlobalBounds().top + size.y / 2.0);
}

sf::Vector2f RectEntity::getSize()
{
	return this->getShape().getSize();
}

void RectEntity::setSize(sf::Vector2f size)
{
	this->getShape().setSize(size);
}

void RectEntity::setMiddleOrigin()
{
	sf::Vector2f v = this->getSize();
	v.x = v.x/2;
	v.y = v.y/2;
	this->setOrigin(v.x,v.y);
}

void RectEntity::setScale(float sx, float sy)
{
	sf::Vector2f v = this->getSize();
	this->setSize(sf::Vector2f(v.x * sx, v.y * sy));
	this->getShape().setScale(sf::Vector2f(sx < 0 ? -1 : 1, sy < 0 ? -1 : 1));
}

