#include "UpdaterApplication.hpp"

using namespace se;

UpdaterApplication::UpdaterApplication(double width, double height, std::string title, sf::Color bgColor)
:					Application(width, height, title)
					, entityListSize(0), bgColor(bgColor), timelinesSize(0), statesSize(0),
					removeLaterListSize(0),app(*this),mp(0,0)
{
	trace("UpdaterApplication creation");
}

UpdaterApplication::UpdaterApplication(std::string title, sf::Color bgColor)
:					Application(title)
					,entityListSize(0), bgColor(bgColor), timelinesSize(0), statesSize(0),
					removeLaterListSize(0), app(*this),mp(0,0)
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

void UpdaterApplication::add(Entity *entity, std::string layout)
{
	this->add(entity);
	this->layout(layout, entity);
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

void UpdaterApplication::add(KeyCatcher *kc)
{
	this->addKeyCatcher(kc);
}

void UpdaterApplication::add(KeyCatcher *kc, std::string layout)
{
	this->addKeyCatcher(kc, layout);
}

void UpdaterApplication::addKeyCatcher(KeyCatcher *kc)
{
	this->keyCatchers.push_back(kc);
	this->keyCatcherListSize++;
	this->add(dynamic_cast<Entity *>(kc));
}

void UpdaterApplication::addKeyCatcher(KeyCatcher *kc, std::string layout)
{
	this->keyCatchers.push_back(kc);
	this->keyCatcherListSize++;
	this->add(dynamic_cast<Entity *>(kc), layout);
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

void UpdaterApplication::removeKeyCatcher(KeyCatcher *kc)
{
	for(int i = 0; i < this->keyCatcherListSize; i++)
	{
		if(kc == this->keyCatchers[i])
		{
			this->keyCatchers.erase(this->keyCatchers.begin() + i);
			this->keyCatcherListSize--;
			break;
		}
	}
}

void UpdaterApplication::removeEntityInShader(const Entity& e)
{
	for(int i = 0; i < this->shaderListSize; i++)
	{
		if(this->shaderList[i]->getLuxEntity() == &e)
		{
			removeShader(this->shaderList[i]->getName());
		}
		else
		{
			this->shaderList[i]->removeEntity(e);
		}
	}
}

void UpdaterApplication::remove(Entity *entity, bool del)
{
	int i;
	this->removeEntityInShader(*entity);
	this->removeTimeline(entity);
	this->removeState(entity);
	this->removeKeyCatcher(dynamic_cast<KeyCatcher *>(entity));
	RenderLayout::removeEntity(entity);
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
	this->conditionalMap.clear();
	this->shaderList.clear();
	this->keyCatchers.clear();
	this->entityNamedList.clear();
	this->entityListMap.clear();
	this->fontMap.clear();
}

void UpdaterApplication::flush()
{
	for(int i = 0; i < this->timelinesSize; i++)
	{
		delete this->timelines[i];
	}
	for(int i = 0; i < this->statesSize; i++)
	{
		delete this->states[i];
	}
	State::flush();
	Timeline::flush();
	RenderLayout::flush();
	Shader::flush();
	for(int i = 0; i < this->shaderListSize; i++)
	{
		delete this->shaderList[i];
	}
	for(int i = 0; i < this->entityListSize; i++)
	{
		delete this->entityList[i];
	}
	for(auto it = this->fontMap.begin() ; it!=this->fontMap.end() ; it++)
	{
		delete it->second;
	}
	for(auto it = this->conditionalMap.begin() ; it!=this->conditionalMap.end() ; it++)
	{
		delete it->second;
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

void UpdaterApplication::updateConditionals()
{
	for(auto it = this->conditionalMap.begin(); it != this->conditionalMap.end(); it++)
	{
		it->second->update();
	}
}

void UpdaterApplication::updateStates()
{
	for(int i = 0; i < this->statesSize; i++)
	{
		if(this->states[i]->target)
		{
			if(this->states[i]->target->getUpdateState())
			{
				this->states[i]->update();
			}
		}
	}
}

void UpdaterApplication::updateShaders()
{
	for(int i = 0; i < this->shaderListSize; i++)
	{
		this->shaderList[i]->update();
	}
}

void UpdaterApplication::updateTimelines()
{
	for(int i = 0; i < this->timelinesSize; i++)
	{
		this->timelines[i]->update();
		if(this->timelines[i]->isTerminated())
		{
			this->removeTimeline(this->timelines[i]);
			i--;
		}
	}
}

void UpdaterApplication::updateEntities()
{
	for(int i = 0; i < this->entityListSize; i++)
	{
		this->entityList[i]->updateIfActivate();
	}
}

void UpdaterApplication::updateRemoveLaterConditionals()
{
	int i;
	for(i = 0; i < this->removeLaterConditionalListSize; i++)
	{
		this->removeConditional(this->removeLaterConditionalList[i]);
	}
	if(i)
	{
		this->removeLaterConditionalList.clear();
		this->removeLaterConditionalListSize = 0;
	}
}

void UpdaterApplication::updateRemoveLater()
{
	int i;
	for(i = 0; i < this->removeLaterListSize; i++)
	{
		this->remove(this->removeLaterList[i]);
	}
	if(i)
	{
		this->removeLaterList.clear();
		this->removeLaterListSize = 0;
	}
}


void UpdaterApplication::update()
{
	this->updateConditionals();
	this->updateStates();
	this->updateShaders();
	this->updateTimelines();
	this->updateEntities();
	this->updateRemoveLaterConditionals();
	this->updateRemoveLater();
	this->mp = util::getMousePosition();
}

void UpdaterApplication::render()
{
	this->fill(this->bgColor);
	for(int i = 0; i < RenderLayout::getSize(); i++)
	{
		RenderLayout *tmp = RenderLayout::getLayout(i);
		for(int j = 0; j < tmp->getNbEntity(); j++)
		{
			tmp->getEntity(j)->renderIfActivate();
		}
	}
	this->display();
}

void UpdaterApplication::textEnteredEventHandler(const sf::Event& event)
{
	for(int i = 0; i < this->keyCatcherListSize; i++)
	{
		this->keyCatchers[i]->keyCatch(event.text.unicode);
	}
}

void UpdaterApplication::removeLater(Entity *e)
{
	this->removeLaterList.push_back(e);
	this->removeLaterListSize++;
}

UpdaterApplication::~UpdaterApplication()
{
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


State *UpdaterApplication::getState(std::string name, Entity *target)
{
	for(int i = 0; i < this->statesSize; i++)
	{
		if(this->states[i]->name == name && this->states[i]->target == target)
		{
			return this->states[i];
		}
	}
	return nullptr;
}

void UpdaterApplication::setState(std::string name, bool state, Entity *target)
{
	if(state)
	{
		this->getState(name, target)->able();
	}
	else
	{
		this->getState(name, target)->disable();
	}
}

void UpdaterApplication::reverseState(std::string name, Entity *target)
{
	this->getState(name, target)->reverse();
}

sf::Font *UpdaterApplication::addFont(std::string fontid, std::string fontname)
{
	sf::Font *font = new sf::Font();
	if(font->loadFromFile(fontname))
	{
		this->fontMap[fontid] = font;
		trace("font loaded");
	}
	else
	{
		delete font;
		font = nullptr;
	}

	return font;
}

sf::Font *UpdaterApplication::getFont(std::string fontid)
{
	return this->fontMap.find(fontid) != this->fontMap.end() ? this->fontMap[fontid] : nullptr;
}

void UpdaterApplication::layout(std::string name, Entity *e)
{
	RenderLayout::removeEntity(e);
	RenderLayout::addInLayout(name, e);
}

Entity *UpdaterApplication::operator[](std::string name)
{
	return this->identify(name);
}

UpdaterApplication& UpdaterApplication::operator<<(Entity *e)
{
	this->add(e);
	return *this;
}

UpdaterApplication& UpdaterApplication::operator<<(KeyCatcher *e)
{
	this->add(e);
	return *this;
}

void UpdaterApplication::operator<<(std::string layout)
{
	this->layout(layout, this->entityList[this->entityListSize-1]);
}

void UpdaterApplication::copyTimelines(Entity& target, const Entity& src)
{
	UpdaterApplication& root = *target.getRoot<UpdaterApplication>();
	for(auto tm : root.timelines)
	{
		if(tm->target == &src)
		{
			Timeline *t = new Timeline(*tm);
			t->target = &target;
			root.createTimeline(t);
		}
	}
}

void UpdaterApplication::createState(State *state)
{
	this->states.push_back(state);
	this->statesSize++;
}

void UpdaterApplication::copyStates(Entity& target, const Entity& src)
{
	UpdaterApplication& root = *target.getRoot<UpdaterApplication>();
	for(auto s : root.states)
	{
		if(s->target == &src)
		{
			State *state = new State(*s);
			state->target = &target;
			root.createState(state);
		}
	}
}

void UpdaterApplication::addShader(Shader& shader)
{
	this->shaderList.push_back(&shader);
	this->shaderListSize++;
}

Shader *UpdaterApplication::getShader(std::string name)
{
	for(int i = 0; i < this->shaderListSize; i++)
	{
		if(this->shaderList[i]->getName() == name)
		{
			return this->shaderList[i];
		}
	}
	return nullptr;
}

void UpdaterApplication::removeShader(std::string name)
{
	for(int i = 0; i < this->shaderListSize; i++)
	{
		if(this->shaderList[i]->getName() == name)
		{
			delete this->shaderList[i];
			this->shaderList.erase(this->shaderList.begin() + i);
			this->shaderListSize--;
			return;
		}
	}
}

void UpdaterApplication::addConditional(std::string id, Conditional *c)
{
	this->conditionalMap[id] = c;
}

void UpdaterApplication::removeConditional(std::string id)
{
	if(this->conditionalMap.find(id) != this->conditionalMap.end())
	{
		delete this->conditionalMap[id];
		this->conditionalMap.erase(id);
	}
}

void UpdaterApplication::removeLaterConditional(std::string id)
{
	if(this->conditionalMap.find(id) != this->conditionalMap.end())
	{
		this->removeLaterConditionalList.push_back(id);
		this->removeLaterConditionalListSize++;
	}
}

void UpdaterApplication::moveAll(int vx, int vy, std::string listName)
{
	std::vector<Entity *> *list = nullptr;
	if(listName.size())
	{
		if(entityNamedList.find(listName) != entityNamedList.end())
		{
			list = identifyList(listName);
		}
		else
		{
			return;
		}
	}
	else
	{
		list = &entityList;
	}
	for(auto e : *list)
	{
		e->move(vx, vy);
	}
}
