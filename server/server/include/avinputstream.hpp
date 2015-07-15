#pragma once

#include "precompile.hpp"

class AVInputStream
{
public: //function
	AVInputStream(AVFormatContext *in_formart_context);
	~AVInputStream();
	bool init();

	bool operator >> (AVFrame*& aFrame); 
private:
	void destroy();
	bool get_frame(AVFrame* & frame);

private: //data
	AVFormatContext* format_context_;
	AVCodecContext*  video_codec_context_;
	AVCodecContext*  audio_codec_context_;
	AVCodec*         codec_;
	AVFrame*         video_frame_;
	AVFrame*         audio_frame_;
	AVPacket         packet_;

	int              video_stream_index_;
	int              audio_stream_index_;
};
