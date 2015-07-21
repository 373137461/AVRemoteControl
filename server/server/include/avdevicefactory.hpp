#pragma once

AV_NAMESPACE_BEGIN

class AVDeviceFactory
{
public:
	AVDeviceFactory();
	~AVDeviceFactory();

	void GetVideoDevices(std::vector<AVDeviceInfoList*>& device_list);
	void GetAudioDevices(std::vector<AVDeviceInfoList*>& device_list);

};

AV_NAMESPACE_END
