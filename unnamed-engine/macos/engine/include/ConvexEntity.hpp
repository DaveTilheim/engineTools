#ifndef CONVEXENTITY_HPP
#define CONVEXENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"
#include <cstdarg>
#include "Animated.hpp"

class ConvexEntity : public Entity<sf::ConvexShape>, public Animated
{
private:
protected:
public:
	static const sf::Vector2f DEFAULT_SIZE;
	ConvexEntity();
	ConvexEntity(float x, float y, Origin origin=TOP_LEFT);
	ConvexEntity(float x, float y, Origin origin=TOP_LEFT, int n=0, ...);
	ConvexEntity(const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	ConvexEntity(const sf::Vector2f& pos, Origin origin=TOP_LEFT, int n=0, ...);
	ConvexEntity(const ConvexEntity& cp);
	ConvexEntity(sf::Texture *texture, float x=0, float y=0, Origin origin=TOP_LEFT);
	ConvexEntity(sf::Texture *texture, float x=0, float y=0, Origin origin=TOP_LEFT, int n=0, ...);
	ConvexEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	ConvexEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin=TOP_LEFT, int n=0, ...);
	virtual ~ConvexEntity();
	void setPoints(unsigned n, ...);
	ConvexEntity& operator=(const ConvexEntity& cp);
	friend ostream &operator<<(ostream& out, const ConvexEntity& obj);
};

#endif
