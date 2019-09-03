#ifndef __UPDATER_APPLICATION_HPP__
#define __UPDATER_APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stdarg.h>
#include "Application.hpp"
#include "Entity.hpp"
#include "State.hpp"
#include "Timeline.hpp"


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
		unsigned entityListSize = 0;
		sf::Color bgColor;
		unsigned timelinesSize = 0;
		std::vector<Timeline *> timelines;
		unsigned statesSize = 0;
		std::vector<State *> states;
		unsigned removeLaterListSize = 0;
		std::vector<Entity *> removeLaterList;
		virtual void load() override;
		virtual void update() override;
		virtual void render() override;
	public:
		UpdaterApplication(double width, double height, std::string title, sf::Color bgColor=sf::Color::Black);
		UpdaterApplication(std::string title, sf::Color bgColor=sf::Color::Black);
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
		void add(const int n, ...);
		void remove(Entity *entity, bool del=true);
		void clear();
		void flush();
		void createTimeline(float second, std::function<void(Entity *)> lambda, Entity *target,bool end=false);
		void createTimeline(float second, std::function<void(Entity *)> lambda, bool end=false);
		void createTimeline(Timeline *tl);
		void createTimelines(const int n, ...);
		void createQueueTimelines(Entity *e, const int n, ...);
		void createQueueTimelines(std::vector<Timeline*> vtl, int i=0, Entity *e=nullptr);
		void createQueueTimelines(std::vector<void *> vtl, int i=0, Entity *e=nullptr);
		void removeTimeline(Entity *target);
		void removeTimeline(Timeline *target);
		void createState(std::string name,std::function<void(Entity *)> lambda, Entity *target,bool act=false);
		void createState(std::string name,std::function<void(Entity *)> lambda, bool act=false);
		void removeState(Entity *target);
		void setState(std::string name, bool state);
		void reverseState(std::string name);
		void removeLater(Entity *e);
		Entity *operator[](std::string name);
	};
	typedef UpdaterApplication UA;
}

#endif
