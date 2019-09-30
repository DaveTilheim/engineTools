#ifndef THREAD_ABLE_HPP
#define THREAD_ABLE_HPP
#include "Thread.hpp"

namespace se
{
	class ThreadAble
	{
	private:
		unsigned long threadFunctionId = -1;
		Thread *thRef = nullptr;
	public:
		virtual void join(Thread& th) = 0;
		void setThreadFunctionId(const unsigned long id);
		unsigned long getThreadFunctionId() const;
		void setThreadRef(Thread &th);
		Thread *getThreadRef();
	};
}

#endif
