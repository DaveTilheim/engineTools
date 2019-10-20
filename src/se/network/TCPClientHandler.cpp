#include "TCPClientHandler.hpp"

using namespace se;


TCPClientHandler::TCPClientHandler(const TCPSocket& sock, const std::vector<TCPClientHandler *>& serverClients) : NetHandler(sock), serverClients(serverClients)
{
	std::cout << "Client handler created" << std::endl;
}

TCPClientHandler::~TCPClientHandler()
{
	std::cout << "Client Handler ended" << std::endl;
}

void TCPClientHandler::frameRedirection(const StringFrame& frame)
{
	std::cout << "frameRedirection" << std::endl;
	std::cout << "DATA: " << frame.getData() << std::endl;
}
