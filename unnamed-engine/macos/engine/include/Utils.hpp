#ifndef UTILS_HPP
#define UTILS_HPP
#include <cmath>
#include <string>

using namespace std;

#define PI 3.14159265359

typedef float Degre;
typedef float Radian;

inline Radian rad(Degre angle)
{
	return angle * PI / 180.0;
}

inline Degre deg(Radian angle)
{
	return angle * 180.0 / PI;
}

bool isImage(string s);
bool isFont(string s);

#endif
