#ifndef TCP_CLIENT_HANDLER_HPP
#define TCP_CLIENT_HANDLER_HPP
#include "NetHandler.hpp"

namespace se
{
	class TCPClientHandler : public NetHandler
	{
	private:
		const std::vector<TCPClientHandler *>& serverClients;
	protected:
		virtual void frameRedirection(const StringFrame&) override;
	public:
		TCPClientHandler(const TCPSocket&, const std::vector<TCPClientHandler *>&);
		virtual ~TCPClientHandler();
	};
}

#endif
