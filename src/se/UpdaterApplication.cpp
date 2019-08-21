#include "UpdaterApplication.hpp"

using namespace se;

UpdaterApplication::UpdaterApplication(double width, double height, std::string &title, sf::Color bgColor)
:					Application(width, height, title), bgColor(bgColor), entityListSize(0)
{

}

UpdaterApplication::UpdaterApplication(std::string &title, sf::Color bgColor)
:					Application(title), bgColor(bgColor), entityListSize(0)
{

}

void UpdaterApplication::add(Entity *entity)
{
	this->entityList.push_back(entity);
	entityListSize++;
}

void UpdaterApplication::remove(Entity *entity)
{
	int i;
	for(i = 0; i < this->entityListSize; i++)
	{
		if(this->entityList[i] == entity)
		{
			break;
		}
	}
	this->entityList.erase(this->entityList.begin()+i);
	this->entityListSize--;
}

void UpdaterApplication::clear()
{
	this->entityList.clear();
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

void UpdaterApplication::update()
{
	int i;
	for(i = 0; i < this->entityListSize; i++)
	{
		this->entityList[i]->update();
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
