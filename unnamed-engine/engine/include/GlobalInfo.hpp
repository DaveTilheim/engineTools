#ifndef GLOBALINFO_HPP
#define GLOBALINFO_HPP

class Application;
class SmartApplication;

void setGlobalDeltaTime(const double *dt);
double getGlobalDeltaTime();
void setGlobalApplication(Application *root);
Application *getGlobalApplication();

inline double getDt()
{
	return getGlobalDeltaTime();
}

inline Application *getRoot()
{
	return getGlobalApplication();
}

inline SmartApplication *getSRoot()
{
	return (SmartApplication *)getGlobalApplication();
}

#endif
