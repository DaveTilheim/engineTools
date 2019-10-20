#ifndef HEADER_HPP
#define HEADER_HPP
#include <iostream>

namespace se
{
	class Header
	{
	private:
		unsigned src = -1;
		unsigned dst = -1;
		unsigned type = -1;
	public:
		Header();
		Header(int src, int dst, int type);
		Header(const Header&);
		unsigned getSrc() const;
		unsigned getDst() const;
		unsigned getType() const;
		Header& operator=(const Header&);
	};
}

#endif
