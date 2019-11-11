#include <graphics/LinkedEntity.hpp>

using namespace se;

Linked::Linked(Entity& e, bool tomanage ,bool todelete) : linked(&e), tomanage(tomanage), todelete(todelete)
{
	
}

Linked::~Linked()
{
	if(todelete)
	{
		delete linked;
	}
}
