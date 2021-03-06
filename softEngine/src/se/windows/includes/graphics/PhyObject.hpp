#ifndef PHY_OBJECT_HPP
#define PHY_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../includes/system/debug.hpp"
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
		float gravity;
		float mass;
		void updateAcceleration(float dt = 1);
		void updateDeceleration(float dt = 1);
		void updateAccelerationRotation(float dt = 1);
		void updateDecelerationRotation(float dt = 1);
	public:
		PhyObject();
		PhyObject(const PhyObject&);
		void setMass(float mass);
		void setSpeed(float vx, float vy);
		void setSpeed(sf::Vector2f speed);
		void setSpeedRotation(float angle);
		void setAcceleration(float vx, float vy);
		void setAcceleration(sf::Vector2f acceleration);
		void setAccelerationRotation(float angle);
		void setPhysic(float mass, float gravity, sf::Vector2f speed=sf::Vector2f(0,0), sf::Vector2f acceleration = sf::Vector2f(0,0),float rv = 0, float ra=0);
		sf::Vector2f &getSpeed();
		sf::Vector2f &getAcceleration();
		void print();
	};
}

#endif
