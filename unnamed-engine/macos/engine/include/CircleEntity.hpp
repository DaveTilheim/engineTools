#ifndef CIRCLEENTITY_HPP
#define CIRCLEENTITY_HPP
#include "Entity.hpp"
#include "Image.hpp"

class CircleEntity : public Entity<sf::CircleShape>
{
private:
protected:
public:
	CircleEntity();
	//add constructors
	CircleEntity(const CircleEntity& cp);
	CircleEntity(sf::Texture *texture);
	virtual ~CircleEntity();
	void updateTexture(const Image& img);
	bool collision(const CircleEntity& other);
	CircleEntity& operator=(const CircleEntity& cp);
	friend ostream &operator<<(ostream& out, const CircleEntity& obj);
};

#endif
