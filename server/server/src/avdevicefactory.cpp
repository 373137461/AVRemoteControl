#include "precompile.hpp"
#include "avdevicefactory.hpp"

AV_NAMESPACE_BEGIN

AVDeviceFactory::AVDeviceFactory()
{
}


AVDeviceFactory::~AVDeviceFactory()
{
}

void AVDeviceFactory::GetVideoDevices(std::vector<AVDeviceInfoList*>& device_list)
{
	AVDeviceInfoList* device_info = nullptr;
	AVInputFormat* theDeviceInputFormat = nullptr;
	while ((theDeviceInputFormat = av_input_video_device_next(theDeviceInputFormat)))
	{
		if (avdevice_list_input_sources(theDeviceInputFormat, nullptr, nullptr, &device_info) >= 0)
		{
			device_list.push_back(device_info);
		}
	}
}

void AVDeviceFactory::GetAudioDevices(std::vector<AVDeviceInfoList*>& device_list)
{
	AVDeviceInfoList* device_info = nullptr;
	AVInputFormat* theDeviceInputFormat = nullptr;
	while ((theDeviceInputFormat = av_input_audio_device_next(theDeviceInputFormat)))
	{
		if (avdevice_list_input_sources(theDeviceInputFormat, nullptr, nullptr, &device_info) >= 0)
		{
			device_list.push_back(device_info);
		}
	}
}

AV_NAMESPACE_END
