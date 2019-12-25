#include "CircleEntity.hpp"

CircleEntity::CircleEntity() : Entity<sf::CircleShape>()
{
	trace("CircleEntity creation");
}

CircleEntity::CircleEntity(const CircleEntity& cp) : Entity<sf::CircleShape>(cp)
{
	trace("CircleEntity creation");
}

CircleEntity::CircleEntity(sf::Texture *texture) : Entity<sf::CircleShape>()
{
	setTexture(texture);
	setRadius((texture->getSize().x + texture->getSize().y) / 2.0);
	trace("CircleEntity creation");
}

CircleEntity::~CircleEntity()
{
	trace("CircleEntity destruction");
}

void CircleEntity::updateTexture(const Image& img)
{
	((sf::Texture *)getTexture())->update(img);
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
