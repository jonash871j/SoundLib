#pragma once
#include "sl_def.h"

namespace SoundLib
{
	class SL_DLL_OUT SoundDevice
	{ 
		friend class SoundDevices;
	private:
		us::String productName;
		uint32_t mid;
		uint32_t pid;
		uint32_t driverVersion;
		uint32_t formats;
		uint32_t channels;
		uint32_t reserved;
		uint32_t support;
		int32_t deviceId;

	private:
		SoundDevice(
			us::String productName,
			uint32_t mid, 
			uint32_t pid, 
			uint32_t driverVersion,
			uint32_t formats, 
			uint32_t channels, 
			uint32_t reserved, 
			uint32_t support, 
			int32_t deviceId
		);

	public:
		~SoundDevice();

	public:
		us::String GetProductName();
		uint32_t GetMid(); 
		uint32_t GetPid(); 
		uint32_t GetDriverVersion();
		uint32_t GetFormats();   
		uint32_t GetChannels();
		uint32_t GetReserved();   
		uint32_t GetSupport();
		uint32_t GetDeviceId();
	};
}