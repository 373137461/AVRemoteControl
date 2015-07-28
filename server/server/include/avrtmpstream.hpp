#pragma once
#include "precompile.hpp"

#include "librtmp/rtmp.h"
#include "librtmp/amf.h"
#include "librtmp/log.h"

AV_NAMESPACE_BEGIN

class AVRTMPStream
{
public:
	AVRTMPStream();
	~AVRTMPStream();

	bool connect(const std::string url);
	bool send_header(unsigned char *buf, int size);
	bool operator << (AVFrame*& aFrame);
	void close();

private:
	bool put_frame(AVFrame*& frame);

private: //data
	RTMP*          rtmp_;
	int            rtmp_socket_;
};

AV_NAMESPACE_END