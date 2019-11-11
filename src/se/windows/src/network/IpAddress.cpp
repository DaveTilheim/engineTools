#include "IpAddress.hpp"

using namespace se;

IpAddress::IpAddress(std::string ip, unsigned short port)
{
	this->sin_family = AF_INET;
	this->sin_port = htons(port);
	this->sin_addr.s_addr = inet_addr(ip.c_str());
	for(int i = 0; i < 8; i++) this->sin_zero[i] = 0;
}

IpAddress::IpAddress(unsigned short port)
{
	this->sin_family = AF_INET;
	this->sin_port = htons(port);
	this->sin_addr.s_addr = INADDR_ANY;
	for(int i = 0; i < 8; i++) this->sin_zero[i] = 0;
}

unsigned short IpAddress::getPort() const
{
	return htons(this->sin_port);
}

std::string IpAddress::getIp() const
{
	char ipstr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &this->sin_addr, ipstr, INET_ADDRSTRLEN);
	return std::string(ipstr);
}

void IpAddress::setIp(const std::string& ip)
{
	this->sin_addr.s_addr = inet_addr(ip.c_str());
}
