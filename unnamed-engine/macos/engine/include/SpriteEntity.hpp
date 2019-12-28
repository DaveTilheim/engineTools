#ifndef SPRITEENTITY_HPP
#define SPRITEENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"

class SpriteEntity : public Entity<sf::Sprite>
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
	void updateTexture(const Image& img);
	SpriteEntity& operator=(const SpriteEntity& cp);
	friend ostream &operator<<(ostream& out, const SpriteEntity& obj);
};

#endif
