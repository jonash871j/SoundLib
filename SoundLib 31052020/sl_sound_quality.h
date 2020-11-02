#pragma once
#include "sl_def.h"

namespace SoundLib
{
	class SL_DLL_OUT SoundQuality
	{
	private:
		uint32_t byteRate = 176400;
		uint16_t blockAlign = 4;
		uint16_t bitsPerSample = 16;
		uint32_t sampleRate = 44100;
		uint16_t channels = 2;
		WaveType type = WaveType::PCM;

	public:
		SoundQuality(uint16_t bitsPerSample = 16, uint32_t sampleRate = 44100, uint16_t channels = 2, WaveType type = WaveType::PCM);
		~SoundQuality();

	public:
		uint32_t GetByteRate();
		uint16_t GetBlockAlign();
		uint16_t GetBitsPerSample();
		uint16_t GetBytesPerSample();
		uint32_t GetSampleRate();
		uint16_t GetChannels();
		WaveType GetType();
	};
}