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
	vx /= timesec;
	vy /= timesec;
	this->move(vx, vy);
}

void Entity::move(float vx, float vy, float timesecx, float timesecy)
{
	vx /= timesecx;
	vy /= timesecy;
	this->move(vx, vy);
}

sf::Vector2f Entity::getComponent(float vx, float vy, float x, float y)
{
	sf::Vector2f pos = this->getPosition();
	float distance = this->getDistance(sf::Vector2f(x, y));
	return sf::Vector2f(sin((x - pos.x) / distance) * vx, sin((y - pos.y) / distance) * vy);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY)
{
	sf::Vector2f pos = this->getPosition();
	float distance = this->getDistance(sf::Vector2f(targetX, targetY));
	this->move(sin((targetX - pos.x) / distance) * vx, sin((targetY - pos.y) / distance) * vy);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY, float timesec)
{
	vx /= timesec;
	vy /= timesec;
	this->moveToward(vx, vy, targetX, targetY);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY, float timesecx, float timesecy)
{
	vx /= timesecx;
	vy /= timesecy;
	this->moveToward(vx, vy, targetX, targetY);
}

void Entity::moveToward(float vx, float vy, Entity &other)
{
	sf::Vector2f pos = other.getPosition();
	this->moveToward(vx, vy, pos.x, pos.y);
}

void Entity::moveToward(float vx, float vy, Entity &other, float timesec)
{
	sf::Vector2f pos = other.getPosition();
	this->moveToward(vx, vy, pos.x, pos.y, timesec);
}

void Entity::moveToward(float vx, float vy, Entity &other, float timesecx, float timesecy)
{
	sf::Vector2f pos = other.getPosition();
	this->moveToward(vx, vy, pos.x, pos.y, timesecx, timesecy);
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

float Entity::getRotation()
{
	return this->shape->getRotation();
}

void Entity::setRotation(float angle)
{
	this->shape->setRotation(angle);
}

void Entity::rotation(float angle)
{
	this->shape->setRotation(this->shape->getRotation() + angle);
}

void Entity::rotate(float angle)
{
	angle *= this->root->getDt();
	this->shape->rotate(angle);
}

void Entity::rotate(float angle, float timesec)
{
	angle /= timesec;
	this->rotate(angle);
}

void Entity::rotate(float angle, float targetX, float targetY)
{
	angle *= this->root->getDt()*this->root->getDt();
	sf::Vector2f pos = this->getPosition();
	this->setPosition(pos.x-targetX, pos.y-targetY);
	pos = this->getPosition();
	this->setPosition(cos(angle) * pos.x - sin(angle) * pos.y,
					  sin(angle) * pos.x + cos(angle) * pos.y);
	pos = this->getPosition();
	this->setPosition(pos.x+targetX, pos.y+targetY);
}

void Entity::rotate(float angle, float targetX, float targetY, float timesec)
{
	angle /= timesec;
	this->rotate(angle, targetX, targetY);
}

void Entity::rotate(float angle, Entity &other)
{
	sf::Vector2f otherPos = other.getPosition();
	this->rotate(angle, otherPos.x, otherPos.y);
}

void Entity::rotate(float angle, Entity &other, float timesec)
{
	sf::Vector2f otherPos = other.getPosition();
	this->rotate(angle, otherPos.x, otherPos.y, timesec);
}


