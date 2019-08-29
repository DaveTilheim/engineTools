#include "UpdaterApplication.hpp"

using namespace se;

UpdaterApplication::UpdaterApplication(double width, double height, std::string &title, sf::Color bgColor)
:					Application(width, height, title), bgColor(bgColor), entityListSize(0), timelinesSize(0)
{

}

UpdaterApplication::UpdaterApplication(std::string &title, sf::Color bgColor)
:					Application(title), bgColor(bgColor), entityListSize(0)
{

}

void UpdaterApplication::load()
{

}

void UpdaterApplication::identify(std::string id, Entity *entity)
{
	this->entityMap[id] = entity;
}

Entity *UpdaterApplication::identify(std::string id)
{
	return this->entityMap[id];
}

void UpdaterApplication::identify(std::string listName, std::string entityName, Entity *entity)
{
	if(this->entityListMap.find(listName) == this->entityListMap.end())
	{
		this->entityListMap[listName] = new std::map<std::string, Entity *>();
		this->entityNamedList[listName] = new std::vector<Entity *>();
	}
	(*this->entityListMap[listName])[entityName] = entity;
	identify(listName+"/"+entityName, entity);
	this->entityNamedList[listName]->push_back(entity);
}

Entity *UpdaterApplication::identify(std::string listName, std::string entityName)
{
	return (*this->entityListMap[listName])[entityName];
}

std::vector<Entity *> *UpdaterApplication::identifyList(std::string name)
{
	return this->entityNamedList[name];
}

void UpdaterApplication::add(Entity *entity)
{
	this->entityList.push_back(entity);
	entityListSize++;
}

void UpdaterApplication::removeTimeline(Entity *target)
{
	for(int i = 0; i < this->timelinesSize; i++)
	{
		if(this->timelines[i]->target == target)
		{
			delete this->timelines[i];
			this->timelines.erase(this->timelines.begin()+i);
			this->timelinesSize--;
			i--;
		}
	}
}

void UpdaterApplication::removeTimeline(Timeline *target)
{
	for(int i = 0; i < this->timelinesSize; i++)
	{
		if(this->timelines[i] == target)
		{
			delete this->timelines[i];
			this->timelines.erase(this->timelines.begin()+i);
			this->timelinesSize--;
			break;
		}
	}
}

void UpdaterApplication::remove(Entity *entity, bool del)
{
	int i;
	this->removeTimeline(entity);
	for(i = 0; i < this->entityListSize; i++)
	{
		if(this->entityList[i] == entity)
		{
			break;
		}
	}
	if(del) delete entity;
	this->entityList.erase(this->entityList.begin()+i);
	this->entityListSize--;
	for(std::map<std::string, std::vector<Entity *> *>::iterator it = this->entityNamedList.begin() ; it!=this->entityNamedList.end() ; it++)
	{
		std::string key = it->first;
		std::vector<Entity *> *vec = it->second;
		int size = vec->size();
		for(i = 0; i < size; i++)
		{
			if((*vec)[i] == entity)
			{
				vec->erase(vec->begin()+i);
				break;
			}
		}
		std::cerr << key << std::endl;
		std::map<std::string, Entity *> *m = this->entityListMap[key];
		std::cerr << m << std::endl;
		for(std::map<std::string, Entity *>::iterator it2 = m->begin(); it2 != m->end(); it2++)
		{
			std::string key2 = it2->first;
			Entity *e = it2->second;
			if((*m)[key2] == entity)
			{
				m->erase(key2);
				this->entityMap.erase(key2);
				break;
			}
		}
	}
}

void UpdaterApplication::clear()
{
	this->entityList.clear();
	this->entityMap.clear();
	for(std::map<std::string, std::vector<Entity *> *>::iterator it = this->entityNamedList.begin() ; it!=this->entityNamedList.end() ; it++)
	{
		std::vector<Entity *> *v = it->second;
		v->clear();
		delete v;
	}
	for(std::map<std::string, std::map<std::string, Entity *> *>::iterator it = this->entityListMap.begin() ; it!=this->entityListMap.end() ; it++)
	{
		std::map<std::string, Entity *> *m = it->second;
		m->clear();
		delete m;
	}
	this->entityNamedList.clear();
	this->entityListMap.clear();
}

void UpdaterApplication::flush()
{
	int i;
	for(i = 0; i < this->entityListSize; i++)
	{
		delete this->entityList[i];
	}
	this->clear();
}

std::vector<Entity*> &UpdaterApplication::getEntityList()
{
	return this->entityList;
}

std::map<std::string, Entity*> &UpdaterApplication::getEntityMap()
{
	return this->entityMap;
}

void UpdaterApplication::setBgColor(sf::Color color)
{
	this->bgColor = color;
}

void UpdaterApplication::update()
{
	int i;
	for(i = 0; i < this->entityListSize; i++)
	{
		this->entityList[i]->update();
	}
	for(i = 0; i < this->timelinesSize; i++)
	{
		this->timelines[i]->update();
		if(this->timelines[i]->isTerminated())
		{
			this->removeTimeline(this->timelines[i]);
			i--;
		}
	}
}

void UpdaterApplication::render()
{
	int i;
	this->fill(this->bgColor);
	for(i = 0; i < this->entityListSize; i++)
	{
		this->entityList[i]->render();
	}
	this->display();
}

UpdaterApplication::~UpdaterApplication()
{
	int size = this->timelines.size();
	for(int i = 0; i < size; i++)
	{
		delete this->timelines[i];
	}
}

void UpdaterApplication::createTimeline(float second, void (*callback)(Entity *), Entity *target, bool end)
{
	Timeline *tl = new Timeline(second, callback, target, end);
	this->timelines.push_back(tl);
	this->timelinesSize++;
}
