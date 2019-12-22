#include "Visual.hpp"


Visual::Visual(bool state) : visualState(state)
{

}

Visual::Visual(const Visual& cp) : visualState(cp.getVisualState())
{

}

void Visual::_view(sf::RenderWindow& window) const
{
	if(visualState)
	{
		view(window);
	}
}

bool Visual::getVisualState() const
{
	return visualState;
}

void Visual::setVisualState(bool state)
{
	visualState = state;
}

Visual& Visual::operator=(const Visual& cp)
{
	setVisualState(cp.getVisualState());
	return *this;
}
