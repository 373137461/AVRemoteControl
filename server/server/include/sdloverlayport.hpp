
#include <SDL.h>

class SdlOverlayPort
{
public:
	SdlOverlayPort(SDL_Surface* screen, int width, int height, AVPixelFormat pix_fmt) 
		: screen_(screen),
		width_(width),
		height_(height),
		pix_fmt_(pix_fmt)
	{
		if (screen_)
		{
			sws_context_ = sws_getContext(width_, height_, pix_fmt_,
				width_, height_, PIX_FMT_YUV420P, SWS_BILINEAR, NULL, NULL, NULL);
			overlay_ = SDL_CreateYUVOverlay(width_, height_, SDL_YV12_OVERLAY, screen_);
			rect_.x = 0;
			rect_.y = 0;
			rect_.w = width_;
			rect_.h = height_;
		}
	}

	~SdlOverlayPort()
	{
		if (overlay_)
			SDL_FreeYUVOverlay(overlay_);
		if (sws_context_)
			sws_freeContext(sws_context_);
	}

	bool put_frame(AVFrame *frame)
	{
		if (frame)
		{
				SDL_LockYUVOverlay(overlay_);
				pict_.data[0] = overlay_->pixels[0];
				pict_.data[1] = overlay_->pixels[2];
				pict_.data[2] = overlay_->pixels[1];

				pict_.linesize[0] = overlay_->pitches[0];
				pict_.linesize[1] = overlay_->pitches[2];
				pict_.linesize[2] = overlay_->pitches[1];

				// Convert the image into YUV format that SDL uses
				if (sws_context_)
				{
					sws_scale(sws_context_, (uint8_t const * const *)frame->data,
						frame->linesize, 0, height_,
						pict_.data, pict_.linesize);;
				}
				SDL_UnlockYUVOverlay(overlay_);
				SDL_DisplayYUVOverlay(overlay_, &rect_);
				return true;
		}
		return false;
	}
private:
	SwsContext* sws_context_;
	SDL_Overlay* overlay_;
	AVPicture pict_;
	SDL_Surface *screen_;
	SDL_Rect rect_;
	int width_;
	int height_;
	AVPixelFormat pix_fmt_;
};
