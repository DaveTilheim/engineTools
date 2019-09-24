#ifndef STATE_HPP
#define STATE_HPP
#include <string>
#include "Entity.hpp"

namespace se
{
	class State final
	{
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
	};
}

#endif
