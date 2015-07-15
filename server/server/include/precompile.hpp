#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <functional>
#include <thread>
#include <vector>
#include <map>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
};

#include "avlogger.hpp"

class AVInputStream;

enum class AVInputStreamType
{
	Desktop,
	Camera,
	Video,
	Network
};
