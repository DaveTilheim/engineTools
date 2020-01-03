#include "Utils.hpp"


bool isImage(string s)
{
	auto c = s.find('.');
	if(c != -1)
	{
		auto sub = s.substr(c, s.size());
		if(sub == ".png" or sub == ".jpg" or sub == ".bmp" or sub == "gif")
		{
			return true;
		}
	}
	return false;
}

bool isFont(string s)
{
	auto c = s.find('.');
	if(c != -1)
	{
		auto sub = s.substr(c, s.size());
		if(sub == ".ttf" or sub == ".otf" or sub == ".eot")
		{
			return true;
		}
	}
	return false;
}
