#include "State.hpp"

using namespace se;

std::map<std::string, State *> State::states = std::map<std::string, State *>();

State::State(std::string name, std::function<void(Entity *)> lambda, Entity *target, bool activated) 
: name(name), activated(activated), lambda(lambda), target(target)
{
	trace("State creation");
}

State::~State()
{
	if(this->getThreadRef())
	{
		this->getThreadRef()->removeByFid(this->getThreadFunctionId());
	}
	trace("State destruction");
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

void State::oneshot()
{
	std::function<void(Entity*)> initialLambda = this->lambda;
	this->lambda = [this, initialLambda](Entity *e){
		initialLambda(e);
		this->disable();
	};
}

void State::join(Thread& th)
{
	this->setThreadRef(th);
	this->setThreadFunctionId(
		th.add([this]()
		{
			this->update();
	}));
	
	State::states[this->name] = this;
}

void State::remove(std::string id)
{
	State::states.erase(id);
}

void State::flush()
{
	for(auto it = State::states.begin(); it != State::states.end(); it = State::states.begin())
	{
		trace(it->first.c_str());
		delete it->second;
		State::states.erase(it->first);
	}
}

State *State::get(std::string id)
{
	return State::states[id];
}
