#ifndef SMARTAPPLICATION_HPP
#define SMARTAPPLICATION_HPP
#include "Application.hpp"
#include "SystemEntity.hpp"
#include <vector>


enum SmartTrait
{
	NONE = 		0x0000,
	DELETABLE = 0x0001
};

SmartTrait operator|(SmartTrait s1, SmartTrait s2);

template <class T> struct SmartObject
{
	SmartTrait traits;
	T *object;
	SmartObject(T *object, SmartTrait trait=NONE) : traits(trait), object(object) {}
	bool deletable() const {return traits & DELETABLE;}
};

class SmartApplication : public Application
{
private:
	vector<SmartObject<SystemEntity>> entities;
	vector<SmartObject<Application>> subApplications;
	vector<Dynamic*> removeLaterList;
	bool toRemove = false;
	void updateEntities();
	void updateRemoving();
	void updateSubApplications();
	void drawEntities(sf::RenderWindow& win) const;
	void remove(Dynamic *obj);
	void removeEntity(SystemEntity* entity);
	void removeSubApplication(Application* subApp);
	void flushEntities();
	void flushSubApplications();
protected:
	SmartApplication& app;
	virtual void update() override;
	virtual void view(sf::RenderWindow& win) const override;
	virtual void load() override = 0;
	void add(SystemEntity& entity, SmartTrait traits=NONE);
	void add(SystemEntity* entity, SmartTrait traits=NONE);
	void addel(SystemEntity& entity);
	void addel(SystemEntity* entity);
	void add(Application& entity, SmartTrait traits=NONE);
	void add(Application* entity, SmartTrait traits=NONE);
	void addel(Application& entity);
	void addel(Application* entity);
	void removeLater(Dynamic& entity);
	void removeLater(Dynamic* entity);
public:
	SmartApplication(string title="SmartApplication");
	SmartApplication(int width, int height, string title="SmartApplication");
	virtual ~SmartApplication();
	SmartApplication& operator<<(SystemEntity& entity);
	SmartApplication& operator<<(SystemEntity* entity);
	SmartApplication& operator<<(Application& subApp);
	SmartApplication& operator<<(Application* subApp);
};

#endif
