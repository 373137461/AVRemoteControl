#include "precompile.hpp"
#include "avinputstream.hpp"

namespace
{
#if defined(_WIN32) || defined(_WIN64)
	static const char* gDesktopInputFormatString = "gdigrab";
#else
	static const char* gDesktopInputFormatString = "x11grab";
#endif
}

AVInputStream::AVInputStream(AVFormatContext *in_format_context) :
format_context_(in_format_context)
, video_codec_context_(nullptr)
, audio_codec_context_(nullptr)
, codec_(nullptr)
, video_frame_(nullptr)
, audio_frame_(nullptr)
, video_stream_index_(-1)
, audio_stream_index_(-1)
{
}

bool AVInputStream::init()
{
	if (avformat_find_stream_info(format_context_, NULL) < 0)
	{
		AVLogger::debug() << "Couldn't find stream information.";
		return false;
	}
	for (unsigned int i = 0; i < format_context_->nb_streams; i++)
	{
		if (format_context_->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream_index_ = i;
		}
		else if (format_context_->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream_index_ = i;
		}
	}
	if (video_stream_index_ == -1 && audio_stream_index_ == -1)
	{
		AVLogger::debug() << "Didn't find a video stream.";
		return false;
	}

	video_codec_context_ = format_context_->streams[video_stream_index_]->codec;
	codec_ = avcodec_find_decoder(audio_codec_context_->codec_id);
	if (codec_ == nullptr)
	{
		AVLogger::debug() << "Codec not found.";
		return false;
	}
	if (avcodec_open2(video_codec_context_, codec_, NULL) < 0)
	{
		AVLogger::debug() << "Could not open codec.";
		return false;
	}

	av_init_packet(&packet_);
	video_frame_ = av_frame_alloc();
	if (video_frame_ == nullptr)
		return false;
	audio_frame_ = av_frame_alloc();
	if (!audio_frame_)
		return false;
	return true;
}

void AVInputStream::destory()
{
	if (format_context_ ) avformat_free_context(format_context_);
	if (video_frame_) av_frame_free(&video_frame_);
	if (audio_frame_) av_frame_free(&audio_frame_);
}

AVInputStream::~AVInputStream()
{
	destory();
}


bool AVInputStream::get_frame(AVFrame* & frame)
{
	frame = nullptr;
	int frameFinished = 0;
	int nbytes;
	while (av_read_frame(format_context_, &packet_) >= 0)
	{
		if (packet_.stream_index == video_stream_index_)
		{
			nbytes = avcodec_decode_video2(video_codec_context_, video_frame_, &frameFinished, &packet_);
			if (nbytes > 0)
			{
				if (frameFinished)
				{
					frame = video_frame_;
					goto success;
				}
			}
			else
			{
				AVLogger::debug() << "Decode Video Packet Error.";
				goto failed;
			}
		}
		else if (packet_.stream_index == audio_stream_index_)
		{
			nbytes = avcodec_decode_audio4(audio_codec_context_, audio_frame_, &frameFinished, &packet_);
			if (nbytes > 0)
			{
				if (frameFinished)
				{
					frame = audio_frame_;
					goto success;
				}
			}
			else
			{
				AVLogger::debug() << "Decode Audio Packet Error.";
				goto failed;
			}
		}
		else
		{
			AVLogger::debug() << "Not Support Stream.";
			goto failed;
		}
		av_free_packet(&packet_);
	}
	return false;
failed:
	av_free_packet(&packet_);
	return false;
success:
	av_free_packet(&packet_);
	return true;
}

bool AVInputStream::operator >> (AVFrame*& frame)
{
	return get_frame(frame);
}
