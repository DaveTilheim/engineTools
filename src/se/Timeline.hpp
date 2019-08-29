#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__
#include "Entity.hpp"
#include <ctime>
#include <chrono>

using namespace std::chrono;

namespace se
{
	class Timeline
	{
	private:
		steady_clock::time_point beg;
		steady_clock::time_point current;
		void updateTime();
		float getPassedTime();
		bool terminated;
	public:
		float wait;
		void (*callback)(Entity *);
		Entity *target;
		bool end;
		Timeline(float, void(*)(Entity *), Entity *, bool=false);
		~Timeline();
		void update();
		bool isTerminated();
	};
}


#endif
