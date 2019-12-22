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

struct SmartObject
{
	SmartTrait traits;
	SystemEntity *entity;
	SmartObject(SystemEntity *entity, SmartTrait trait=NONE) : traits(trait), entity(entity)
	{

	}

	bool deletable() const
	{
		return traits & DELETABLE;
	}
};

class SmartApplication : public Application
{
private:
	vector<SmartObject> entities;
	vector<SystemEntity*> removeLaterList;
	bool toRemove = false;
	void updateEntities();
	void updateRemoving();
	void drawEntities(sf::RenderWindow& win) const;
	void removeEntity(SystemEntity* entity);
protected:
	SmartApplication& app;
	SmartApplication(string title="SmartApplication");
	SmartApplication(int width, int height, string title="SmartApplication");
	virtual void update() override;
	virtual void view(sf::RenderWindow& win) const override;
	virtual void load() override = 0;
	void add(SystemEntity& entity, SmartTrait traits=NONE);
	void add(SystemEntity* entity, SmartTrait traits=NONE);
	void addel(SystemEntity& entity);
	void addel(SystemEntity* entity);
	void removeLater(SystemEntity& entity);
	void removeLater(SystemEntity* entity);
	SmartTrait getTrait(const SystemEntity& entity) const;
	SmartTrait getTrait(const SystemEntity* entity) const;
public:
	virtual ~SmartApplication();
	SmartApplication& operator<<(SystemEntity& entity);
	SmartApplication& operator<<(SystemEntity* entity);
};

#endif
