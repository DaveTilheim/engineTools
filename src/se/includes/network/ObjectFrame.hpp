#ifndef OBJECT_FRAME_HPP
#define OBJECT_FRAME_HPP
#include "Frame.hpp"
#include <iostream>
#include <cstring>

namespace se
{
	class ObjectFrame : public Frame
	{
	private:
		void *data = nullptr;
		size_t dsize = 0;
	public:
		ObjectFrame();
		ObjectFrame(const Header&, void *data, size_t size);
		ObjectFrame(int src, int dst, int type, void *data, size_t size);
		ObjectFrame(const ObjectFrame&);
		ObjectFrame(void *data, size_t dsize);
		template <class T> ObjectFrame(const Header&, const T&);
		template <class T> ObjectFrame(int src, int dst, int type, const T&);
		virtual ~ObjectFrame();
		void *getData() const;
		char *encapsulation() const;
		ObjectFrame& operator=(const ObjectFrame&);
		void print(std::ostream&);
		virtual size_t size() const;
		template <class T> operator T() const;
		template <class T> operator T*() const;
	};

	template <class T>
	ObjectFrame::ObjectFrame(const Header& header, const T& data) : ObjectFrame(header, (void*)&data, sizeof(data))
	{

	}

	template <class T>
	ObjectFrame::ObjectFrame(int src, int dst, int type, const T& data) : ObjectFrame(src, dst, type, (void*) &data, sizeof(data))
	{

	}

	template <class T>
	ObjectFrame::operator T() const
	{
		std::cout << "not a pointer" << std::endl;
		return *(T *)this->getData();
	}

	template <class T>
	ObjectFrame::operator T*() const
	{
		std::cout << "pointer" << std::endl;
		void *dynObj = malloc(this->dsize);
		memcpy(dynObj, this->getData(), this->dsize);
		return (T *)dynObj;
	}
}

#endif
