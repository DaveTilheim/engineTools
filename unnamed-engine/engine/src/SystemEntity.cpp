#include "SystemEntity.hpp"


SystemEntity::SystemEntity()
{

}

SystemEntity::SystemEntity(const SystemEntity& cp) : DynamicVisual(cp)
{

}

SystemEntity::~SystemEntity()
{

}

SystemEntity& SystemEntity::operator=(const SystemEntity& cp)
{
	DynamicVisual::operator=(cp);
	return *this;
}
