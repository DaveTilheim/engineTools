#ifndef UPDATER_APPLICATION_HPP
#define UPDATER_APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stdarg.h>
#include "Application.hpp"
#include "../../includes/graphics/Entity.hpp"
#include "State.hpp"
#include "Timeline.hpp"
#include "Utilities.hpp"
#include "../../includes/graphics/RenderLayout.hpp"
#include "../../includes/graphics/KeyCatcher.hpp"
#include "../../includes/graphics/Shader.hpp"
#include "Conditional.hpp"


namespace se
{
	class UpdaterApplication : public Application
	{
	private:
		void updateConditionals();
		void updateStates();
		void updateShaders();
		void updateTimelines();
		void updateEntities();
		void updateRemoveLaterConditionals();
		void updateRemoveLater();
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
		std::map<std::string, sf::Font *> fontMap;
		unsigned keyCatcherListSize = 0;
		std::vector<KeyCatcher *> keyCatchers;
		unsigned shaderListSize = 0;
		std::vector<Shader *>shaderList;
		std::map<std::string, Conditional *> conditionalMap;
		std::vector<std::string> removeLaterConditionalList;
		unsigned removeLaterConditionalListSize = 0;
		virtual void load() override;
		virtual void update() override;
		virtual void render() override;
		virtual void textEnteredEventHandler(const sf::Event& event) override final;
	public:
		UpdaterApplication &app;
		sf::Vector2i mp;
		UpdaterApplication(double width, double height, std::string title, sf::Color bgColor=sf::Color::Black);
		UpdaterApplication(std::string title, sf::Color bgColor=sf::Color::Black);
		virtual ~UpdaterApplication();
		std::vector<Entity*> &getEntityList();
		std::map<std::string, Entity*> &getEntityMap();
		void setBgColor(sf::Color color);
		void identify(std::string id, Entity *entity);
		Entity *identify(std::string id);
		template <class T> T *identify(std::string id);
		void identify(std::string listName, std::string entityName, Entity *entity);
		Entity *identify(std::string listName, std::string entityName);
		template <class T> T *identify(std::string listName, std::string entityName);
		std::vector<Entity *> *identifyList(std::string name);
		void identifyList(std::string listName, std::string name);
		void add(Entity *entity);
		void add(Entity *entity, std::string layout);
		void add(const int n, ...);
		void add(KeyCatcher *kc);
		void add(KeyCatcher *kc, std::string layout);
		void addKeyCatcher(KeyCatcher *kc);
		void addKeyCatcher(KeyCatcher *kc, std::string layout);
		void removeKeyCatcher(KeyCatcher *kc);
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
		void copyTimelines(Entity&, const Entity&);
		void createState(std::string name,std::function<void(Entity *)> lambda, Entity *target,bool act=false);
		void createState(std::string name,std::function<void(Entity *)> lambda, bool act=false);
		void createState(State *state);
		State *getState(std::string name);
		State *getState(std::string name, Entity *target);
		void removeState(Entity *target);
		void setState(std::string name, bool state);
		void reverseState(std::string name);
		void setState(std::string name, bool state, Entity *target);
		void reverseState(std::string name, Entity *entity);
		void copyStates(Entity&, const Entity&);
		void removeLater(Entity *e);
		sf::Font *addFont(std::string fontid, std::string fontname);
		sf::Font *getFont(std::string fontid);
		void layout(std::string, Entity *e);
		Entity *operator[](std::string name);
		void addShader(Shader& shader);
		void removeEntityInShader(const Entity&);
		Shader *getShader(std::string name);
		void removeShader(std::string name);
		void addConditional(std::string id, Conditional *c);
		void removeConditional(std::string id);
		void removeLaterConditional(std::string id);
		void moveAll(int vx, int vy, std::string listName="");
		UpdaterApplication& operator<<(Entity *e);
		UpdaterApplication& operator<<(KeyCatcher *e);
		void operator<<(std::string layout);
	};

	template <class T>
	T *UpdaterApplication::identify(std::string id)
	{
		return this->entityMap.find(id) != this->entityMap.end() ? dynamic_cast<T *>(this->entityMap[id]) : nullptr;
	}

	template <class T>
	T *UpdaterApplication::identify(std::string listName, std::string entityName)
	{
		if(this->entityListMap.find(listName) != this->entityListMap.end())
		{
			return (*this->entityListMap[listName]).find(entityName) != (*this->entityListMap[listName]).end() ? dynamic_cast<T *>((*this->entityListMap[listName])[entityName]) : nullptr;
		}
		return nullptr;
	}

	typedef UpdaterApplication UA;
}

#endif
