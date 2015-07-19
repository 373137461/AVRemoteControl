#pragma once

AV_NAMESPACE_BEGIN

class AVInputStream
{
public: 
	AVInputStream(AVFormatContext *in_formart_context);
	~AVInputStream();
	
	bool operator >> (AVFrame*& aFrame);
	int width() { if (video_codec_context_) return video_codec_context_->width; return 0; }
	int height() { if (video_codec_context_) return video_codec_context_->height; return 0; }
	AVPixelFormat pix_fmt() { if (video_codec_context_) return video_codec_context_->pix_fmt; return AV_PIX_FMT_NONE;  }

private:
	bool init();
	void destroy();
	bool get_frame(AVFrame* & frame);

private: //data
	AVFormatContext* format_context_;
	AVCodecContext*  video_codec_context_;
	AVCodecContext*  audio_codec_context_;
	AVCodec*         audio_codec_;
	AVCodec*         video_codec_;
	AVFrame*         video_frame_;
	AVFrame*         audio_frame_;
	AVPacket         packet_;

	int              video_stream_index_;
	int              audio_stream_index_;
};

AV_NAMESPACE_END