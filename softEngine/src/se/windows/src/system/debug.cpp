#include <system/debug.hpp>
#ifdef DEBUG

void sedebug::_trace(const char *file, const char *func, const int line, const char *msg)
{
	std::cerr << "\033[97m (" << file << "\033[0m::\033[97m" << func << "\033[0m::\033[97m" << line << ") : \033[91m" << msg << " \033[0m" << std::endl;
}

#endif
