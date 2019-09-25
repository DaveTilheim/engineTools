#include "Thread.hpp"

using namespace se;

std::map<std::string, Thread *> Thread::threads = std::map<std::string, Thread *>();

Thread::Thread(std::string sttcname)
{
	Thread::threads[sttcname] = this;
	this->sttcname = sttcname;
	trace("Thread creation");
}

Thread::~Thread()
{
	if(this->thread)
	{
		delete this->thread;
		this->thread = nullptr;
	}
	this->running = false;
	this->pause = true;
	this->idPause = -1;
	this->nbFunctions = 0;
	this->functions.clear();
	if(Thread::threads.find(this->sttcname) != Thread::threads.end())
		Thread::threads.erase(this->sttcname);
	trace("Thread destruction");
}

void Thread::start(const unsigned long *appTick)
{
	if(this->thread)
	{
		delete this->thread;
		this->running = false;
		this->pause = true;
		this->idPause = -1;
	}
	std::function<void()> func;
	if(appTick)
	{
		func = [this, appTick](){
			unsigned long tick = *appTick;
			while(util::appOpen && this->running)
			{
				tick = *appTick;
				for(int i = 0; i < this->nbFunctions; i++)
				{
					this->functions[i]();
				}
				while(tick == *appTick && util::appOpen && this->running);
			}
		};
	}
	else
	{
		func = [this](){
			while(util::appOpen && this->running)
			{
				for(int i = 0; i < this->nbFunctions; i++)
				{
					this->functions[i]();
				}
			}
		};
	}
	this->thread = new std::thread(func);
	this->running = true;
	trace("Thread is started");
}

void Thread::stop()
{
	this->running = false;
}

void Thread::join()
{
	this->stop();
	if(this->thread)
	{
		this->thread->join();
	}
	delete this->thread;
	this->thread = nullptr;
}

void Thread::wait()
{
	if(this->pause == false)
	{
		this->idPause = this->nbFunctions;
		this->add([this](){
			while(this->pause);
		});
		this->pause = true;
	}
}

void Thread::play()
{
	this->pause = false;
	this->remove(this->idPause);
	this->idPause = -1;
}

void Thread::add(std::function<void()> function)
{
	this->functions.push_back(function);
	this->nbFunctions++;
}

void Thread::remove(int i)
{
	if(i >= 0)
	{
		this->functions.erase(this->functions.begin() + i);
		this->nbFunctions--;
	}
}

Thread *Thread::get(std::string sttcname)
{
	return Thread::threads.find(sttcname) != Thread::threads.end() ? Thread::threads[sttcname] : nullptr;
}

void Thread::flush()
{
	for(auto it = Thread::threads.begin(); it != Thread::threads.end(); it = Thread::threads.begin())
	{
		trace(it->first.c_str());
		if(it->second->pause)
		{
			it->second->play();
		}
		it->second->join();
		delete it->second;
		Thread::threads.erase(it->first);
	}
}

void Thread::del(std::string sttcname)
{
	if(Thread::threads[sttcname]->pause)
	{
		Thread::threads[sttcname]->play();
	}
	Thread::threads[sttcname]->join();
	delete Thread::threads[sttcname];
	Thread::threads.erase(sttcname);
}


