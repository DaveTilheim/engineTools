#ifndef GLOBALINFO_HPP
#define GLOBALINFO_HPP


void setGlobalDeltaTime(const double *dt);
double getGlobalDeltaTime();

inline double getDt()
{
	return getGlobalDeltaTime();
}


#endif
