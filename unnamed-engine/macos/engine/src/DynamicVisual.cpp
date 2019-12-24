#include "DynamicVisual.hpp"


DynamicVisual::DynamicVisual(bool dynamicState, bool visualState) : Dynamic(dynamicState), Visual(visualState)
{

}

DynamicVisual::DynamicVisual(const DynamicVisual& cp) : Dynamic(cp), Visual(cp)
{

}

unsigned char DynamicVisual::getState() const
{
	return getDynamicState() | (getVisualState() << 1);
}

void DynamicVisual::setState(bool dynamicState, bool visualState)
{
	setDynamicState(dynamicState);
	setVisualState(visualState);
}

void DynamicVisual::pause()
{
	setState(false, false);
}

void DynamicVisual::play()
{
	setState(true, true);
}

DynamicVisual& DynamicVisual::operator=(const DynamicVisual& cp)
{
	Dynamic::operator=(cp);
	Visual::operator=(cp);
	return *this;
}

ostream& operator<<(ostream& out, const DynamicVisual& obj)
{
	return out << "Dynamic: " << obj.getDynamicState() << "\t" << "Visual: " << obj.getVisualState() << " ";
}
