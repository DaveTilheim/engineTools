#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__
#include "Entity.hpp"
#include <ctime>
#include <climits>
#include <chrono>

using namespace std::chrono;

namespace se
{
	class Timeline final
	{
	private:
		steady_clock::time_point beg;
		steady_clock::time_point current;
		void updateTime();
		float getPassedTime();
		bool terminated;
	public:
		static const unsigned long INDEFINITE = ULONG_MAX;
		float wait;
		std::function<void(Entity *)> lambda;
		std::function<void()> endfunc;
		Entity *target;
		bool end;
		bool endCall = false;
		Timeline(float, std::function<void(Entity *)> lambda, Entity *, bool=false);
		Timeline(float, std::function<void(Entity *)> lambda, bool=false);
		~Timeline();
		void update();
		bool isTerminated();
		void reset();
		void setEndfunc(std::function<void()> endfunc);
	};

	
}


#endif
