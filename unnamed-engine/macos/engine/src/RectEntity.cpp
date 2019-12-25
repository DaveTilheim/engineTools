#include "RectEntity.hpp"


const sf::Vector2f RectEntity::DEFAULT_SIZE = sf::Vector2f(50, 50);



RectEntity::RectEntity() : Entity<sf::RectangleShape>()
{
	trace("RectEntity creation");
}

RectEntity::RectEntity(float x, float y, Origin origin) : Entity<sf::RectangleShape>(x, y)
{
	setSize(DEFAULT_SIZE);
	setSideOrigin(origin);
}

RectEntity::RectEntity(const sf::Vector2f& pos, Origin origin) : Entity<sf::RectangleShape>(pos)
{
	setSize(DEFAULT_SIZE);
	setSideOrigin(origin);
}

RectEntity::RectEntity(float x, float y, float w, float h, Origin origin) : Entity<sf::RectangleShape>(x, y)
{
	setSize(sf::Vector2f(w, h));
	setSideOrigin(origin);
}

RectEntity::RectEntity(const sf::Vector2f& pos, const sf::Vector2f& size, Origin origin) : Entity<sf::RectangleShape>(pos)
{
	setSize(size);
	setSideOrigin(origin);
}

RectEntity::RectEntity(const RectEntity& cp) : Entity<sf::RectangleShape>(cp)
{
	trace("RectEntity creation");
}

RectEntity::RectEntity(sf::Texture *texture) : Entity<sf::RectangleShape>()
{
	setTexture(texture);
	setSize(static_cast<sf::Vector2f>(texture->getSize()));
	trace("RectEntity creation");
}

RectEntity::~RectEntity()
{
	trace("RectEntity destruction");
}

float RectEntity::getWidth() const
{
	return getSize().x;
}

float RectEntity::getHeight() const
{
	return getSize().y;
}

sf::Vector2f RectEntity::getDimension() const
{
	return getSize();
}

void RectEntity::setWidth(float w)
{
	setSize(sf::Vector2f(w, getSize().y));
}

void RectEntity::setHeight(float h)
{
	setSize(sf::Vector2f(getSize().x, h));
}

void RectEntity::setDimension(float w, float h)
{
	setSize(sf::Vector2f(w, h));
}

void RectEntity::updateTexture(const Image& img)
{
	((sf::Texture *)getTexture())->update(img);
}

RectEntity& RectEntity::operator=(const RectEntity& cp)
{
	Entity<sf::RectangleShape>::operator=(cp);
	return *this;
}

ostream &operator<<(ostream& out, const RectEntity& obj)
{
	return out << *dynamic_cast<const Entity<sf::RectangleShape> *>(&obj);
}
