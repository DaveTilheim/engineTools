#include "Dynamic.hpp"


Dynamic::Dynamic(bool state) : dynamicState(state)
{

}

Dynamic::Dynamic(const Dynamic& cp) : dynamicState(cp.getDynamicState())
{

}

void Dynamic::_update()
{
	if(dynamicState)
	{
		update();
	}
}

bool Dynamic::getDynamicState() const
{
	return dynamicState;
}

void Dynamic::setDynamicState(bool state)
{
	dynamicState = state;
}

Dynamic& Dynamic::operator=(const Dynamic& cp)
{
	setDynamicState(cp.getDynamicState());
	return *this;
}

string Dynamic::addrStr() const
{
	stringstream ss;
	ss << hex << (unsigned long *)this;
	return ss.str();
}

