#include "State.hpp"

using namespace se;

State::State(std::string name, std::function<void(Entity *)> lambda, Entity *target, bool activated) 
: name(name), lambda(lambda), target(target), activated(activated)
{

}

State::~State()
{
	std::cout << "state deleted" << std::endl;
}

void State::update()
{
	if(this->activated)
	{
		this->lambda(this->target);
	}
}

void State::able()
{
	this->activated = true;
}

void State::disable()
{
	this->activated = false;
}

void State::reverse()
{
	this->activated = not this->activated;
}
