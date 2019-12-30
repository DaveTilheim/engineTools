#include "ConvexEntity.hpp"


ConvexEntity::ConvexEntity() : Entity<sf::ConvexShape>()
{
	trace("ConvexEntity creation");
}

ConvexEntity::ConvexEntity(float x, float y, Origin origin) : Entity<sf::ConvexShape>(x, y)
{
	setSideOrigin(origin);
}

ConvexEntity::ConvexEntity(float x, float y, Origin origin, int n, ...) : Entity<sf::ConvexShape>(x, y)
{
	va_list args;
	setPointCount(n);
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		setPoint(i, sf::Vector2f(va_arg(args, int), va_arg(args, int)));
	}
	va_end(args);
	setSideOrigin(origin);
}

ConvexEntity::ConvexEntity(const sf::Vector2f& pos, Origin origin) : Entity<sf::ConvexShape>(pos)
{
	setSideOrigin(origin);
}

ConvexEntity::ConvexEntity(const sf::Vector2f& pos, Origin origin, int n, ...) : Entity<sf::ConvexShape>(pos)
{
	va_list args;
	setPointCount(n);
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		setPoint(i, sf::Vector2f(va_arg(args, int), va_arg(args, int)));
	}
	va_end(args);
	setSideOrigin(origin);
}

ConvexEntity::ConvexEntity(const ConvexEntity& cp) : Entity<sf::ConvexShape>(cp)
{
	trace("ConvexEntity creation");
}

ConvexEntity::ConvexEntity(sf::Texture *texture, float x, float y, Origin origin) : Entity<sf::ConvexShape>(x, y)
{
	setTexture(texture);
	setSideOrigin(origin);
	trace("ConvexEntity creation");
}

ConvexEntity::ConvexEntity(sf::Texture *texture, float x, float y, Origin origin, int n, ...) : Entity<sf::ConvexShape>(x, y)
{
	va_list args;
	setPointCount(n);
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		setPoint(i, sf::Vector2f(va_arg(args, int), va_arg(args, int)));
	}
	va_end(args);
	setTexture(texture);
	setSideOrigin(origin);
	trace("ConvexEntity creation");
}

ConvexEntity::ConvexEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin) : Entity<sf::ConvexShape>(pos)
{
	setTexture(texture);
	setSideOrigin(origin);
	trace("ConvexEntity creation");
}

ConvexEntity::ConvexEntity(sf::Texture *texture, const sf::Vector2f& pos, Origin origin, int n, ...) : Entity<sf::ConvexShape>(pos)
{
	va_list args;
	setPointCount(n);
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		setPoint(i, sf::Vector2f(va_arg(args, int), va_arg(args, int)));
	}
	va_end(args);
	setTexture(texture);
	setSideOrigin(origin);
	trace("ConvexEntity creation");
}

ConvexEntity::~ConvexEntity()
{
	trace("ConvexEntity destruction");
}

void ConvexEntity::setPoints(unsigned n, ...)
{
	va_list args;
	setPointCount(n);
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		setPoint(i, sf::Vector2f(va_arg(args, int), va_arg(args, int)));
	}
	va_end(args);
}

ConvexEntity& ConvexEntity::operator=(const ConvexEntity& cp)
{
	Entity<sf::ConvexShape>::operator=(cp);
	return *this;
}

ostream &operator<<(ostream& out, const ConvexEntity& obj)
{
	return out << *dynamic_cast<const Entity<sf::ConvexShape> *>(&obj);
}
