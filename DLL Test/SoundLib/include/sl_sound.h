#pragma once
#include "sl_def.h"
#include "sl_sound_quality.h"

namespace SoundLib
{
	class SL_DLL_OUT Sound
	{ 
	private:
		uint8_t* buffer = nullptr;
		uint64_t size = 0;
		SoundQuality quality;

	public:
		Sound();

		// Used to set sound quality
		Sound(uint8_t bitsPerSample, uint32_t sampleRate, uint8_t channels, WaveType type);

		// Used to set sound quality
		Sound(SoundQuality quality);

		~Sound();

	public:
		// Used to set sound buffer array
		void SetBuffer(uint8_t* buffer, uint64_t size);

		// Used to set value in buffer array
		void SetValue(uint32_t index, uint8_t value);

		// Used to get value in buffer array
		uint32_t GetValue(uint32_t index);

		// Used to set sound quality
		void SetSoundQuality(uint16_t bitsPerSample, uint32_t sampleRate, uint16_t channels, WaveType type);

		// Used to set sound quality
		void SetSoundQuality(SoundQuality quality);

	public:
		// Used to get sound buffer array
		uint8_t* GetBuffer();

		// Used to get size of buffer
		uint64_t GetSize();

		// Used to get SoundQulity structure
		SoundQuality* GetSoundQuality();
	};
}