#include "SpriteEntity.hpp"


SpriteEntity::SpriteEntity() : Entity<sf::Sprite>()
{
	trace("SpriteEntity creation");
}

SpriteEntity::SpriteEntity(float x, float y, Origin origin) : Entity<sf::Sprite>(x, y)
{
	setSideOrigin(origin);
}

SpriteEntity::SpriteEntity(const sf::Vector2f& pos, Origin origin) : Entity<sf::Sprite>(pos)
{
	setSideOrigin(origin);
}

SpriteEntity::SpriteEntity(const SpriteEntity& cp) : Entity<sf::Sprite>(cp)
{
	trace("SpriteEntity creation");
}

SpriteEntity::SpriteEntity(sf::Texture *texture, float x, float y, Origin origin) : Entity<sf::Sprite>(x, y)
{
	setTexture(*texture);
	setSideOrigin(origin);
	trace("SpriteEntity creation");
}

SpriteEntity::SpriteEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin) : Entity<sf::Sprite>(pos)
{
	setTexture(*texture);
	setSideOrigin(origin);
	trace("SpriteEntity creation");
}

SpriteEntity::~SpriteEntity()
{
	trace("SpriteEntity destruction");
}

void SpriteEntity::updateTexture(const Image& img)
{
	((sf::Texture *)getTexture())->update(img);
}

SpriteEntity& SpriteEntity::operator=(const SpriteEntity& cp)
{
	Entity<sf::Sprite>::operator=(cp);
	return *this;
}

ostream &operator<<(ostream& out, const SpriteEntity& obj)
{
	return out << *dynamic_cast<const Entity<sf::Sprite> *>(&obj);
}
