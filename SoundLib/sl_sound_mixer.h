#pragma once
#include "sl_def.h"

namespace SoundLib
{
	static class SL_DLL_OUT SoundMixer
	{
	public:
		// Used to set volume for both speaker channels
		static void SetVolume(float volumeLeft, float volumeRight);

		// Used to set the same volume for both speaker channels
		static void SetVolume(float volume);
	
	public:
		// Used to get volume for both speaker channels
		static void GetVolume(float& volumeLeft, float& volumeRight);

		// Used to get volume for left speaker channel
		static float GetVolumeLeft();

		// Used to get volume for right speaker channel
		static float GetVolumeRight();

	public:
		// Used to get the state of volume has been set
		static bool GetIsVolumeSet();
	}SoundMixer;
}