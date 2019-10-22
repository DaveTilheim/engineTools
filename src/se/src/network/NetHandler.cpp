#include "NetHandler.hpp"

using namespace se;


NetHandler::NetHandler()
{

}

NetHandler::NetHandler(const TCPSocket& sock) : tcpSocket(sock)
{
	
}

NetHandler::~NetHandler()
{
	if(this->listener)
	{
		this->listener->join();
		delete this->listener;
	}
	this->tcpSocket.close();
}

TCPSocket& NetHandler::com()
{
	return this->tcpSocket;
}

bool NetHandler::isRunning()
{
	return this->running;
}

void NetHandler::stop()
{
	this->running = false;
}

void NetHandler::wait()
{
	while(this->isRunning());
}

void *NetHandler::run()
{
	std::cout << "in " << this << std::endl;
	this->running = true;
	while(this->running)
	{
		StringFrame frame;
		frame = this->tcpSocket.srecieve();
		frameRedirection(frame);
	}
	return this;
}

void NetHandler::start()
{
	std::cout << this << std::endl;
	this->listener = new std::thread(&NetHandler::run, this);
}
