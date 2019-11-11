#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP
#include <vector>
#include "TCPSocket.hpp"
#include "TCPClientHandler.hpp"

namespace se
{
	class TCPServer
	{
	private:
		std::vector<TCPClientHandler *> clients;
		TCPSocket socketServer;
		IpAddress ip;
	public:
		bool running = true;
		TCPServer(const IpAddress&);
		virtual ~TCPServer();
		void run(unsigned maxConn=100);
	};
}

#endif
