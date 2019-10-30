#include "Conditional.hpp"

using namespace se;


Conditional::Conditional(std::function<bool()> cond, std::function<void(Conditional*)> updTrue, bool oneTrue) :condition(cond), updTrue(updTrue), oneTrue(oneTrue)
{
	trace("Conditional created");
}

Conditional::Conditional(std::function<bool()> cond, std::function<void(Conditional*)> updTrue, std::function<void(Conditional*)> updFalse, bool oneTrue, bool oneFalse) : condition(cond), updTrue(updTrue), updFalse(updFalse), oneTrue(oneTrue), oneFalse(oneFalse)
{
	trace("Conditional created");
}

Conditional::~Conditional()
{
	trace("Conditional destroyed");
}

void Conditional::update()
{
	if(condition())
	{
		if(oneFalse) passFalse = true;
		if(oneTrue)
		{
			if(passTrue)
			{
				updTrue(this);
				passTrue = false;
			}
		}
		else
		{
			updTrue(this);
		}
	}
	else
	{
		if(oneTrue) passTrue = true;
		if(oneFalse)
		{
			if(passFalse)
			{
				updFalse(this);
				passFalse = false;
			}
		}
		else
		{
			updFalse(this);
		}
	}
}
