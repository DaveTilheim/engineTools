#ifndef THREAD_HPP
#define THREAD_HPP
#include <thread>
#include <functional>
#include <map>
#include <vector>
#include "Utilities.hpp"
#include "debug.hpp"

namespace se
{
	class Thread
	{
	private:
		struct Functional
		{
			std::function<void()> f;
			unsigned long id = -1;
		};
		unsigned long currentId = -1;
		static std::map<std::string, Thread *> threads;
		std::string sttcname = "";
		std::thread *thread = nullptr;
		std::vector<Functional> functions;
		unsigned nbFunctions = 0;
		bool running = false;
		bool pause = false;
		unsigned idPause = -1;
	public:
		static Thread *get(std::string sttcname);
		static void del(std::string sttcname);
		static void flush();
		Thread(std::string sttcname);
		virtual ~Thread();
		void start(const unsigned long *appTick=nullptr, bool alone=false);
		void stop();
		void join();
		void wait();
		void play();
		unsigned long add(std::function<void()> function);
		void remove(int i);
		void removeByFid(unsigned long id);
	};
}

#endif
