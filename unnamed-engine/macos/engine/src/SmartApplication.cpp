#include "SmartApplication.hpp"


SmartTrait operator|(SmartTrait s1, SmartTrait s2)
{
	return (SmartTrait)((int)s1 | (int)s2);
}

SmartApplication::SmartApplication(string title) : Application(title), app(*this)
{
	filter.setSize(static_cast<sf::Vector2f>(window.getSize()));
	w_view = sf::View(getCenter(), static_cast<sf::Vector2f>(getWindow().getSize()));
	trace("SmartApplication creation");
}

SmartApplication::SmartApplication(int width, int height, string title) : Application(width, height, title), app(*this)
{
	filter.setSize(static_cast<sf::Vector2f>(window.getSize()));
	w_view = sf::View(getCenter(), static_cast<sf::Vector2f>(getWindow().getSize()));
	trace("SmartApplication creation");
}

sf::Texture SmartApplication::capture() const
{
	sf::RenderTexture rt;
	rt.create(window.getSize().x, window.getSize().y);
	rt.clear(getBackgroundColor());
	for(auto so : entities)
	{
		rt.draw(*dynamic_cast<sf::Drawable *>(so.object));
	}
	rt.display();
	return rt.getTexture();
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

void SmartApplication::updateTimers()
{
	for(auto so : timers)
	{
		if(dynamic_cast<Timer *>(so.object)->isFinished())
		{
			removeLater(so.object);
		}
		else
		{
			so.object->_update();
		}
	}
}

void SmartApplication::textEnteredEventHandler(const sf::Event& event)
{
	for(auto so : entities)
	{
		if(dynamic_cast<InputEntity *>(so.object))
		{
			InputEntity *i = dynamic_cast<InputEntity *>(so.object);
			if(i->isFocused())
			{
				i->input(event.text);
			}
		}
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
	updateTimers();
	updateRemoving();
}

void SmartApplication::view(sf::RenderWindow& window)
{
	if(not dynamicViewMode)
	{
		fill();
		if(viewMode)
		{
			window.setView(w_view);
		}
		drawEntities(window);
	}
	else
	{
		dynamicView.capture = capture();
		dynamicView.reference = dynamicView.capture.copyToImage();
		dynamicView.image = dynamicView.reference;
		dynamicView.traitement(dynamicView);
		dynamicView.capture.update(dynamicView.image);
		dynamicView.sprite.setTexture(dynamicView.capture);
		if(viewMode)
		{
			window.setView(w_view);
		}
		window.draw(dynamicView.sprite);
	}
	if(viewMode)
	{
		window.setView(window.getDefaultView());
	}
	if(filterMode)
	{
		window.draw(filter);
	}
	refresh();
}

void SmartApplication::setDynamicViewMode(bool mode)
{
	dynamicViewMode = mode;
}

void SmartApplication::setDynamicTraitement(function<void(DynamicView&)> traitement)
{
	dynamicView.traitement = traitement;
}

void SmartApplication::setViewMode(bool mode)
{
	viewMode = mode;
}

sf::View& SmartApplication::getView()
{
	return w_view;
}

void SmartApplication::setFilterMode(bool fm)
{
	filterMode = fm;
}

void SmartApplication::setFilter(const sf::Color& color)
{
	filter.setFillColor(color);
}

void SmartApplication::setFilter(const sf::Texture* txtr)
{
	filter.setTexture(txtr);
}

sf::RectangleShape SmartApplication::getFilter() const
{
	return filter;
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
	else if(dynamic_cast<Timer *>(&obj))
	{
		addTimer(dynamic_cast<Timer *>(&obj), traits);
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
	else if(dynamic_cast<Timer *>(obj))
	{
		addTimer(dynamic_cast<Timer *>(obj), traits);
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

void SmartApplication::addTimer(Timer& timer, SmartTrait traits)
{
	SmartObject sobj(&timer, traits);
	timers.push_back(sobj);
}

void SmartApplication::addTimer(Timer* timer, SmartTrait traits)
{
	SmartObject sobj(timer, traits);
	timers.push_back(sobj);
}

void SmartApplication::addTexture(string filename)
{
	if(textures.find(filename) == textures.end())
	{
		textures[filename] = new sf::Texture();
	}
	if(not textures[filename]->loadFromFile(filename))
	{
		delete textures[filename];
		textures.erase(filename);
	}
	else
	{
		trace("Texture " + filename + " created");
	}
}

void SmartApplication::addTexture(const Image& img)
{
	if(textures.find(img.getName()) == textures.end())
	{
		textures[img.getName()] = new sf::Texture();
	}
	textures[img.getName()]->loadFromImage(img);
	trace("Texture " + img.getName() + " created");
}

void SmartApplication::addFont(string fontfile)
{
	if(fonts.find(fontfile) == fonts.end())
	{
		fonts[fontfile] = new sf::Font();
	}
	if(not fonts[fontfile]->loadFromFile(fontfile))
	{
		delete fonts[fontfile];
		fonts.erase(fontfile);
	}
	else
	{
		trace("Font " + fontfile + " created");
	}
}

void SmartApplication::removeTexture(string textureName)
{
	if(textures.find(textureName) != textures.end())
	{
		delete textures[textureName];
		textures.erase(textureName);
		trace("Texture " + textureName + " removed");
	}
}

void SmartApplication::removeTexture(sf::Texture *texture)
{
	for(auto t : textures)
	{
		if(t.second == texture)
		{
			delete t.second;
			textures.erase(t.first);
			trace("Texture " + t.first + " removed");
			break;
		}
	}
}

void SmartApplication::removeTexture(SystemEntity* entity)
{
	if(dynamic_cast<sf::Shape *>(entity))
	{
		if(dynamic_cast<sf::Shape *>(entity)->getTexture())
		{
			removeTexture((sf::Texture *)dynamic_cast<sf::Shape *>(entity)->getTexture());
		}
	}
	else if(dynamic_cast<sf::Sprite *>(entity))
	{
		if(dynamic_cast<sf::Sprite *>(entity)->getTexture())
		{
			removeTexture((sf::Texture *)dynamic_cast<sf::Sprite *>(entity)->getTexture());
		}
	}
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
	else if(dynamic_cast<Timer *>(obj))
	{
		removeTimer(dynamic_cast<Timer *>(obj));
	}
}

void SmartApplication::removeEntity(SystemEntity* entity)
{
	int i = 0;
	for(auto so : entities)
	{
		if(so.object == entity)
		{
			removeTexture(entity);
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

void SmartApplication::removeTimer(Timer *timer)
{
	int i = 0;
	for(auto so : timers)
	{
		if(so.object == timer)
		{
			if(so.deletable())
			{
				delete dynamic_cast<Timer *>(so.object);
			}
			timers.erase(timers.begin() + i);
			break;
		}
		i++;
	}
}

void SmartApplication::removeFont(string fid)
{
	for(auto f : fonts)
	{
		if(f.first == fid)
		{
			delete f.second;
			fonts.erase(fid);
		}
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

sf::Texture* SmartApplication::getTexture(string textureName)
{
	if(textures.find(textureName) != textures.end())
	{
		return textures[textureName];
	}
	return nullptr;
}

sf::Font* SmartApplication::getFont(string fontId)
{
	if(fonts.find(fontId) != fonts.end())
	{
		return fonts[fontId];
	}
	return nullptr;
}

sf::Texture* SmartApplication::duplicateTexture(string textureName, string otherName)
{
	if(textures.find(textureName) != textures.end())
	{
		if(textures.find(otherName) == textures.end())
		{
			textures[otherName] = new sf::Texture(*textures[textureName]);
			return textures[otherName];
		}
	}
	return nullptr;
}

sf::Texture* SmartApplication::duplicateTexture(string textureName, SystemEntity* entity)
{
	sf::Texture *ret = duplicateTexture(textureName, textureName + "-" + entity->addrStr());
	if(dynamic_cast<sf::Shape *>(entity))
	{
		dynamic_cast<sf::Shape *>(entity)->setTexture(ret);
	}
	else if(dynamic_cast<sf::Sprite *>(entity))
	{
		dynamic_cast<sf::Sprite *>(entity)->setTexture(*ret);
	}
	return ret;
}

sf::Texture* SmartApplication::duplicateTexture(string textureName, SystemEntity& entity)
{
	return duplicateTexture(textureName, &entity);
}

int SmartApplication::countEntities() const
{
	return entities.size();
}

int SmartApplication::countSubApplications() const
{
	return subApplications.size();
}

int SmartApplication::countTimers() const
{
	return timers.size();
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

SmartApplication& SmartApplication::operator<<(string obj)
{
	if(isImage(obj))
		addTexture(obj);
	else if(isFont(obj))
		addFont(obj);
	return *this;
}

SmartApplication& SmartApplication::operator<<(const Image& image)
{
	addTexture(image);
	return *this;
}

SmartApplication& SmartApplication::operator<<(SmartObject so)
{
	add(so.object, so.traits);
	return *this;
}

sf::Texture *SmartApplication::operator[](string textureName)
{
	return getTexture(textureName);
}

sf::Font *SmartApplication::operator()(string font)
{
	return getFont(font);
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
	entities.clear();
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
	subApplications.clear();
}

void SmartApplication::flushTextures()
{
	for(auto t : textures)
	{
		delete t.second;
		trace("Texture " + t.first + " removed");
	}
	textures.clear();
}

void SmartApplication::flushTimers()
{
	for(auto so : timers)
	{
		if(so.deletable())
		{
			delete dynamic_cast<Timer *>(so.object);
		}
	}
	timers.clear();
}

void SmartApplication::flushFonts()
{
	for(auto f : fonts)
	{
		delete f.second;
		trace("Font " + f.first + " removed");
	}
	fonts.clear();
}

void SmartApplication::flush()
{
	flushEntities();
	flushSubApplications();
	flushTextures();
	flushTimers();
	flushFonts();
}

SmartApplication::~SmartApplication()
{
	flush();
	trace("SmartApplication destruction");
	cout << "SystemEntities: " << SystemEntity::getSystemEntityCounter() << endl;
	cout << "Timers: " << Timer::getTimerCounter() << endl;
	cout << "Applications: " << Application::getApplicationCounter() << " (includes the current Application)" << endl;
}
