#include "TCPServer.hpp"

using namespace se;


TCPServer::TCPServer(const IpAddress& ip) : ip(ip)
{
	this->socketServer.bind(ip);
}

TCPServer::~TCPServer()
{
	for(auto ch : this->clients)
	{
		ch->wait();
		delete ch;
	}
	std::cout << "server stoped" << std::endl;
}

void TCPServer::run(unsigned maxConn)
{
	this->socketServer.listen(maxConn);
	this->running = true;
	while(this->running)
	{
		TCPSocket socketClient = this->socketServer.accept();
		std::cout << "client accepté" << std::endl;
		TCPClientHandler *clientHandler = new TCPClientHandler(socketClient, this->clients);
		std::cout << "client créé" << std::endl;
		this->clients.push_back(clientHandler);
		clientHandler->start();
		std::cout << "client lancé" << std::endl;
	}
}
