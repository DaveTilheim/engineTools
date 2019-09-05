#include "Timeline.hpp"

using namespace se;


Timeline::Timeline(float second, std::function<void(Entity *)> lambda, Entity *target, bool end)
: wait(second), lambda(lambda), target(target), end(end)
{
	beg = high_resolution_clock::now();
	current = beg;
	terminated = false;
}

Timeline::Timeline(float second, std::function<void(Entity *)> lambda, bool end)
: wait(second), lambda(lambda), target(nullptr), end(end)
{
	beg = high_resolution_clock::now();
	current = beg;
	terminated = false;
}

void Timeline::updateTime()
{
	current = high_resolution_clock::now();
}

float Timeline::getPassedTime()
{
	float ret = duration_cast<milliseconds>(current-beg).count() / 1000.0;
	return ret;
}

void Timeline::update()
{
	this->updateTime();
	if(this->end)
	{
		if(this->getPassedTime() >= this->wait)
		{
			this->lambda(this->target);
			this->terminated = true;
		}
	}
	else
	{
		if(this->getPassedTime() < this->wait)
		{
			this->lambda(this->target);
		}
		else
		{
			this->terminated = true;
			if(this->endfunc)
			{
				this->endfunc();
			}
		}
	}
}

bool Timeline::isTerminated()
{
	return this->terminated;
}

void Timeline::reset()
{
	beg = high_resolution_clock::now();
	current = beg;
	terminated = false;
}

void Timeline::setEndfunc(std::function<void()> endfunc)
{
	this->endfunc = endfunc;
	this->endCall = true;
}

Timeline::~Timeline()
{
	//std::cout << "delete timeline" << std::endl;
}
