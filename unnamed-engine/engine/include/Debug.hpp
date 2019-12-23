#ifdef DEBUG
#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>
#include <string>
#include <map>

using namespace std;

#define trace(msg) cerr << "\033[91m" << __FILE__ << " " << __func__ << " " << __LINE__ << " \033[96m" << msg << "\033[0m" << endl
#endif
#else
#define trace(msg)
#endif