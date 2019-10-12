#ifdef DEBUG
#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>

#define trace(msg) sedebug::_trace(__FILE__, __func__, __LINE__, msg)

namespace sedebug
{
	void _trace(const char *file, const char *func, const int line, const char *msg);
}

#endif
#else
#define trace(msg)
#endif
