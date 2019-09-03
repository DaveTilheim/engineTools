#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "Updater.hpp"
#include "Application.hpp"
#include "PhyObject.hpp"
#include <cstdarg>
#include <SFML/Graphics.hpp>

namespace se
{
	class Entity : public Updater, public PhyObject
	{
	protected:
		sf::Shape *shape;
		std::map<std::string, sf::Texture *> textures;
		std::string currentTexture;
		sf::Color bgColor;
		Application *root;
	public:
		Entity(float x, float y, float width, float height, Application *root, sf::Color bgColor=sf::Color::White);
		Entity(float x, float y, float radius, Application *root, sf::Color bgColor=sf::Color::White);
		virtual ~Entity();
		virtual void update() override abstract;
		virtual void render() override;
		virtual void setPosition(float x, float y);
		virtual void setRotatePosition(sf::Vector2f ref, float angle, float distance, float originMarginAngle=0.0);
		virtual void setOrigin(float x, float y);
		virtual void setMiddleOrigin() abstract;
		virtual void setScale(float sx, float sy) abstract;
		sf::Vector2f getPosition();
		sf::Vector2f getOrigin();
		float getRotation();
		float getRotation(float x, float y);
		template <class T> T* getRoot();
		template <class T> void remove(bool=true);
		template <class T> void removeLater();
		virtual void movePhy(bool deceleration=false);
		virtual void movePhy(sf::Vector2f speed, sf::Vector2f target);
		virtual void movePhy(sf::Vector2f speed, Entity &target);
		virtual void movePhy(Entity &other, float metreAsPixel=1); // by mass
		virtual void movePhy(std::vector<Entity *> &others, float metreAsPixel=1); // by mass
		virtual void moveGrav(Entity &other); // by gravity
		virtual void moveGrav(std::vector<Entity *> &others); // by gravity
		virtual void move(float vx, float vy); //per second
		virtual void move(float vx, float vy, float timesec); //per timesec
		virtual void move(float vx, float vy, float timesecx, float timesecy);
		virtual void moveToward(float vx, float vy, float targetX, float targetY);
		virtual void moveToward(float vx, float vy, float targetX, float targetY, float timesec);
		virtual void moveToward(float vx, float vy, float targetX, float targetY, float timesecx, float timesecy);
		virtual void moveToward(float vx, float vy, Entity &other);
		virtual void moveToward(float vx, float vy, Entity &other, float timesec);
		virtual void moveToward(float vx, float vy, Entity &other, float timesecx, float timesecy);
		virtual float getDistance(sf::Vector2f point, float metreAsPixel=1);
		virtual float getDistance(Entity& other, float metreAsPixel=1);
		virtual sf::Vector2f getDistanceComponent(sf::Vector2f point, float metreAsPixel=1);
		virtual sf::Vector2f getDistanceComponent(Entity& other, float metreAsPixel=1);
		virtual sf::Vector2f getComponent(float vx, float vy, float x, float y);
		virtual void setRotation(float angle);
		virtual void setRotation(float targetX, float targetY);
		virtual void setRotation(Entity &other);
		virtual void rotation(float angle);
		virtual void rotateToward(float va, float x, float y); // ???
		virtual void rotatePhy(bool deceleration=false);
		virtual void rotate(float angle); //per second
		virtual void rotate(float angle, float timesec); //per timesec
		virtual void rotate(float angle, float targetX, float targetY); //per second
		virtual void rotate(float angle, float targetX, float targetY, float timesec); //per timesec
		virtual void rotate(float angle, Entity &other); //per second
		virtual void rotate(float angle, Entity &other, float timesec); //per timesec
		virtual void spirale(float vx, float vy, float angle, float targetX, float targetY); // per second
		virtual void spirale(float vx, float vy, float angle, float targetX, float targetY, float timesec); // per timesec
		virtual void spirale(float vx, float vy, float angle, float targetX, float targetY, float timeseca, float timesecx, float timesecy); // per timesec
		virtual void spirale(float vx, float vy, float angle, Entity &other);
		virtual void spirale(float vx, float vy, float angle, Entity &other, float timesec);
		virtual void spirale(float vx, float vy, float angle, Entity &other, float timeseca, float timesecx, float timesecy);
		virtual void spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit);
		virtual void spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit, float timesec);
		virtual void spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit, float timeseca, float timesecx, float timesecy);
		virtual void spiraleLimit(float vx, float vy, float angle, Entity &other, float limit);
		virtual void spiraleLimit(float vx, float vy, float angle, Entity &other, float limit, float timesec);
		virtual void spiraleLimit(float vx, float vy, float angle, Entity &other, float limit, float timeseca, float timesecx, float timesecy);
		template <class T> void state(std::string name,  std::function<void(Entity *)> lambda, bool act=false);
		template <class T> void doDuring(float second, std::function<void(Entity *)> lambda);
		template <class T> void doAfterDuring(float second, std::function<void(Entity *)> lambda);
		template <class T> void setState(std::string name, bool state);
		template <class T> void reverseState(std::string name);
		template <class T> void doStepByStep(int n, ...);
		void addTexture(std::string name, std::string filename);
		virtual void setTexture(std::string name);
		virtual sf::Vector2f getMiddle() abstract;
	};

	template <class T>
	void Entity::setState(std::string name, bool state)
	{
		this->getRoot<T>()->setState(name, state);
	}

	template <class T>
	void Entity::reverseState(std::string name)
	{
		this->getRoot<T>()->reverseState(name);
	}

	template <class T>
	void Entity::state(std::string name, std::function<void(Entity *)> lambda, bool act)
	{
		this->getRoot<T>()->createState(name, lambda, this, act);
	}

	template <class T> T *Entity::getRoot()
	{
		return dynamic_cast<T*>(this->root);
	}

	template <class T> void Entity::remove(bool del)
	{
		this->getRoot<T>()->remove(this, del);
	}

	template <class T> void Entity::removeLater()
	{
		this->getRoot<T>()->removeLater(this);
	}

	template <class T> void Entity::doDuring(float second, std::function<void(Entity *)> lambda)
	{
		this->getRoot<T>()->createTimeline(second, lambda, this, false);
	}

	template <class T> void Entity::doAfterDuring(float second, std::function<void(Entity *)> lambda)
	{
		this->getRoot<T>()->createTimeline(second, lambda, this, true);
	}

	template <class T> void Entity::doStepByStep(int n, ...)
	{
		std::vector<void *> *tls = new std::vector<void *>();
		va_list args;
		va_start(args, n);
		for(int i = 0; i < n; i++)
		{
			tls->push_back(va_arg(args, void *));
		}
		va_end(args);
		this->getRoot<T>()->createQueueTimelines(*tls, 0,this);
		delete tls;
	}
}

#endif
