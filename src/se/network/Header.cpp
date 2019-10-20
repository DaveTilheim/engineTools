#include "Header.hpp"

using namespace se;


Header::Header()
{

}

Header::Header(int src, int dst, int type) : src(src), dst(dst), type(type)
{

}

Header::Header(const Header& cp)
{
	this->src = cp.src;
	this->dst = cp.dst;
	this->type = cp.type;
}

unsigned Header::getSrc() const
{
	return this->src;
}

unsigned Header::getDst() const
{
	return this->dst;
}

unsigned Header::getType() const
{
	return this->type;
}

Header& Header::operator=(const Header& cp)
{
	this->src = cp.src;
	this->dst = cp.dst;
	this->type = cp.type;
	return *this;
}

