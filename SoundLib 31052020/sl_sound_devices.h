#pragma once
#include "sl_def.h"
#include "sl_sound_device.h"

namespace SoundLib
{
	class SL_DLL_OUT SoundDevices
	{
	private:
		uint32_t amount;
		SoundDevice** soundDevices = nullptr;

	public:
		SoundDevices();
		~SoundDevices();

	public:
		uint32_t GetAmount();
		SoundDevice** GetDevices();
		SoundDevice* GetDevice(uint32_t i);
		SoundDevice* GetDefaultDevice();
	};
}

