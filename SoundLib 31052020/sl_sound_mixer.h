#pragma once
#include "sl_def.h"

namespace SoundLib
{
	namespace SoundMixer
	{
		// Used to set volume for both speaker channels
		static void SetVolume(float volumeLeft, float volumeRight);

		// Used to set the same volume for both speaker channels
		static void SetVolume(float volume);
	
		// Used to get volume for both speaker channels
		static void GetVolume(float& volumeLeft, float& volumeRight);

		// Used to get volume for left speaker channel
		static float GetVolumeLeft();

		// Used to get volume for right speaker channel
		static float GetVolumeRight();

		// Used to get the state of volume has been set
		static bool GetIsVolumeSet();
	};
}