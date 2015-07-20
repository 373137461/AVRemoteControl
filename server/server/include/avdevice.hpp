#pragma once


#include "avinputstream.hpp"

AV_NAMESPACE_BEGIN

class AVDevice
{
public:
	AVDevice(const std::string & name);
	AVInputStream *create_stream(const std::string & name, AVDictionary *options = nullptr);
	~AVDevice();
private:
	AVInputFormat *format_;
	std::string name_;
};

AV_NAMESPACE_END