#ifndef IP_ADDRESS_HPP
#define IP_ADDRESS_HPP
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <string>
#include <iostream>

namespace se
{
	class IpAddress final : protected sockaddr_in
	{
	public:
		IpAddress(std::string ip="undefined", unsigned short port=30000);
		IpAddress(unsigned short port);
		unsigned short getPort() const;
		std::string getIp() const;
		void setIp(const std::string& ip);
	};
}

#endif
