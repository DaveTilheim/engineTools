#include "TextEntity.hpp"


TextEntity::TextEntity() : Entity<sf::Text>()
{

}

TextEntity::TextEntity(float x, float y, Origin origin) : Entity<sf::Text>(x, y)
{
	setSideOrigin(origin);
}

TextEntity::TextEntity(const sf::Vector2f& pos, Origin origin) : Entity<sf::Text>(pos)
{
	setSideOrigin(origin);
}

TextEntity::TextEntity(float x, float y, string text, const sf::Font& font, unsigned cs, Origin origin) : Entity<sf::Text>(x, y)
{
	setFont(font);
	setString(text);
	setCharacterSize(cs);
	setSideOrigin(origin);
}

TextEntity::TextEntity(const sf::Vector2f& pos, string text, const sf::Font& font, unsigned cs, Origin origin) : Entity<sf::Text>(pos)
{
	setFont(font);
	setString(text);
	setCharacterSize(cs);
	setSideOrigin(origin);
}

TextEntity::TextEntity(const TextEntity& cp) : Entity<sf::Text>(cp)
{

}

TextEntity::~TextEntity()
{

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
