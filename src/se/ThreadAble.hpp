#ifndef THREAD_ABLE_HPP
#define THREAD_ABLE_HPP
#include "Thread.hpp"

namespace se
{
	class ThreadAble
	{
	public:
		virtual void join(Thread& th) = 0;
	};
}

#endif
