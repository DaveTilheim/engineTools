#ifndef __PHY_OBJECT_HPP__
#define __PHY_OBJECT_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "PhyConst.hpp"

namespace se
{
	class PhyObject
	{
	protected:
		sf::Vector2f speed;
		sf::Vector2f acceleration;
		float speedRotation;
		float accelerationRotation;
		sf::Vector2f force;
		sf::Vector2f cineticEnergy;
		sf::Vector2f potentialEnergy;
		sf::Vector2f mecanicalEnergy;
		float gravity;
		float mass;
		void updateEnergy();
		void updateForce();
		void updateAcceleration(float dt = 1);
		void updateDeceleration(float dt = 1);
		void updateAccelerationRotation(float dt = 1);
		void updateDecelerationRotation(float dt = 1);
	public:
		PhyObject();
		void setMass(float mass);
		void setSpeed(float vx, float vy);
		void setSpeed(sf::Vector2f speed);
		void setSpeedRotation(float angle);
		void setAcceleration(float vx, float vy);
		void setAcceleration(sf::Vector2f acceleration);
		void setAccelerationRotation(float angle);
		void setPhysic(float mass, float gravity, sf::Vector2f speed=sf::Vector2f(0,0), sf::Vector2f acceleration = sf::Vector2f(0,0),float rv = 0, float ra=0);
		void print();
	};
}

#endif
