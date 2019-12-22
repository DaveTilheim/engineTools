#ifdef DEBUG
#warning debug mode
#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>
#include <string>

using namespace std;

#define trace(msg) cerr << __FILE__ << " " << __func__ << " " << __LINE__ << " " << __DATE__ << " " << msg << endl
#define tracelc(msg, l, c) cerr << "\033[" << l << ";" << c << "H" << __FILE__ << " " << __func__ << " " << __LINE__ << " " << __DATE__ << " " << msg << endl

#endif
#else
#warning release mode
#define trace(msg)
#define tracelc(msg, l, c)
#endif