#include "SystemEntity.hpp"


SystemEntity::SystemEntity(const SystemEntity& cp) : DynamicVisual(cp)
{
	trace("SystemEntity creation");
}

SystemEntity::~SystemEntity()
{
	trace("SystemEntity destruction");
}

SystemEntity& SystemEntity::operator=(const SystemEntity& cp)
{
	DynamicVisual::operator=(cp);
	return *this;
}
