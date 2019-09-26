#ifndef STATE_HPP
#define STATE_HPP
#include <string>
#include "Entity.hpp"

namespace se
{
	class State final
	{
	private:
		static std::map<std::string, State *> states;
	public:
		std::string name;
		bool activated;
		std::function<void(Entity *)> lambda;
		Entity *target;
		State(std::string name, std::function<void(Entity *)> lambda, Entity *target, bool activated=false);
		~State();
		void update();
		void able();
		void disable();
		void reverse();
		void join(Thread& th);
		static void remove(std::string id);
		static void flush();
		static State *get(std::string id);
	};
}

#endif
