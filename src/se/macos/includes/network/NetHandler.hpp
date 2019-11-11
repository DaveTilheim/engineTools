#ifndef NET_HANDLER_HPP
#define NET_HANDLER_HPP
#include "TCPSocket.hpp"
#include <thread>

namespace se
{
	class NetHandler
	{
	private:
		std::thread *listener = nullptr;
		bool running = true;
		void *run();
	protected:
		TCPSocket tcpSocket;
		NetHandler();
		NetHandler(const TCPSocket&);
		virtual void frameRedirection(const StringFrame&) = 0;
	public:
		virtual ~NetHandler();
		virtual void start() final;
		virtual void stop() final;
		virtual bool isRunning() final;
		virtual void wait() final;
		TCPSocket& com();
	};
}

#endif
