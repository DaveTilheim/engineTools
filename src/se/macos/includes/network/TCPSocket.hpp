#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP
#include "Socket.hpp"

namespace se
{
	class TCPSocket final : public Socket
	{
	public:
		TCPSocket(int,int) = delete;
		TCPSocket();
		TCPSocket(int);
		void listen(unsigned maxConn=100) const;
		TCPSocket accept() const;
		void connect(const IpAddress&) const;
		virtual void send(const StringFrame&) override;
		virtual StringFrame srecieve() override;
		virtual void send(const ObjectFrame&) override;
		virtual ObjectFrame orecieve() override;
		TCPSocket& operator=(const TCPSocket&);
	};
}

#endif
