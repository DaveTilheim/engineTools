#include "UDPSocket.hpp"

using namespace se;

UDPSocket::UDPSocket(int port) : Socket(SOCK_DGRAM, IPPROTO_UDP)
{
	this->dstIp = IpAddress(port);
	std::cerr << "UDPsocket created" << std::endl;
}

void UDPSocket::setDstIp(const std::string& ip)
{
	this->dstIp.setIp(ip);
}

void UDPSocket::send(const StringFrame& frame)
{
	std::string frameStr = frame.encapsulation();
	sendto(this->sock, (const char *)frameStr.c_str(), frame.size(), 0, reinterpret_cast<const sockaddr*>(&this->dstIp), sizeof(this->dstIp));
}

StringFrame UDPSocket::srecieve()
{
	char buffer[1024];
	socklen_t len = sizeof(this->dstIp);
	int n = recvfrom(this->sock, (void *)buffer, 1024, 0, reinterpret_cast<sockaddr*>(&this->dstIp), &len);
	buffer[n] = '\0';
	return StringFrame(buffer);
}

void UDPSocket::send(const ObjectFrame& frame)
{
	char *frameObj = frame.encapsulation();
	sendto(this->sock, frameObj, frame.size(), 0, reinterpret_cast<const sockaddr*>(&this->dstIp), sizeof(this->dstIp));
	delete[] frameObj;
}

ObjectFrame UDPSocket::orecieve()
{
	char buffer[1024];
	socklen_t len = sizeof(this->dstIp);
	size_t n = recvfrom(this->sock, (void *)buffer, 1024, 0, reinterpret_cast<sockaddr*>(&this->dstIp), &len);
	buffer[n] = '\0';
	return ObjectFrame(buffer, n);
}
