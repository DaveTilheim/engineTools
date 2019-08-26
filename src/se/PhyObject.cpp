#include "PhyObject.hpp"

using namespace se;

PhyObject::PhyObject()
: speed(0,0), acceleration(0,0), force(0,0), cineticEnergy(0,0), 
potentialEnergy(0,0), mecanicalEnergy(0,0), mass(0), gravity(0),
speedRotation(0), accelerationRotation(0)
{
	
}


void PhyObject::updateEnergy()
{
	this->cineticEnergy.x = 0.5 * this->mass * (this->speed.x * this->speed.x);
	this->cineticEnergy.y = 0.5 * this->mass * (this->speed.y * this->speed.y);
	this->mecanicalEnergy.x = this->cineticEnergy.x + this->potentialEnergy.x;
	this->mecanicalEnergy.y = this->cineticEnergy.y + this->potentialEnergy.y;
}

void PhyObject::updateForce()
{
	this->force.x = this->mass * this->acceleration.x;
	this->force.y = this->mass * this->acceleration.y;
}

void PhyObject::updateAcceleration(float dt)
{
	this->speed.x += this->acceleration.x * dt;
	this->speed.y += this->acceleration.y * dt;
	this->updateEnergy();
	this->updateForce();
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
	this->updateEnergy();
	this->updateForce();
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
	this->updateEnergy();
	this->updateForce();
}

void PhyObject::setSpeed(float vx, float vy)
{
	this->speed.x = vx;
	this->speed.y = vy;
	this->updateEnergy();
}

void PhyObject::setSpeed(sf::Vector2f speed)
{
	this->setSpeed(speed.x, speed.y);
}

void PhyObject::setAcceleration(float vx, float vy)
{
	this->acceleration.x = vx;
	this->acceleration.y = vy;
	this->updateForce();
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
	this->updateEnergy();
	this->updateForce();
}

void PhyObject::print()
{
	std::cout << "mass: " << this->mass << std::endl;
	std::cout << "speed: x: " << this->speed.x << " y: " << this->speed.y << std::endl;
	std::cout << "acceleration: x: " << this->acceleration.x << " y: " << this->acceleration.y << std::endl;
	std::cout << "force: x: " << this->force.x << " y: " << this->force.y << std::endl;
	std::cout << "cineticE: x: " << this->cineticEnergy.x << " y: " << this->cineticEnergy.y << std::endl;
	std::cout << "potentialE: x: " << this->potentialEnergy.x << " y: " << this->potentialEnergy.y << std::endl;
	std::cout << "mecanicE: x: " << this->mecanicalEnergy.x << " y: " << this->mecanicalEnergy.y << std::endl;
	std::cout << "gravity: " << this->gravity << std::endl << std::endl;
}
