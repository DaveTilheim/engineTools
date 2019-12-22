#include "GlobalInfo.hpp"


const double *dt = nullptr;
Application *root = nullptr;

void setGlobalDeltaTime(const double *dlt)
{
	dt = dlt;
}

double getGlobalDeltaTime()
{
	return *dt;
}

void setGlobalApplication(Application *roota)
{
	root = roota;
}

Application *getGlobalApplication()
{
	return root;
}
