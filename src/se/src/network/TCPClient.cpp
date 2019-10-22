#include "TCPClient.hpp"

using namespace se;


TCPClient::TCPClient(const IpAddress& ip) : NetHandler(), ip(ip)
{
	this->tcpSocket.connect(ip);
	std::cout << "Client created" << std::endl;
}

TCPClient::~TCPClient()
{
	std::cout << "Client ended" << std::endl;
}

void TCPClient::frameRedirection(const StringFrame& frame)
{
	std::cout << "frameRedirection" << std::endl;
	std::cout << "DATA: " << frame.getData() << std::endl;
}
