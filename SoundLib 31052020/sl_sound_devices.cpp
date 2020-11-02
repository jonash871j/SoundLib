#include "sl_sound_devices.h"
#include "sl_sound_device.h"
#include "sl_misc.h"

#pragma comment(lib, "winmm.lib")
#include <Windows.h>

namespace SoundLib
{
	SoundDevices::SoundDevices()
	{
		WAVEOUTCAPS woc;

		// Gets amount of valid sound output devices
		amount = waveOutGetNumDevs();
		for (uint32_t i = 0; i < amount; i++)
		{
			if (waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)) != S_OK)
				amount--;
		}

		// Creates sound device array
		soundDevices = new SoundDevice*[amount];

		// Gets information for each sound device
		for (uint32_t i = 0; i < amount; i++)
		{
			if (waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)) == S_OK)
			{
				soundDevices[i] = new SoundDevice(
					woc.szPname, 
					woc.wMid, 
					woc.wPid, 
					woc.vDriverVersion,
					woc.dwFormats, 
					woc.wChannels, 
					woc.wReserved1,
					woc.dwSupport, 
					i
				);
			}
		}
	}
	SoundDevices::~SoundDevices()
	{
		delete[] soundDevices;
	}

	uint32_t SoundDevices::GetAmount()
	{
		return amount;
	}
	SoundDevice** SoundDevices::GetDevices()
	{
		return soundDevices;
	}
	SoundDevice* SoundDevices::GetDevice(uint32_t i)
	{
		return soundDevices[i];
	}
	SoundDevice* SoundDevices::GetDefaultDevice()
	{
		return soundDevices[0];
	}
}