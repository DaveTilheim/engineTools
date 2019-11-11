#ifndef FRAME_HPP
#define FRAME_HPP
#include <cstdlib>
#include <iostream>
#include "Header.hpp"

namespace se
{
	class Frame
	{
	protected:
		Header header;
	public:
		Frame();
		Frame(const Header&);
		Frame(int src, int dst, int type);
		Header getHeader() const;
		virtual size_t size() const = 0;
	};
}

#endif
