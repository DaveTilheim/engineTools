#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "Updater.hpp"
#include "Application.hpp"
#include <SFML/Graphics.hpp>

namespace se
{
	class Entity : public Updater
	{
	protected:
		sf::RectangleShape shape;
		sf::Color bgColor;
		Application *root;
	public:
		Entity(float x, float y, float width, float height, Application *root, sf::Color bgColor=sf::Color::Red);
		virtual ~Entity();
		virtual void update() abstract;
		virtual void render();
		void setPosition(float x, float y);
		sf::RectangleShape &getShape();
		virtual void move(float vx, float vy); //per seconds
		virtual void move(float vx, float vy, float timesec); //per timesec
		virtual void move(float vx, float vy, float timesecx, float timesecy);
	};
}

#endif
