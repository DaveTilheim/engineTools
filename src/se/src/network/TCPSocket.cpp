#include "TCPSocket.hpp"

using namespace se;

TCPSocket::TCPSocket() : Socket(SOCK_STREAM, 0)
{
	std::cerr << "TCPsocket created" << std::endl;
}

TCPSocket::TCPSocket(int sock) : Socket(sock, SOCK_STREAM, 0)
{
	std::cerr << "TCPsocket created: " << sock << std::endl;
}

void TCPSocket::listen(unsigned maxConn) const
{
	if(::listen(this->sock, maxConn))
	{
		std::cout << "listen failed" << std::endl;
		exit(1);
	}
}

TCPSocket TCPSocket::accept() const
{
	sockaddr_in info;
	socklen_t len = sizeof(info);
	int externTCPS = ::accept(this->sock, reinterpret_cast<sockaddr*>(&info), &len);
	if(externTCPS < 0)
	{
		std::cout << "accept failed" << std::endl;
		exit(1);
	}
	return TCPSocket(externTCPS);
}

void TCPSocket::connect(const IpAddress& serverId) const
{
	if(::connect(this->sock, reinterpret_cast<const sockaddr*>(&serverId), sizeof(serverId)) < 0)
	{
		std::cout << "connection failed" << std::endl;
		exit(1);
	}
}

void TCPSocket::send(const StringFrame& frame)
{
	std::string frameStr = frame.encapsulation();
	std::cout << "Envoie de : " << frameStr << std::endl;
	::send(this->sock, (const char *)frameStr.c_str(), frame.size(), 0);
}

StringFrame TCPSocket::srecieve()
{
	char buffer[1024];
	int n = recv(this->sock, (void *)buffer, 1024, 0);
	buffer[n] = '\0';
	std::cout << "Réception de : " << buffer << std::endl;
	return StringFrame(buffer);
}

void TCPSocket::send(const ObjectFrame& frame)
{
	char *frameObj = frame.encapsulation();
	::send(this->sock, frameObj, frame.size(), 0);
	delete[] frameObj;
}

ObjectFrame TCPSocket::orecieve()
{
	char buffer[1024];
	size_t n = recv(this->sock, (void *)buffer, 1024, 0);
	buffer[n] = '\0';
	return ObjectFrame(buffer, n);
}

TCPSocket& TCPSocket::operator=(const TCPSocket& cp)
{
	this->sock = cp.sock;
	this->proto = cp.proto;
	this->type = cp.type;
	return *this;
}
