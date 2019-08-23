#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "Updater.hpp"
#include "Application.hpp"
#include <SFML/Graphics.hpp>

typedef sf::RectangleShape Rectangle;
typedef sf::CircleShape Circle;

namespace se
{
	class Entity : public Updater
	{
	protected:
		sf::Shape *shape;
		sf::Color bgColor;
		Application *root;
	public:
		Entity(float x, float y, float width, float height, Application *root, sf::Color bgColor=sf::Color::Red);
		Entity(float x, float y, float radius, Application *root, sf::Color bgColor=sf::Color::Red);
		virtual ~Entity();
		virtual void update() abstract;
		virtual void render();
		virtual void setPosition(float x, float y);
		virtual void setOrigin(float x, float y);
		sf::Vector2f getPosition();
		sf::Vector2f getOrigin();
		float getRotation();
		virtual void move(float vx, float vy); //per second
		virtual void move(float vx, float vy, float timesec); //per timesec
		virtual void move(float vx, float vy, float timesecx, float timesecy);
		virtual float getDistance(sf::Vector2f point);
		virtual float getDistance(Entity& other);
		virtual void setRotation(float angle);
		virtual void rotation(float angle);
		virtual void rotate(float angle); //per second
		virtual void rotate(float angle, float timesec); //per timesec
		virtual void rotate(float angle, float targetX, float targetY); //per second
		virtual void rotate(float angle, float targetX, float targetY, float timesec); //per timesec
		virtual void rotate(float angle, Entity &other); //per second
		virtual void rotate(float angle, Entity &other, float timesec); //per timesec
		virtual sf::Vector2f getMiddle() abstract;
	};
}

#endif
