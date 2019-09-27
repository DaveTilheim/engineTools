#include "ThreadAble.hpp"

using namespace se;

void ThreadAble::setThreadFunctionId(const unsigned long id)
{
	this->threadFunctionId = id;
}

unsigned long ThreadAble::getThreadFunctionId() const
{
	return this->threadFunctionId;
}
