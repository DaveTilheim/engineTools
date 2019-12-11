#ifndef TIMELINE_HPP
#define TIMELINE_HPP
#include "../../includes/graphics/Entity.hpp"
#include <ctime>
#include <climits>
#include <chrono>

using namespace std::chrono;

namespace se
{
	class Timeline final : public ThreadAble
	{
	private:
		static std::vector<Timeline *> timelines;
		high_resolution_clock::time_point beg;
		high_resolution_clock::time_point current;
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
		Timeline(const Timeline& cp);
		virtual ~Timeline();
		void update();
		bool isTerminated();
		void reset();
		void periodic();
		void setEndfunc(std::function<void()> endfunc);
		virtual void join(Thread &th) override;
		static void flush();
		static void del(Timeline *tm);
	};
}


#endif
