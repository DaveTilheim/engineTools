#ifndef STRING_FRAME_HPP
#define STRING_FRAME_HPP
#include <string>
#include <sstream>
#include <sys/types.h>
#include "Frame.hpp"

namespace se
{
	class StringFrame : public Frame
	{
	private:
		std::string data = "";
	public:
		StringFrame();
		StringFrame(const Header&, std::string data);
		StringFrame(int src, int dst, int type, std::string data);
		StringFrame(std::string);
		StringFrame(const StringFrame&);
		std::string getData() const;
		std::string encapsulation() const;
		StringFrame& operator=(const StringFrame&);
		virtual size_t size() const;
	};
}

#endif
