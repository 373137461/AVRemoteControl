#include "precompile.hpp"
#include "avrtmpstream.hpp"

#include "librtmp/rtmp.h"

AV_NAMESPACE_BEGIN

AVRTMPStream::AVRTMPStream()
: rtmp_(RTMP_Alloc()),
  rtmp_socket_(0)
{
}


AVRTMPStream::~AVRTMPStream()
{
	if (rtmp_ != nullptr)
	{
		RTMP_Free(rtmp_);
		rtmp_ = nullptr;
	}
}

bool AVRTMPStream::connect(const std::string url)
{
	if (rtmp_ == nullptr)
	{
		return false;
	}
	RTMP_Init(rtmp_);

	if (RTMP_SetupURL(rtmp_, url.c_str()) < 0)
	{
		return false;
	}

	RTMP_EnableWrite(rtmp_);

	if (RTMP_Connect(rtmp_, nullptr) < 0)
	{
		return false;
	}

	rtmp_socket_ = rtmp_->m_sb.sb_socket;

	if (RTMP_ConnectStream(rtmp_, 0) < 0)
	{
		return false;
	}

	return true;
}

bool AVRTMPStream::send_header(unsigned char *buf, int size)
{
	return true;
}

bool AVRTMPStream::operator<<(AVFrame*& aFrame)
{
	return put_frame(aFrame);
}

void AVRTMPStream::close()
{
	if (rtmp_)
	{
		RTMP_DeleteStream(rtmp_);
		RTMP_Close(rtmp_);
	}
}

bool AVRTMPStream::put_frame(AVFrame*& frame)
{
	//Todo: call AMF from librtmp 
	//do frame data convert to rtmp data
	return true;
}

AV_NAMESPACE_END