#include "RenderLayout.hpp"

using namespace se;

std::vector<RenderLayout *> RenderLayout::layouts = std::vector<RenderLayout *>();
unsigned RenderLayout::layoutsSize = 0;
RenderLayout *RenderLayout::defaultLayout = new RenderLayout("default", 0);

RenderLayout::RenderLayout(std::string name, unsigned order)
 : name(name), order(order)
{
	if(order < 0)
	{
		this->order = RenderLayout::layoutsSize;
	}
	RenderLayout::layouts.push_back(this);
	RenderLayout::layoutsSize++;
	std::sort(RenderLayout::layouts.begin(), RenderLayout::layouts.end(), RenderLayout::compare);
	trace("create Layout");
}

RenderLayout::~RenderLayout()
{
	trace("Layout destroyed");
}

bool RenderLayout::compare(RenderLayout *l1, RenderLayout *l2)
{
	return l1->order < l2->order;
}

void RenderLayout::addEntity(Entity *e)
{
	this->entityList.push_back(e);
	this->entityListSize++;
}

void RenderLayout::addInLayout(std::string name, Entity *e)
{
	for(auto it : RenderLayout::layouts)
	{
		if(it->name == name)
		{
			it->addEntity(e);
		}
	}
}

unsigned RenderLayout::getNbEntity()
{
	return this->entityListSize;
}

Entity *RenderLayout::getEntity(unsigned i)
{
	return this->entityList[i];
}

void RenderLayout::flush()
{
	for(auto it : RenderLayout::layouts)
	{
		delete it;
	}
}

unsigned RenderLayout::getSize()
{
	return RenderLayout::layoutsSize;
}

RenderLayout *RenderLayout::getLayout(unsigned i)
{
	return RenderLayout::layouts[i];
}

RenderLayout *RenderLayout::getLayout(std::string name)
{
	for(auto it : RenderLayout::layouts)
	{
		if(it->name == name)
		{
			return it;
		}
	}
	return nullptr;
}

void RenderLayout::removeEntity(Entity *e)
{
	for(int i = 0; i < RenderLayout::layoutsSize; i++)
	{
		for(int j = 0; j < RenderLayout::layouts[i]->entityListSize; j++)
		{
			if(RenderLayout::layouts[i]->entityList[j] == e)
			{
				RenderLayout::layouts[i]->entityList.erase(RenderLayout::layouts[i]->entityList.begin() + j);
				RenderLayout::layouts[i]->entityListSize--;
				return;
			}
		}
	}
}

void RenderLayout::swapLayout(std::string l1, std::string l2)
{
	RenderLayout *rl1 = RenderLayout::getLayout(l1);
	RenderLayout *rl2 = RenderLayout::getLayout(l2);
	unsigned order = rl1->order;
	rl1->order = rl2->order;
	rl2->order = order;
	std::sort(RenderLayout::layouts.begin(), RenderLayout::layouts.end(), RenderLayout::compare);
}

void RenderLayout::changeLayout(std::string l, Entity *e)
{
	RenderLayout::removeEntity(e);
	RenderLayout::addInLayout(l, e);
}
