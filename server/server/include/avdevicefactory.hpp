#pragma once

AV_NAMESPACE_BEGIN

class AVDeviceFactory
{
public:
	AVDeviceFactory();
	~AVDeviceFactory();
	int is_device(const AVClass *avclass)
	{
		if (!avclass)
			return 0;
			return AV_IS_INPUT_DEVICE(avclass->category) || AV_IS_OUTPUT_DEVICE(avclass->category);
	}
	int show_devices();
	void GetVideoDevices(std::vector<AVDeviceInfoList*>& device_list);
	void GetAudioDevices(std::vector<AVDeviceInfoList*>& device_list);

};

AV_NAMESPACE_END
