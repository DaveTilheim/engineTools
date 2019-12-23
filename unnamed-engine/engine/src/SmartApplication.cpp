#include "SmartApplication.hpp"


SmartTrait operator|(SmartTrait s1, SmartTrait s2)
{
	return (SmartTrait)((int)s1 | (int)s2);
}

SmartApplication::SmartApplication(string title) : Application(title), app(*this)
{
	trace("SmartApplication creation");
}

SmartApplication::SmartApplication(int width, int height, string title) : Application(width, height, title), app(*this)
{
	trace("SmartApplication creation");
}

void SmartApplication::updateEntities()
{
	for(auto so : entities)
	{
		so.object->_update();
	}
}

void SmartApplication::updateSubApplications()
{
	for(auto so : subApplications)
	{
		GlobalInfo::offset = so.object;
		if(not so.object->runNoWait())
		{
			removeLater(so.object);
		}
	}
	GlobalInfo::offset = this;
}

void SmartApplication::updateRemoving()
{
	if(toRemove)
	{
		for(auto se : removeLaterList)
		{
			remove(se);
		}
		removeLaterList.clear();
		toRemove = false;
	}
}

void SmartApplication::drawEntities(sf::RenderWindow& window) const
{
	for(auto so : entities)
	{
		so.object->_view(window);
	}
}

void SmartApplication::update()
{
	updateEntities();
	updateSubApplications();
	updateRemoving();
}

void SmartApplication::view(sf::RenderWindow& window) const
{
	fill(getBackgroundColor());
	drawEntities(window);
	refresh();
}

void SmartApplication::add(SystemEntity& entity, SmartTrait traits)
{
	SmartObject obj(&entity, traits);
	entities.push_back(obj);
}

void SmartApplication::add(SystemEntity* entity, SmartTrait traits)
{
	SmartObject obj(entity, traits);
	entities.push_back(obj);
}

void SmartApplication::addel(SystemEntity& entity)
{
	SmartObject obj(&entity, DELETABLE);
	entities.push_back(obj);
}

void SmartApplication::addel(SystemEntity* entity)
{
	SmartObject obj(entity, DELETABLE);
	entities.push_back(obj);
}

void SmartApplication::add(Application& subApp, SmartTrait traits)
{
	SmartObject obj(&subApp, traits);
	subApp.load();
	subApplications.push_back(obj);
}

void SmartApplication::add(Application* subApp, SmartTrait traits)
{
	SmartObject obj(subApp, traits);
	subApp->load();
	subApplications.push_back(obj);
}

void SmartApplication::addel(Application& subApp)
{
	SmartObject obj(&subApp, DELETABLE);
	subApp.load();
	subApplications.push_back(obj);
}

void SmartApplication::addel(Application* subApp)
{
	SmartObject obj(subApp, DELETABLE);
	subApp->load();
	subApplications.push_back(obj);
}

void SmartApplication::remove(Dynamic *obj)
{
	if(dynamic_cast<SystemEntity *>(obj))
	{
		removeEntity(dynamic_cast<SystemEntity *>(obj));
	}
	else if(dynamic_cast<Application *>(obj))
	{
		removeSubApplication(dynamic_cast<Application *>(obj));
	}
}

void SmartApplication::removeEntity(SystemEntity* entity)
{
	int i = 0;
	for(auto so : entities)
	{
		if(so.object == entity)
		{
			if(so.deletable())
			{
				delete so.object;
			}
			entities.erase(entities.begin() + i);
			break;
		}
		i++;
	}
}

void SmartApplication::removeSubApplication(Application* subApp)
{
	int i = 0;
	for(auto so : subApplications)
	{
		if(so.object == subApp)
		{
			if(so.deletable())
			{
				delete so.object;
			}
			subApplications.erase(subApplications.begin() + i);
			break;
		}
		i++;
	}
}

void SmartApplication::removeLater(Dynamic& obj)
{
	toRemove = true;
	removeLaterList.push_back(&obj);
}

void SmartApplication::removeLater(Dynamic* obj)
{
	toRemove = true;
	removeLaterList.push_back(obj);
}


SmartApplication& SmartApplication::operator<<(SystemEntity& entity)
{
	add(entity);
	return *this;
}

SmartApplication& SmartApplication::operator<<(SystemEntity* entity)
{
	addel(entity);
	return *this;
}

SmartApplication& SmartApplication::operator<<(Application& sub)
{
	add(sub);
	return *this;
}

SmartApplication& SmartApplication::operator<<(Application* sub)
{
	addel(sub);
	return *this;
}

void SmartApplication::flushEntities()
{
	for(auto so : entities)
	{
		if(so.deletable())
		{
			delete so.object;
		}
	}
}

void SmartApplication::flushSubApplications()
{
	for(auto so : subApplications)
	{
		if(so.deletable())
		{
			delete so.object;
		}
	}
}

SmartApplication::~SmartApplication()
{
	flushEntities();
	flushSubApplications();
	trace("SmartApplication destruction");
}
