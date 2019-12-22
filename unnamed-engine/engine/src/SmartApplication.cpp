#include "SmartApplication.hpp"


SmartTrait operator|(SmartTrait s1, SmartTrait s2)
{
	return (SmartTrait)((int)s1 | (int)s2);
}

SmartApplication::SmartApplication(string title) : Application(title), app(*this)
{

}

SmartApplication::SmartApplication(int width, int height, string title) : Application(width, height, title), app(*this)
{

}

void SmartApplication::updateEntities()
{
	for(auto so : entities)
	{
		so.entity->_update();
	}
}

void SmartApplication::updateRemoving()
{
	if(toRemove)
	{
		for(auto se : removeLaterList)
		{
			removeEntity(se);
		}
		removeLaterList.clear();
		toRemove = false;
	}
}

void SmartApplication::drawEntities(sf::RenderWindow& window) const
{
	for(auto so : entities)
	{
		so.entity->_view(window);
	}
}

void SmartApplication::update()
{
	updateEntities();
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

void SmartApplication::removeEntity(SystemEntity* entity)
{
	int i = 0;
	for(auto so : entities)
	{
		if(so.entity == entity)
		{
			if(so.deletable())
			{
				delete so.entity;
			}
			entities.erase(entities.begin() + i);
			break;
		}
		i++;
	}
}

void SmartApplication::removeLater(SystemEntity& entity)
{
	toRemove = true;
	removeLaterList.push_back(&entity);
}

void SmartApplication::removeLater(SystemEntity* entity)
{
	toRemove = true;
	removeLaterList.push_back(entity);
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

SmartTrait SmartApplication::getTrait(const SystemEntity& entity) const
{
	for(auto so : entities)
	{
		if(so.entity == &entity)
		{
			return so.traits;
		}
	}
	return NONE;
}

SmartTrait SmartApplication::getTrait(const SystemEntity* entity) const
{
	for(auto so : entities)
	{
		if(so.entity == entity)
		{
			return so.traits;
		}
	}
	return NONE;
}

SmartApplication::~SmartApplication()
{
	for(auto so : entities)
	{
		if(so.deletable())
		{
			delete so.entity;
		}
	}
}
