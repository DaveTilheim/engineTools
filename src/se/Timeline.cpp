#include "Timeline.hpp"

using namespace se;


Timeline::Timeline(float second, std::function<void(Entity *)> lambda, Entity *target, bool end)
: wait(second), lambda(lambda), target(target), end(end)
{
	beg = high_resolution_clock::now();
	current = beg;
	terminated = false;
	trace("Timeline creation");
}

Timeline::Timeline(float second, std::function<void(Entity *)> lambda, bool end)
: wait(second), lambda(lambda), target(nullptr), end(end)
{
	beg = high_resolution_clock::now();
	current = beg;
	terminated = false;
	trace("Timeline creation");
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
	trace("Timeline destruction");
}

std::vector<Timeline *> Timeline::timelines = std::vector<Timeline *>();

void Timeline::join(Thread &th)
{
	this->setThreadFunctionId(
		th.add([this, &th]() {
			if(not this->terminated)
			{
				this->update();
			}
			else
			{
				Timeline::del(this);
				th.removeByFid(this->getThreadFunctionId());
			}
	}));
	Timeline::timelines.push_back(this);
}

void Timeline::flush()
{
	unsigned size = Timeline::timelines.size();
	while(size != 0)
	{
		delete Timeline::timelines[0];
		Timeline::timelines.erase(Timeline::timelines.begin());
		size--;
	}
}

void Timeline::del(Timeline *tm)
{
	unsigned size = Timeline::timelines.size();
	for(int i = 0; i < size; i++)
	{
		if(Timeline::timelines[i] == tm)
		{
			delete tm;
			Timeline::timelines.erase(Timeline::timelines.begin()+i);
			break;
		}
	}
}

