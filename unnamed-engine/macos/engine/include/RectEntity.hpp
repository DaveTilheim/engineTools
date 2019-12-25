#ifndef RECTENTITY_HPP
#define RECTENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"

class RectEntity : public Entity<sf::RectangleShape>
{
private:
protected:
public:
	static const sf::Vector2f DEFAULT_SIZE;
	RectEntity();
	RectEntity(float x, float y, Origin origin=TOP_LEFT);
	RectEntity(const sf::Vector2f& pos, Origin origin=TOP_LEFT);
	RectEntity(float x, float y, float w, float h, Origin origin=TOP_LEFT);
	RectEntity(const sf::Vector2f& pos, const sf::Vector2f& size, Origin origin=TOP_LEFT);
	RectEntity(const RectEntity& cp);
	RectEntity(sf::Texture *texture);
	virtual ~RectEntity();
	float getWidth() const;
	float getHeight() const;
	sf::Vector2f getDimension() const;
	void setWidth(float w);
	void setHeight(float h);
	void setDimension(float w, float h);
	void updateTexture(const Image& img);
	RectEntity& operator=(const RectEntity& cp);
	friend ostream &operator<<(ostream& out, const RectEntity& obj);
};

#endif
