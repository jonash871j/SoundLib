#include "sl_sound_device.h"

namespace SoundLib
{
	SoundDevice::SoundDevice(us::String productName,
		uint32_t mid, 
		uint32_t pid, 
		uint32_t driverVersion,
		uint32_t formats, 
		uint32_t channels, 
		uint32_t reserved, 
		uint32_t support, 
		int32_t deviceId)	
			: 
		productName(productName), 
		mid(mid), 
		pid(pid), 
		driverVersion(driverVersion),
		formats(formats), 
		channels(channels), 
		reserved(reserved), 
		support(support), 
		deviceId(deviceId)
	{}

	SoundDevice::~SoundDevice() {}

	us::String SoundDevice::GetProductName()
	{
		return productName;
	}
	uint32_t SoundDevice::GetMid()
	{
		return mid;
	}
	uint32_t SoundDevice::GetPid()
	{
		return pid;
	}
	uint32_t SoundDevice::GetDriverVersion()
	{
		return driverVersion;
	}
	uint32_t SoundDevice::GetFormats()
	{
		return formats;
	}
	uint32_t SoundDevice::GetChannels()
	{
		return channels;
	}
	uint32_t SoundDevice::GetReserved()
	{
		return reserved;
	}
	uint32_t SoundDevice::GetSupport()
	{
		return support;
	}
	uint32_t SoundDevice::GetDeviceId()
	{
		return deviceId;
	}
}