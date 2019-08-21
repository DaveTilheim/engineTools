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
		void setPosition(float x, float y);
		void setOrigin(float x, float y);
		sf::Vector2f getPosition();
		sf::Vector2f getOrigin();
		virtual void move(float vx, float vy); //per seconds
		virtual void move(float vx, float vy, float timesec); //per timesec
		virtual void move(float vx, float vy, float timesecx, float timesecy);
		virtual float getDistance(sf::Vector2f point);
		virtual float getDistance(Entity& other);
		virtual sf::Vector2f getMiddle() abstract;
	};
}

#endif
