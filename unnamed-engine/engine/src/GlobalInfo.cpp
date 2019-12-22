#include "GlobalInfo.hpp"


const double *dt = nullptr;

void setGlobalDeltaTime(const double *dlt)
{
	dt = dlt;
}

double getGlobalDeltaTime()
{
	return *dt;
}
