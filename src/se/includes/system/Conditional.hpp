#ifndef CONDITIONNAL_HPP
#define CONDITIONNAL_HPP
#include <functional>
#include "debug.hpp"

namespace se
{
	class Conditional final
	{
	private:
		std::function<bool()> condition;
		std::function<void(Conditional*)> updTrue;
		std::function<void(Conditional*)> updFalse = [](Conditional*){};
		bool oneTrue = false;
		bool oneFalse = false;
		bool passTrue = true;
		bool passFalse = true;
	public:
		Conditional(std::function<bool()> cond, std::function<void(Conditional*)> upd, bool oneTrue=false);
		Conditional(std::function<bool()> cond, std::function<void(Conditional*)> updTrue, std::function<void(Conditional*)> updFalse, bool oneTrue=false, bool oneFalse=false);
		~Conditional();
		void update();
	};
}

#endif
