#include "SystemEntity.hpp"


int SystemEntity::systemEntityCounter = 0;


SystemEntity::SystemEntity() : DynamicVisual()
{
	trace("SystemEntity creation");
	SystemEntity::systemEntityCounter++;
}

SystemEntity::SystemEntity(const SystemEntity& cp) : DynamicVisual(cp)
{
	trace("SystemEntity creation");
	SystemEntity::systemEntityCounter++;
}

SystemEntity::~SystemEntity()
{
	trace("SystemEntity destruction");
	SystemEntity::systemEntityCounter--;
}

SystemEntity& SystemEntity::operator=(const SystemEntity& cp)
{
	DynamicVisual::operator=(cp);
	return *this;
}

int SystemEntity::getSystemEntityCounter()
{
	return systemEntityCounter;
}
