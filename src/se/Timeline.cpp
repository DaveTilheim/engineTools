#include "Timeline.hpp"

using namespace se;

Timeline::Timeline(float second, void(*callback)(Entity *), Entity *target, bool end)
: wait(second), callback(callback), target(target), end(end)
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
	if(this->target == nullptr)
	{
		this->terminated = true;
	}
	else
	{
		this->updateTime();
		if(this->end)
		{
			if(this->getPassedTime() >= this->wait)
			{
				this->callback(this->target);
				this->terminated = true;
			}
		}
		else
		{
			if(this->getPassedTime() < this->wait)
			{
				this->callback(this->target);
			}
			else
			{
				this->terminated = true;
			}
		}
	}
}

bool Timeline::isTerminated()
{
	return this->terminated;
}

Timeline::~Timeline()
{
	//std::cout << "delete timeline" << std::endl;
}
