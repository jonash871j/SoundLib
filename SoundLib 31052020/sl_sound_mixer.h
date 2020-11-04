#pragma once
#include "sl_def.h"

namespace SoundLib
{
	// https://stackoverflow.com/questions/42469459/how-to-change-volume-level-of-non-default-sound-device-programmatically
	static class SoundMixer // Should not be static
	{
	public:
		// Used to set volume for both speaker channels
		static void SetVolume(float volumeLeft, float volumeRight);

		// Used to set the same volume for both speaker channels
		static void SetVolume(float volume);
	
		// Used to get volume for both speaker channels
		static void GetVolume(float& volumeLeft, float& volumeRight);

	public:
		// Used to get volume for left speaker channel
		static float GetVolumeLeft();

		// Used to get volume for right speaker channel
		static float GetVolumeRight();

		// Used to get the state of volume has been set
		static bool GetIsVolumeSet();
	}SoundMixer;
}