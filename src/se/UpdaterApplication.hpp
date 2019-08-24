#ifndef __UPDATER_APPLICATION_HPP__
#define __UPDATER_APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Application.hpp"
#include "Entity.hpp"


namespace se
{
	class UpdaterApplication : public Application
	{
	protected:
		std::vector<Entity*> entityList;
		unsigned entityListSize;
		sf::Color bgColor;
		virtual void update();
		virtual void render();
	public:
		UpdaterApplication(double width, double height, std::string &title, sf::Color bgColor=sf::Color::Black);
		UpdaterApplication(std::string &title, sf::Color bgColor=sf::Color::Black);
		std::vector<Entity*> &getEntityList();
		void setBgColor(sf::Color color);
		void add(Entity *entity);
		void remove(Entity *entity);
		void clear();
		void flush();
	};
}

#endif
