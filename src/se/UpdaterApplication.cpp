#include "UpdaterApplication.hpp"

using namespace se;

UpdaterApplication::UpdaterApplication(double width, double height, std::string title, sf::Color bgColor)
:					Application(width, height, title)
					, entityListSize(0), bgColor(bgColor), timelinesSize(0), statesSize(0),
					removeLaterListSize(0), mp(0,0)
{
	trace("UpdaterApplication creation");
}

UpdaterApplication::UpdaterApplication(std::string title, sf::Color bgColor)
:					Application(title)
					,entityListSize(0), bgColor(bgColor), timelinesSize(0), statesSize(0),
					removeLaterListSize(0), mp(0,0)
{
	trace("UpdaterApplication creation");
}

void UpdaterApplication::load()
{

}

void UpdaterApplication::identify(std::string id, Entity *entity)
{
	this->entityMap[id] = entity;
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

Entity *UpdaterApplication::identify(std::string id)
{
	return this->entityMap.find(id) != this->entityMap.end() ? this->entityMap[id] : nullptr;
}

Entity *UpdaterApplication::identify(std::string listName, std::string entityName)
{
	if(this->entityListMap.find(listName) != this->entityListMap.end())
	{
		return (*this->entityListMap[listName]).find(entityName) != (*this->entityListMap[listName]).end() ? (*this->entityListMap[listName])[entityName] : nullptr;
	}
	return nullptr;
}

std::vector<Entity *> *UpdaterApplication::identifyList(std::string name)
{
	return this->entityNamedList.find(name) != this->entityNamedList.end() ? this->entityNamedList[name] :nullptr;
}

void UpdaterApplication::add(Entity *entity)
{
	this->entityList.push_back(entity);
	entityListSize++;
}

void UpdaterApplication::add(const int n, ...)
{
	va_list args;
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		this->add(va_arg(args, Entity *));
	}
	va_end(args);
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

void UpdaterApplication::removeState(Entity *target)
{
	for(int i = 0; i < this->statesSize; i++)
	{
		if(this->states[i]->target == target)
		{
			delete this->states[i];
			this->states.erase(this->states.begin()+i);
			this->statesSize--;
			i--;
		}
	}
}

void UpdaterApplication::remove(Entity *entity, bool del)
{
	int i;
	this->removeTimeline(entity);
	this->removeState(entity);
	bool in = false;
	if(del) delete entity;
	for(i = 0; i < this->entityListSize; i++)
	{
		if(this->entityList[i] == entity)
		{
			in = true;
			break;
		}
	}
	if(in)
	{
		this->entityList.erase(this->entityList.begin()+i);
		this->entityListSize--;
	}
	
	for(auto it = this->entityNamedList.begin() ; it!=this->entityNamedList.end() ; it++)
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
		for(auto it2 = m->begin(); it2 != m->end(); it2++)
		{
			std::string key2 = it2->first;
			if((*m)[key2] == entity)
			{
				m->erase(key2);
				break;
			}
		}
	}
	for(auto it = this->entityMap.begin(); it != this->entityMap.end(); ++it)
	{
		if(entity == it->second)
		{
			this->entityMap.erase(it->first);
			break;
		}
	}
}

void UpdaterApplication::clear()
{
	this->entityList.clear();
	this->entityMap.clear();
	for(auto it = this->entityNamedList.begin() ; it!=this->entityNamedList.end() ; it++)
	{
		std::vector<Entity *> *v = it->second;
		v->clear();
		delete v;
	}
	for(auto it = this->entityListMap.begin() ; it!=this->entityListMap.end() ; it++)
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
	for(i = 0; i < this->statesSize; i++)
	{
		this->states[i]->update();
	}
	for(i = 0; i < this->removeLaterListSize; i++)
	{
		this->remove(this->removeLaterList[i]);
	}
	if(i)
	{
		this->removeLaterList.clear();
		this->removeLaterListSize = 0;
	}
	this->mp = util::getMousePosition();
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

void UpdaterApplication::removeLater(Entity *e)
{
	this->removeLaterList.push_back(e);
	this->removeLaterListSize++;
}

UpdaterApplication::~UpdaterApplication()
{
	for(int i = 0; i < this->timelinesSize; i++)
	{
		delete this->timelines[i];
	}
	for(int i = 0; i < this->statesSize; i++)
	{
		delete this->states[i];
	}
	this->flush();
	trace("UpdaterApplication destruction");
}

void UpdaterApplication::createTimeline(float second, std::function<void(Entity *)> lambda, Entity *target, bool end)
{
	Timeline *tl = new Timeline(second, lambda, target, end);
	this->timelines.push_back(tl);
	this->timelinesSize++;
}

void UpdaterApplication::createTimeline(Timeline *tl)
{
	this->timelines.push_back(tl);
	this->timelinesSize++;
}

void UpdaterApplication::createTimelines(const int n, ...)
{
	va_list args;
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		this->createTimeline(va_arg(args, Timeline *));
	}
	va_end(args);
}

void UpdaterApplication::createTimeline(float second, std::function<void(Entity *)> lambda, bool end)
{
	this->createTimeline(new Timeline(second, lambda, nullptr, end));
}

void UpdaterApplication::createQueueTimelines(std::vector<Timeline *> vtl, int i, Entity *target)
{
	vtl[i]->target = target;
	vtl[i]->reset();
	this->createTimeline(vtl[i]);
	if(i != vtl.size() - 1)
	{
		vtl[i]->setEndfunc([this, i, vtl](){
				this->createQueueTimelines(vtl, i+1);
		});
	}
}

void UpdaterApplication::createQueueTimelines(std::vector<void *> vtl, int i, Entity *target)
{
	std::vector<Timeline *> *vt = new std::vector<Timeline *>();
	int size = vtl.size();
	for(int i = 0; i < size; i++)
	{
		vt->push_back((Timeline *)vtl[i]);
	}
	this->createQueueTimelines(*vt, i, target);
	delete vt;
}

void UpdaterApplication::createQueueTimelines(Entity *target, const int n, ...)
{
	std::vector<Timeline *> *tls = new std::vector<Timeline *>();
	va_list args;
	va_start(args, n);
	for(int i = 0; i < n; i++)
	{
		tls->push_back(va_arg(args, Timeline *));
	}
	va_end(args);
	this->createQueueTimelines(*tls, 0, target);
	delete tls;
}

void UpdaterApplication::createState(std::string name, std::function<void(Entity *)> lambda, Entity *target, bool act)
{
	State *s = new State(name, lambda, target, act);
	this->states.push_back(s);
	this->statesSize++;
}

void UpdaterApplication::createState(std::string name,std::function<void(Entity *)> lambda, bool act)
{
	this->createState(name, lambda, nullptr, act);
}

State *UpdaterApplication::getState(std::string name)
{
	for(int i = 0; i < this->statesSize; i++)
	{
		if(this->states[i]->name == name)
		{
			return this->states[i];
		}
	}
	return nullptr;
}

void UpdaterApplication::setState(std::string name, bool state)
{
	if(state)
	{
		this->getState(name)->able();
	}
	else
	{
		this->getState(name)->disable();
	}
}

void UpdaterApplication::reverseState(std::string name)
{
	this->getState(name)->reverse();
}

Entity *UpdaterApplication::operator[](std::string name)
{
	return this->identify(name);
}

