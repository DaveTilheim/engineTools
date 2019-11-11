#include "StringFrame.hpp"

using namespace se;


StringFrame::StringFrame(const Header& header, std::string data) : Frame(header), data(data)
{

}

StringFrame::StringFrame() : Frame()
{

}

StringFrame::StringFrame(int src, int dst, int type, std::string data) : Frame(src,dst,type), data(data)
{

}

StringFrame::StringFrame(std::string eframe)
{
	int src, dst, type;
	std::stringstream stream(eframe);
	std::string token;
	std::getline(stream, token, ':');
	src = std::atoi(token.c_str());
	std::getline(stream, token, ':');
	dst = std::atoi(token.c_str());
	std::getline(stream, token, ':');
	type = std::atoi(token.c_str());
	std::getline(stream, token, '\0');
	this->data = token;
	this->header = Header(src, dst, type);
}

StringFrame::StringFrame(const StringFrame& cp)
{
	std::cerr << "copie" << std::endl;
	this->header = cp.header;
	this->data = cp.data;
}

std::string StringFrame::getData() const
{
	return this->data;
}

std::string StringFrame::encapsulation() const
{
	return std::to_string(
		header.getSrc())+":"+
		std::to_string(header.getDst())+":"+
		std::to_string(header.getType())+":"+
		data;
}

StringFrame& StringFrame::operator=(const StringFrame& cp)
{
	std::cerr << "affectation" << std::endl;
	this->header = cp.header;
	this->data = cp.data;
	return *this;
}

size_t StringFrame::size() const
{
	std::cerr << "in size" << std::endl;
	return this->encapsulation().size();
}
