#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP
#include "NetHandler.hpp"

namespace se
{
	class TCPClient : public NetHandler
	{
	private:
		IpAddress ip;
	protected:
		virtual void frameRedirection(const StringFrame&) override;
	public:
		TCPClient(const IpAddress&);
		virtual ~TCPClient();
	};
}

#endif
