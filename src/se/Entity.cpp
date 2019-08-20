#include "Entity.hpp"
#include <exception>

using namespace se;

Entity::Entity(float x, float y, float width, float height, Application *root, sf::Color bgColor) 
: shape(sf::Vector2f(width, height)), bgColor(bgColor), root(root)
{
	this->shape.setFillColor(this->bgColor);
	this->shape.setPosition(x, y);
}

Entity::~Entity()
{
	std::cout << "Entity deleted" << std::endl;
}

void Entity::render()
{
	this->root->getWindow()->draw(this->shape);
}

void Entity::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

sf::RectangleShape &Entity::getShape()
{
	return this->shape;
}

void Entity::move(float vx, float vy)
{
	vx *= this->root->getDt();
	vy *= this->root->getDt();
	this->shape.move(vx, vy);
	//std::cout << "vx = " << vx << " vy = " << vy << " dt = " << this->root->getDt() << std::endl;
}

void Entity::move(float vx, float vy, float timesec)
{
	if(vx != 0)
		vx /= timesec;
	if(vy != 0)
		vy /= timesec;
	this->move(vx, vy);
}

void Entity::move(float vx, float vy, float timesecx, float timesecy)
{
	if(vx != 0)
		vx /= timesecx;
	if(vy != 0)
		vy /= timesecy;
	this->move(vx, vy);
}
