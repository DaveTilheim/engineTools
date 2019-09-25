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
		static std::map<std::string, Thread *> threads;
		std::string sttcname = "";
		std::thread *thread = nullptr;
		std::vector<std::function<void()>> functions;
		unsigned nbFunctions = 0;
		bool running = false;
		bool pause = false;
		unsigned idPause = -1;
	public:
		static Thread *get(std::string sttcname);
		static void del(std::string sttcname);
		static void flush();
		Thread(std::string sttcname);
		~Thread();
		void start(const unsigned long *appTick=nullptr);
		void stop();
		void join();
		void wait();
		void play();
		void add(std::function<void()> function);
		void remove(int i);
	};
}

#endif
