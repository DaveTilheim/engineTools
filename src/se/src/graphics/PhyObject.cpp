#include "PhyObject.hpp"

using namespace se;

PhyObject::PhyObject()
: speed(0,0), acceleration(0,0),
speedRotation(0), accelerationRotation(0), gravity(0), mass(0)
{
	trace("PhyObject creation");
}

PhyObject::PhyObject(const PhyObject& cp)
{
	this->speed = cp.speed;
	this->acceleration = cp.acceleration;
	this->speedRotation = cp.speedRotation;
	this->accelerationRotation = cp.accelerationRotation;
	this->gravity = cp.gravity;
	this->mass = cp.mass;
	trace("PhyObject creation");
}

void PhyObject::updateAcceleration(float dt)
{
	this->speed.x += this->acceleration.x * dt;
	this->speed.y += this->acceleration.y * dt;
}

void PhyObject::updateDeceleration(float dt)
{
	this->speed.x -= this->acceleration.x * dt;
	this->speed.y -= this->acceleration.y * dt;
	if((this->acceleration.x > 0 && this->speed.x < 0) || (this->acceleration.x < 0 && this->speed.x > 0))
	{
		this->speed.x = 0;
		this->acceleration.x = 0;
	}
	if((this->acceleration.y > 0 && this->speed.y < 0) || (this->acceleration.y < 0 && this->speed.y > 0))
	{
		this->speed.y = 0;
		this->acceleration.y = 0;
	}
}

void PhyObject::updateAccelerationRotation(float dt)
{
	this->speedRotation += this->accelerationRotation * dt;
}

void PhyObject::updateDecelerationRotation(float dt)
{
	this->speedRotation -= this->accelerationRotation * dt;
	if((this->accelerationRotation > 0 && this->speedRotation < 0) || (this->accelerationRotation < 0 && this->speedRotation > 0))
	{
		this->speedRotation = 0;
		this->accelerationRotation = 0;
	}
}

void PhyObject::setMass(float mass)
{
	this->mass = mass;
}

void PhyObject::setSpeed(float vx, float vy)
{
	this->speed.x = vx;
	this->speed.y = vy;
}

void PhyObject::setSpeed(sf::Vector2f speed)
{
	this->setSpeed(speed.x, speed.y);
}

void PhyObject::setAcceleration(float vx, float vy)
{
	this->acceleration.x = vx;
	this->acceleration.y = vy;
}

void PhyObject::setAcceleration(sf::Vector2f acceleration)
{
	this->setAcceleration(acceleration.x, acceleration.y);
}

void PhyObject::setSpeedRotation(float angle)
{
	this->speedRotation	= angle;
}

void PhyObject::setAccelerationRotation(float angle)
{
	this->accelerationRotation = angle;
}

void PhyObject::setPhysic(float mass, float gravity, sf::Vector2f speed, sf::Vector2f acceleration, float rv, float ra)
{
	this->mass = mass;
	this->gravity = gravity;
	this->speed = speed;
	this->acceleration = acceleration;
	this->speedRotation = rv;
	this->accelerationRotation = ra;
}

sf::Vector2f &PhyObject::getSpeed()
{
	return this->speed;
}

sf::Vector2f &PhyObject::getAcceleration()
{
	return this->acceleration;
}

void PhyObject::print()
{
	std::cout << "mass: " << this->mass << std::endl;
	std::cout << "speed: x: " << this->speed.x << " y: " << this->speed.y << std::endl;
	std::cout << "acceleration: x: " << this->acceleration.x << " y: " << this->acceleration.y << std::endl;
	std::cout << "gravity: " << this->gravity << std::endl << std::endl;
}
