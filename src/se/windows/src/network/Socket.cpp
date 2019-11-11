#include "Socket.hpp"

using namespace se;

Socket::Socket(int type, int proto)
{
	if((this->sock = socket(AF_INET, type, proto)) < 0)
	{
		std::cerr << "error at socket creation" << std::endl;
	}
	else
	{
		this->type = type;
		this->proto = proto;
	}
	std::cerr << "socket opened: " << this->sock << std::endl;
}

Socket::Socket(int sock, int type, int proto)
{
	this->sock = sock;
	this->type = type;
	this->proto = proto;
	std::cerr << "socket opened: " << this->sock << std::endl;
}

Socket::~Socket()
{
	this->close();
}

bool Socket::connected()
{
	int optval;
	socklen_t optlen = sizeof(optval);
	int res = getsockopt(this->sock,SOL_SOCKET,SO_ERROR,&optval, &optlen);
	if(optval == 0 and res == 0)
	{
		return true;
	}
	return false;
}

void Socket::close()
{
	if(this->connected())
	{
		::close(this->sock);
		std::cerr << "socket closed: " << this->sock << std::endl;
	}
}

int Socket::getSocket() const
{
	return this->sock;
}

int Socket::getType() const
{
	return this->type;
}

int Socket::getProto() const
{
	return this->proto;
}

void Socket::bind(const IpAddress& ip)
{
	if(::bind(this->sock, reinterpret_cast<const sockaddr*>(&ip), sizeof(ip)) < 0)
	{
		std::cerr << "error for binding socket at " << ip.getIp() << std::endl;
		exit(1);
	}
}
