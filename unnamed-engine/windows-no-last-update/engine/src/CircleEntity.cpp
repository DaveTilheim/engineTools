#include "CircleEntity.hpp"

const float CircleEntity::DEFAULT_RADIUS = 25.0f;


CircleEntity::CircleEntity() : Entity<sf::CircleShape>()
{
	trace("CircleEntity creation");
}


CircleEntity::CircleEntity(float x, float y, Origin origin) : Entity<sf::CircleShape>(x, y)
{
	setRadius(DEFAULT_RADIUS);
	setSideOrigin(origin);
}

CircleEntity::CircleEntity(const sf::Vector2f& pos, Origin origin) : Entity<sf::CircleShape>(pos)
{
	setRadius(DEFAULT_RADIUS);
	setSideOrigin(origin);
}

CircleEntity::CircleEntity(float x, float y, float radius, Origin origin) : Entity<sf::CircleShape>(x, y)
{
	setRadius(radius);
	setSideOrigin(origin);
}

CircleEntity::CircleEntity(const sf::Vector2f& pos, float radius, Origin origin) : Entity<sf::CircleShape>(pos)
{
	setRadius(radius);
	setSideOrigin(origin);
}

CircleEntity::CircleEntity(const CircleEntity& cp) : Entity<sf::CircleShape>(cp)
{
	trace("CircleEntity creation");
}

CircleEntity::CircleEntity(sf::Texture *texture, float x, float y, Origin origin) : Entity<sf::CircleShape>(x, y)
{
	setTexture(texture);
	setRadius((texture->getSize().x + texture->getSize().y) / 2.0);
	setSideOrigin(origin);
	trace("CircleEntity creation");
}

CircleEntity::CircleEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin) : Entity<sf::CircleShape>(pos)
{
	setTexture(texture);
	setRadius((texture->getSize().x + texture->getSize().y) / 2.0);
	setSideOrigin(origin);
	trace("CircleEntity creation");
}

CircleEntity::~CircleEntity()
{
	trace("CircleEntity destruction");
}

bool CircleEntity::collision(const CircleEntity& other)
{
	return (getDistance(other.getSidePosition()) < getRadius() + other.getRadius());
}

CircleEntity& CircleEntity::operator=(const CircleEntity& cp)
{
	Entity<sf::CircleShape>::operator=(cp);
	return *this;
}

ostream &operator<<(ostream& out, const CircleEntity& obj)
{
	return out << *dynamic_cast<const Entity<sf::CircleShape> *>(&obj);
}
