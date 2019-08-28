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
	{
		delete this->shape;
	}
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

void Entity::movePhy(bool deceleration)
{
	if(deceleration)
	{
		this->updateDeceleration(this->root->getDt());
	}
	else
	{
		this->updateAcceleration(this->root->getDt());
	}
	this->rotatePhy();
	this->move(this->speed.x, this->speed.y);
}

void Entity::movePhy(sf::Vector2f speed, sf::Vector2f target)
{
	sf::Vector2f v = this->getComponent(speed.x,speed.y,target.x,target.y);
	this->setAcceleration(v);
	this->accelerationRotation = (sqrt(v.x*v.x+v.y*v.y))*(v.x < 0 ? -1 : 1)*(v.y < 0 ? -1 : 1 );
	this->movePhy();
}

void Entity::movePhy(sf::Vector2f speed, Entity &target)
{
	sf::Vector2f pos = target.getPosition();
	this->movePhy(speed, pos);
}


void Entity::moveGrav(Entity &other)
{
	this->movePhy(sf::Vector2f(other.gravity, other.gravity), other.getPosition());
}

void Entity::moveGrav(std::vector<Entity *> &others)
{
	int size = others.size();
	this->setAcceleration(sf::Vector2f(0,0));
	for(int i = 0; i < size; i++)
	{
		if(this != others[i])
		{
			sf::Vector2f pos = others[i]->getPosition();
			sf::Vector2f a = this->getComponent(others[i]->gravity, others[i]->gravity, pos.x, pos.y);
			this->acceleration.x += a.x;
			this->acceleration.y += a.y;
			this->accelerationRotation += (sqrt(a.x*a.x+a.y*a.y))*(a.x < 0 ? -1 : 1)*(a.y < 0 ? -1 : 1 );
			this->updateAccelerationRotation(this->root->getDt());
			this->updateAcceleration(this->root->getDt());
		}
	}
	this->movePhy();
}

void Entity::movePhy(std::vector<Entity *> &others, float metreAsPixel)
{
	int size = others.size();
	this->setAcceleration(sf::Vector2f(0,0));
	for(int i = 0; i < size; i++)
	{
		if(this != others[i])
		{
			sf::Vector2f dc = this->getDistanceComponent(*others[i], metreAsPixel);
			float d = this->getDistance(*others[i], metreAsPixel);
			if(d)
			{
				this->force.x = ((G * this->mass * others[i]->mass) / (d*d)) * (dc.x < 0 ? -1 : 1);
				this->force.y = ((G * this->mass * others[i]->mass) / (d*d)) * (dc.y < 0 ? -1 : 1);
			}
			else
			{
				this->force.x = 0;
				this->force.y = 0;
			}
			this->acceleration.x += this->force.x / this->mass;
			this->acceleration.y += this->force.y / this->mass;
			this->updateAcceleration(this->root->getDt());
			this->accelerationRotation += (sqrt(this->force.x*this->force.x+this->force.y*this->force.y)* (dc.x < 0 ? -1 : 1)* (dc.y < 0 ? -1 : 1)) / this->mass;
			this->updateAccelerationRotation(this->root->getDt());
		}
	}
	this->movePhy();
}

