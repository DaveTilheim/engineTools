#ifndef __STATE_HPP__
#define __STATE_HPP__
#include <string>
#include "Entity.hpp"

namespace se
{
	class State
	{
	public:
		std::string name;
		bool activated;
		void (*callback)(Entity *);
		Entity *target;
		State(std::string name, void (*callback)(Entity *), Entity *target, bool activated=false);
		~State();
		void update();
		void able();
		void disable();
		void reverse();
	};
}

#endif
