#ifndef UDP_SOCKET_HPP
#define UDP_SOCKET_HPP
#include "Socket.hpp"

namespace se
{
	class UDPSocket final : public Socket
	{
	private:
		IpAddress dstIp;
	public:
		UDPSocket(int,int) = delete;
		UDPSocket(int=30000);
		void setDstIp(const std::string&);
		virtual void send(const StringFrame&) override;
		virtual StringFrame srecieve() override;
		virtual void send(const ObjectFrame&) override;
		virtual ObjectFrame orecieve() override;
	};
}

#endif
