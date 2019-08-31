#ifndef __UPDATER_APPLICATION_HPP__
#define __UPDATER_APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Application.hpp"
#include "Entity.hpp"
#include "Timeline.hpp"
#include "State.hpp"

namespace se
{
	class UpdaterApplication : public Application
	{
	private:
		State *getState(std::string name);
	protected:
		std::vector<Entity*> entityList;
		std::map<std::string, std::vector<Entity *> *> entityNamedList;
		std::map<std::string, Entity*> entityMap;
		std::map<std::string, std::map<std::string, Entity *> *> entityListMap;
		unsigned entityListSize;
		sf::Color bgColor;
		unsigned timelinesSize;
		std::vector<Timeline *> timelines;
		unsigned statesSize;
		std::vector<State *> states;
		virtual void load();
		virtual void update();
		virtual void render();
	public:
		UpdaterApplication(double width, double height, std::string &title, sf::Color bgColor=sf::Color::Black);
		UpdaterApplication(std::string &title, sf::Color bgColor=sf::Color::Black);
		~UpdaterApplication();
		std::vector<Entity*> &getEntityList();
		std::map<std::string, Entity*> &getEntityMap();
		void setBgColor(sf::Color color);
		void identify(std::string id, Entity *entity);
		Entity *identify(std::string id);
		void identify(std::string listName, std::string entityName, Entity *entity);
		Entity *identify(std::string listName, std::string entityName);
		std::vector<Entity *> *identifyList(std::string name);
		void identifyList(std::string listName, std::string name);
		void add(Entity *entity);
		void remove(Entity *entity, bool del=true);
		void clear();
		void flush();
		void createTimeline(float second, void (*callback)(Entity *), Entity *target, bool end=false);
		void removeTimeline(Entity *target);
		void removeTimeline(Timeline *target);
		void createState(std::string name, void (*callback)(Entity *), Entity *target, bool act=false);
		void removeState(Entity *target);
		void setState(std::string name, bool state);
		void reverseState(std::string name);
	};
	typedef UpdaterApplication UA;
}

#endif