void Entity::movePhy(Entity &other, float metreAsPixel)
{
	sf::Vector2f dc = this->getDistanceComponent(other, metreAsPixel);
	float d = this->getDistance(other, metreAsPixel);
	if(d)
	{
		this->force.x = ((G * this->mass * other.mass) / (d*d)) * (dc.x < 0 ? -1 : 1);
		this->force.y = ((G * this->mass * other.mass) / (d*d)) * (dc.y < 0 ? -1 : 1);
	}
	else
	{
		this->force.x = 0;
		this->force.y = 0;
	}
	this->acceleration.x += this->force.x / this->mass;
	this->acceleration.y += this->force.y / this->mass;
	this->accelerationRotation = (sqrt(this->force.x*this->force.x+this->force.y*this->force.y)* (dc.x < 0 ? -1 : 1)* (dc.y < 0 ? -1 : 1)) / this->mass;
	this->updateAccelerationRotation(this->root->getDt());
	this->movePhy();
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
	if(distance)
		return sf::Vector2f(sin((x - pos.x) / distance) * vx, sin((y - pos.y) / distance) * vy);
	return sf::Vector2f(0,0);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY)
{
	sf::Vector2f pos = this->getPosition();
	float distance = this->getDistance(sf::Vector2f(targetX, targetY));
	if(distance)
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

float Entity::getDistance(sf::Vector2f point, float metreAsPixel)
{
	const sf::Vector2f& middle = this->getMiddle();
	return sqrt((point.x - middle.x)*(point.x - middle.x) + (point.y - middle.y)*(point.y - middle.y)) * metreAsPixel;
}

float Entity::getDistance(Entity& other, float metreAsPixel)
{
	return this->getDistance(other.getMiddle(), metreAsPixel);
}

sf::Vector2f Entity::getDistanceComponent(sf::Vector2f point, float metreAsPixel)
{
	sf::Vector2f pos = this->getPosition();
	return sf::Vector2f((point.x - pos.x) * metreAsPixel, (point.y - pos.y) * metreAsPixel);
}

sf::Vector2f Entity::getDistanceComponent(Entity& other, float metreAsPixel)
{
	sf::Vector2f pos = other.getPosition();
	return this->getDistanceComponent(pos, metreAsPixel);
}

float Entity::getRotation()
{
	return this->shape->getRotation();
}

void Entity::setRotation(float angle)
{
	this->shape->setRotation(angle);
}

void Entity::setRotation(float targetX, float targetY)
{
	sf::Vector2f pos = this->getPosition();
	float angle = atan2(-(pos.y-targetY), -(pos.x-targetX))*180/3.141518;
	this->setRotation(angle);
}

void Entity::setRotation(Entity &other)
{
	sf::Vector2f pos = other.getPosition();
	this->setRotation(pos.x, pos.y);
}

void Entity::rotation(float angle)
{
	this->shape->setRotation(this->shape->getRotation() + angle);
}

void Entity::rotatePhy(bool deceleration)
{
	if(deceleration)
	{
		this->updateDecelerationRotation(this->root->getDt());
	}
	else
	{
		this->updateAccelerationRotation(this->root->getDt());
	}
	this->rotate(this->speedRotation);
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

void Entity::spirale(float vx, float vy, float angle, float targetX, float targetY)
{
	this->rotate(angle, targetX, targetY);
	this->moveToward(vx, vy, targetX, targetY);
}


void Entity::spirale(float vx, float vy, float angle, float targetX, float targetY, float timesec)
{
	this->rotate(angle, targetX, targetY, timesec);
	this->moveToward(vx, vy, targetX, targetY, timesec);
}

void Entity::spirale(float vx, float vy, float angle, float targetX, float targetY, float timeseca, float timesecx, float timesecy)
{
	this->rotate(angle, targetX, targetY, timeseca);
	this->moveToward(vx, vy, targetX, targetY, timesecx, timesecy);
}


void Entity::spirale(float vx, float vy, float angle, Entity &other)
{
	sf::Vector2f pos = other.getPosition();
	this->rotate(angle, pos.x, pos.y);
	this->moveToward(vx, vy, pos.x, pos.y);
}


void Entity::spirale(float vx, float vy, float angle, Entity &other, float timesec)
{
	sf::Vector2f pos = other.getPosition();
	this->rotate(angle, pos.x, pos.y, timesec);
	this->moveToward(vx, vy, pos.x, pos.y, timesec);
}

void Entity::spirale(float vx, float vy, float angle, Entity &other, float timeseca, float timesecx, float timesecy)
{
	sf::Vector2f pos = other.getPosition();
	this->rotate(angle, pos.x, pos.y, timeseca);
	this->moveToward(vx, vy, pos.x, pos.y, timesecx, timesecy);
}

void Entity::spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spirale(vx, vy, angle, targetX, targetY);
	}
	else
	{
		this->rotate(angle, targetX, targetY);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit, float timesec)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spirale(vx, vy, angle, targetX, targetY, timesec);
	}
	else
	{
		this->rotate(angle, targetX, targetY, timesec);
	}
}


void Entity::spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit, float timeseca, float timesecx, float timesecy)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spirale(vx, vy, angle, targetX, targetY, timeseca, timesecx, timesecy);
	}
	else
	{
		this->rotate(angle, targetX, targetY, timeseca);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, Entity &other, float limit)
{
	if(this->getDistance(other) > limit)
	{
		this->spirale(vx, vy, angle, other);
	}
	else
	{
		this->rotate(angle, other);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, Entity &other, float limit, float timesec)
{
	if(this->getDistance(other) > limit)
	{
		this->spirale(vx, vy, angle, other, timesec);
	}
	else
	{
		this->rotate(angle, other, timesec);
	}
}


void Entity::spiraleLimit(float vx, float vy, float angle, Entity &other, float limit, float timeseca, float timesecx, float timesecy)
{
	if(this->getDistance(other) > limit)
	{
		this->spirale(vx, vy, angle, other, timeseca, timesecx, timesecy);
	}
	else
	{
		this->rotate(angle, other, timeseca);
	}
}



