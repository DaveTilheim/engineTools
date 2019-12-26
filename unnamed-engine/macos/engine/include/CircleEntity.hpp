#ifndef CIRCLEENTITY_HPP
#define CIRCLEENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"

class CircleEntity : public Entity<sf::CircleShape>
{
private:
protected:
public:
	static const float DEFAULT_RADIUS;
	CircleEntity();
	CircleEntity(float x, float y, Origin origin=TOP_LEFT);
	CircleEntity(const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	CircleEntity(float x, float y, float radius, Origin origin=TOP_LEFT);
	CircleEntity(const sf::Vector2f& pos, float radius, Origin origin=TOP_LEFT);
	CircleEntity(const CircleEntity& cp);
	CircleEntity(sf::Texture *texture, float x=0, float y=0, Origin origin=TOP_LEFT);
	CircleEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	virtual ~CircleEntity();
	void updateTexture(const Image& img);
	bool collision(const CircleEntity& other);
	CircleEntity& operator=(const CircleEntity& cp);
	friend ostream &operator<<(ostream& out, const CircleEntity& obj);
};

#endif
