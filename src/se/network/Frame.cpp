#include "Frame.hpp"

using namespace se;

Frame::Frame()
{

}

Frame::Frame(const Header& header) : header(header)
{

}

Frame::Frame(int src, int dst, int type) : header(src, dst, type)
{

}

Header Frame::getHeader() const
{
	return this->header;
}
