#include "ObjectFrame.hpp"

using namespace se;


ObjectFrame::ObjectFrame() : Frame()
{

}

ObjectFrame::ObjectFrame(const Header& header, void *data, size_t size) : Frame(header), dsize(size)
{
	this->data = malloc(this->dsize);
	memcpy(this->data, data, this->dsize);
}

ObjectFrame::ObjectFrame(int src, int dst, int type, void *data, size_t size) : Frame(src, dst, type), data(data), dsize(size)
{
	this->data = malloc(this->dsize);
	memcpy(this->data, data, this->dsize);
}

ObjectFrame::ObjectFrame(void *eframe, size_t dsize) : Frame(), dsize(dsize)
{
	memcpy(&this->header, eframe, sizeof(Header));
	this->data = malloc(dsize);
	memcpy(this->data,(char*)eframe + sizeof(Header), dsize);
}

ObjectFrame::ObjectFrame(const ObjectFrame& cp)
{
	*this = cp;
}

ObjectFrame::~ObjectFrame()
{
	if(this->data)
	{
		free(this->data);
	}
}

void *ObjectFrame::getData() const
{
	return this->data;
}

char *ObjectFrame::encapsulation() const
{
	char *frame = new char[sizeof(Header) + dsize];
	memcpy(frame, &header, sizeof(Header));
	memcpy(frame+sizeof(Header), data, dsize);
	return frame;
}

ObjectFrame& ObjectFrame::operator=(const ObjectFrame& cp)
{
	if(this->data)
	{
		free(this->data);
	}
	this->header = cp.header;
	this->data = malloc(cp.dsize);
	memcpy(this->data, cp.data, cp.dsize);
	this->dsize = cp.dsize;
	return *this;
}

size_t ObjectFrame::size() const
{
	return sizeof(Header) + this->dsize;
}

void ObjectFrame::print(std::ostream& out)
{
	char *eframe = encapsulation();
	for(int i = 0; i < size(); i++)
	{
		for(int j = 0; j < 8; j++)
		{
			out << (((unsigned)eframe[i] >> (8-j-1)) & 1);
		}
		out << ":";
	}
	std::cout << std::endl;
	delete[] eframe;
}


