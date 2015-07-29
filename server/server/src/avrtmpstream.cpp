#include "precompile.hpp"
#include "avrtmpstream.hpp"

#include "librtmp/rtmp.h"

AV_NAMESPACE_BEGIN

AVRTMPStream::AVRTMPStream()
{

}


AVRTMPStream::~AVRTMPStream()
{

}

bool AVRTMPStream::connect(const std::string url)
{
	if (RTMP_SetupURL(rtmp_, url.c_str()) < 0) {
		return false;
	}

	RTMP_EnableWrite(rtmp_);

	if (RTMP_Connect(rtmp_, NULL) < 0) {
		return false;
	}

	rtmp_socket_ = rtmp_->m_sb.sb_socket;

	if (RTMP_ConnectStream(rtmp_, 0) < 0) {
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
	return true;
}

void AVRTMPStream::close()
{
	if (rtmp_)
	{
		RTMP_Close(rtmp_);
		RTMP_Free(rtmp_);
		rtmp_ = NULL;
	}
}

bool AVRTMPStream::put_frame(AVFrame*& frame)
{
	return true;
}

AV_NAMESPACE_END