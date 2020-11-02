#include "sl_sound_quality.h"

namespace SoundLib
{
	SoundQuality::SoundQuality(uint16_t bitsPerSample, uint32_t sampleRate, uint16_t channels, WaveType type)
		: bitsPerSample(bitsPerSample), sampleRate(sampleRate), channels(channels), type(type) 
	{
		byteRate = (sampleRate * channels * bitsPerSample) / 8;
		blockAlign = (channels * bitsPerSample) / 8;
	}
	SoundQuality::~SoundQuality(){}
	uint32_t SoundQuality::GetByteRate()
	{
		return byteRate;
	}
	uint16_t SoundQuality::GetBlockAlign()
	{
		return blockAlign;
	}
	uint16_t SoundQuality::GetBitsPerSample()
	{
		return bitsPerSample;
	}
	uint16_t SoundQuality::GetBytesPerSample()
	{
		return bitsPerSample / 8;
	}
	uint32_t SoundQuality::GetSampleRate()
	{
		return sampleRate;
	}
	uint16_t SoundQuality::GetChannels()
	{
		return channels;
	}
	WaveType SoundQuality::GetType()
	{
		return type;
	}
}