#include "precompile.hpp"
#include "avdevice.hpp"
#include <string>

AV_NAMESPACE_BEGIN

AVDevice::AVDevice(const std::string & name) 
:name_(name),
format_(nullptr)
{
	format_ = av_find_input_format(name_.c_str());
}

AVInputStream* AVDevice::create_stream(const std::string & name, AVDictionary *options)
{
	if (format_)
	{
		AVFormatContext *format_context = nullptr;
		if (avformat_open_input(&format_context, name.c_str(), format_, &options) != 0)
		{
			AVLogger::debug() << "Couldn't open input stream.";
			return nullptr;
		}
		return new AVInputStream(format_context);
	}
	return nullptr;
}

AVDevice::~AVDevice()
{
}

AV_NAMESPACE_END