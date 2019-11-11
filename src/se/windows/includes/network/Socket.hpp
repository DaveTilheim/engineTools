#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <iostream>
#include <WinSock2.h>
#include "IpAddress.hpp"
#include "StringFrame.hpp"
#include "ObjectFrame.hpp"

namespace se
{
	class Socket
	{
	protected:
		int sock;
		int type;
		int proto;
	public:
		Socket(int type, int proto);
		Socket(int, int, int);
		virtual ~Socket();
		void close();
		bool connected();
		int getSocket() const;
		int getType() const;
		int getProto() const;
		void bind(const IpAddress&);
		virtual void send(const StringFrame&) = 0;
		virtual StringFrame srecieve() = 0;
		virtual void send(const ObjectFrame&) = 0;
		virtual ObjectFrame orecieve() = 0;
	};
}

#endif
