#include "TextEntity.hpp"


TextEntity::TextEntity() : Entity<sf::Text>()
{
	trace("TextEntity creation");
}

TextEntity::TextEntity(float x, float y, Origin origin) : Entity<sf::Text>(x, y)
{
	setSideOrigin(origin);
	trace("TextEntity creation");
}

TextEntity::TextEntity(const sf::Vector2f& pos, Origin origin) : Entity<sf::Text>(pos)
{
	setSideOrigin(origin);
	trace("TextEntity creation");
}

TextEntity::TextEntity(float x, float y, string text, const sf::Font& font, unsigned cs, Origin origin) : Entity<sf::Text>(x, y)
{
	setFont(font);
	setString(text);
	setCharacterSize(cs);
	setSideOrigin(origin);
	trace("TextEntity creation");
}

TextEntity::TextEntity(const sf::Vector2f& pos, string text, const sf::Font& font, unsigned cs, Origin origin) : Entity<sf::Text>(pos)
{
	setFont(font);
	setString(text);
	setCharacterSize(cs);
	setSideOrigin(origin);
	trace("TextEntity creation");
}

TextEntity::TextEntity(const TextEntity& cp) : Entity<sf::Text>(cp)
{
	trace("TextEntity creation");
}

TextEntity::TextEntity(string text, const sf::Font& font, unsigned csize, const sf::Color& c, unsigned thicksize,const sf::Color& thickcolor) : Entity<sf::Text>()
{
	setFont(font);
	setString(text);
	setCharacterSize(csize);
	setFillColor(c);
	if(thicksize)
	{
		setOutlineThickness(thicksize);
		setOutlineColor(thickcolor);
	}
	trace("TextEntity creation");
}

TextEntity::~TextEntity()
{
	trace("TextEntity destruction");
}

TextEntity& TextEntity::operator=(const TextEntity& cp)
{
	Entity<sf::Text>::operator=(cp);
	return *this;
}

ostream &operator<<(ostream& out, const TextEntity& obj)
{
	return out << *dynamic_cast<const Entity<sf::Text> *>(&obj);
}
