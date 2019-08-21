#include "Entity.hpp"
#include <exception>
#include <cmath>

using namespace se;

Entity::Entity(float x, float y, float width, float height, Application *root, sf::Color bgColor) 
: shape(new sf::RectangleShape(sf::Vector2f(width, height))), bgColor(bgColor), root(root)
{
	this->shape->setFillColor(this->bgColor);
	this->shape->setPosition(x, y);
}

Entity::Entity(float x, float y, float radius, Application *root, sf::Color bgColor) 
: shape(new sf::CircleShape(radius)), bgColor(bgColor), root(root)
{
	this->shape->setFillColor(this->bgColor);
	this->shape->setPosition(x, y);
}

Entity::~Entity()
{
	if(this->shape)
		delete this->shape;
	std::cout << "Entity deleted" << std::endl;
}

void Entity::render()
{
	this->root->getWindow()->draw(*this->shape);
}

void Entity::setPosition(float x, float y)
{
	this->shape->setPosition(x, y);
}

void Entity::setOrigin(float x, float y)
{
	this->shape->setOrigin(x, y);
}

sf::Vector2f Entity::getPosition()
{
	return this->shape->getPosition();;
}

sf::Vector2f Entity::getOrigin()
{
	return this->shape->getOrigin();
}

void Entity::move(float vx, float vy)
{
	vx *= this->root->getDt();
	vy *= this->root->getDt();
	this->shape->move(vx, vy);
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

float Entity::getDistance(sf::Vector2f point)
{
	const sf::Vector2f& middle = this->getMiddle();
	return sqrt((point.x - middle.x)*(point.x - middle.x) + (point.y - middle.y)*(point.y - middle.y));
}

float Entity::getDistance(Entity& other)
{
	return this->getDistance(other.getMiddle());
}
