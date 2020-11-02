#include "sl_sound_mixer.h"
#include "sl_misc.h"

#pragma comment(lib, "winmm.lib")
#include <Windows.h>

namespace SoundLib
{
	static bool s_isVolumeSet = false;
	static float s_volumeLeft = 25.0f;
	static float s_volumeRight = 25.0f;
	static HWAVEOUT s_waveOut = { 0 };

	void SoundMixer::SetVolume(float volumeLeft, float volumeRight)
	{
		s_volumeLeft = volumeLeft;
		s_volumeRight = volumeRight;
		s_isVolumeSet = true;

		uint32_t volume = (Misc::FloatToUInt16(volumeLeft) << 16) |
						(Misc::FloatToUInt16(volumeRight) << 0);
		waveOutSetVolume(s_waveOut, volume);
	}
	void SoundMixer::SetVolume(float volume)
	{
		SetVolume(volume, volume);
	}

	void SoundMixer::GetVolume(float& volumeLeft, float& volumeRight)
	{
		volumeLeft = s_volumeLeft;
		volumeRight = s_volumeRight;
	}
	float SoundMixer::GetVolumeLeft()
	{
		return s_volumeLeft;
	}
	float SoundMixer::GetVolumeRight()
	{
		return s_volumeRight;
	}

	bool SoundMixer::GetIsVolumeSet()
	{
		return s_isVolumeSet;
	}
}