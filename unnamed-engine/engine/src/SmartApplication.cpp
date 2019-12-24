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
		GlobalInfo::offset = dynamic_cast<Application *>(so.object);
		if(not dynamic_cast<Application *>(so.object)->runNoWait())
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

void SmartApplication::updateAdding()
{
	if(toAdd)
	{
		for(auto se : addLaterList)
		{
			add(se);
		}
		addLaterList.clear();
		toAdd = false;
	}
}

void SmartApplication::drawEntities(sf::RenderWindow& window) const
{
	for(auto so : entities)
	{
		dynamic_cast<SystemEntity *>(so.object)->_view(window);
	}
}

void SmartApplication::update()
{
	updateAdding();
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

void SmartApplication::add(SmartObject& so)
{
	add(so.object, so.traits);
}

void SmartApplication::add(Dynamic& obj, SmartTrait traits)
{
	if(dynamic_cast<SystemEntity *>(&obj))
	{
		addEntity(dynamic_cast<SystemEntity *>(&obj), traits);
	}
	else if(dynamic_cast<Application *>(&obj))
	{
		addSubApplication(dynamic_cast<Application *>(&obj), traits);
	}
}

void SmartApplication::add(Dynamic* obj, SmartTrait traits)
{
	if(dynamic_cast<SystemEntity *>(obj))
	{
		addEntity(dynamic_cast<SystemEntity *>(obj), traits);
	}
	else if(dynamic_cast<Application *>(obj))
	{
		addSubApplication(dynamic_cast<Application *>(obj), traits);
	}
}

void SmartApplication::addEntity(SystemEntity& entity, SmartTrait traits)
{
	SmartObject sobj(&entity, traits);
	entities.push_back(sobj);
}

void SmartApplication::addEntity(SystemEntity* entity, SmartTrait traits)
{
	SmartObject sobj(entity, traits);
	entities.push_back(sobj);
}

void SmartApplication::addSubApplication(Application& subApp, SmartTrait traits)
{
	SmartObject sobj(&subApp, traits);
	subApp.load();
	subApplications.push_back(sobj);
}

void SmartApplication::addSubApplication(Application* subApp, SmartTrait traits)
{
	SmartObject sobj(subApp, traits);
	subApp->load();
	subApplications.push_back(sobj);
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
				delete dynamic_cast<SystemEntity *>(so.object);
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
				delete dynamic_cast<Application *>(so.object);
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

void SmartApplication::addLater(Dynamic& obj, SmartTrait traits)
{
	toAdd = true;
	addLaterList.push_back(SmartObject(&obj, traits));
}

void SmartApplication::addLater(Dynamic* obj, SmartTrait traits)
{
	toAdd = true;
	addLaterList.push_back(SmartObject(obj, traits));
}

int SmartApplication::countEntities() const
{
	return entities.size();
}

int SmartApplication::countSubApplications() const
{
	return subApplications.size();
}


SmartApplication& SmartApplication::operator<<(Dynamic& obj)
{
	addLater(obj);
	return *this;
}

SmartApplication& SmartApplication::operator<<(Dynamic* obj)
{
	addLater(obj, DELETABLE);
	return *this;
}

SmartApplication& SmartApplication::operator>>(Dynamic& obj)
{
	add(obj);
	return *this;
}

SmartApplication& SmartApplication::operator>>(Dynamic* obj)
{
	add(obj, DELETABLE);
	return *this;
}

void SmartApplication::flushEntities()
{
	for(auto so : entities)
	{
		if(so.deletable())
		{
			delete dynamic_cast<SystemEntity *>(so.object);
		}
	}
}

void SmartApplication::flushSubApplications()
{
	for(auto so : subApplications)
	{
		if(so.deletable())
		{
			delete dynamic_cast<Application *>(so.object);
		}
	}
}

void SmartApplication::flush()
{
	flushEntities();
	flushSubApplications();
}

SmartApplication::~SmartApplication()
{
	flush();
	trace("SmartApplication destruction");
	cout << "SystemEntities: " << SystemEntity::getSystemEntityCounter() << endl;
}
