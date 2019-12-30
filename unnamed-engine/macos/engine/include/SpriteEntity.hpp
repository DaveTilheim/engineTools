#ifndef SPRITEENTITY_HPP
#define SPRITEENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"
#include "Animated.hpp"

class SpriteEntity : public Entity<sf::Sprite>, public Animated
{
private:
public:
	SpriteEntity();
	SpriteEntity(float x, float y, Origin origin=TOP_LEFT);
	SpriteEntity(const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	SpriteEntity(const SpriteEntity& cp);
	SpriteEntity(sf::Texture *texture, float x=0, float y=0, Origin origin=TOP_LEFT);
	SpriteEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	virtual ~SpriteEntity();
	SpriteEntity& operator=(const SpriteEntity& cp);
	friend ostream &operator<<(ostream& out, const SpriteEntity& obj);
};

#endif
