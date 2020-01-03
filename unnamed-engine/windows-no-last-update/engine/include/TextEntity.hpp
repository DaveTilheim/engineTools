#ifndef TEXTENTITY_HPP
#define TEXTENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"

class TextEntity : public Entity<sf::Text>
{
private:
protected:
public:
	TextEntity();
	TextEntity(float x, float y, Origin origin=TOP_LEFT);
	TextEntity(const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	TextEntity(float x, float y, string text, const sf::Font& font, unsigned cs=20, Origin origin=TOP_LEFT);
	TextEntity(const sf::Vector2f& pos, string text, const sf::Font& font, unsigned cs=20, Origin origin=TOP_LEFT);
	TextEntity(const TextEntity& cp);
	TextEntity(string text, const sf::Font& font, unsigned csize=20, const sf::Color& c=sf::Color::White, unsigned thicksize=0,const sf::Color& thickcolor=sf::Color::Black);
	virtual ~TextEntity();
	TextEntity& operator=(const TextEntity& cp);
	friend ostream &operator<<(ostream& out, const TextEntity& obj);
};

#endif
