#include "sl_sound_data.h"
#include <memory>

namespace SoundLib
{
	SoundData::SoundData()
	{
	}
	SoundData::SoundData(uint8_t bitsPerSample, uint32_t sampleRate, uint8_t channels, WaveType type)
	{
		SetSoundQuality(bitsPerSample, sampleRate, channels, type);
	}

	SoundData::SoundData(SoundQuality quality)
		: quality(quality){}

	SoundData::~SoundData()
	{
		delete[] buffer;
	}
	void SoundData::SetBuffer(uint8_t* buffer, uint64_t size)
	{
		this->size = size;
		this->buffer = buffer;
	}
	void SoundData::SetValue(uint32_t index, uint8_t value)
	{
		buffer[index] = value;
	}
	uint32_t SoundData::GetValue(uint32_t index)
	{
		return buffer[index];
	}
	void SoundData::SetSoundQuality(uint16_t bitsPerSample, uint32_t sampleRate, uint16_t channels, WaveType type)
	{
		quality = SoundQuality(bitsPerSample, sampleRate, channels, type);
	}
	void SoundData::SetSoundQuality(SoundQuality quality)
	{
		this->quality = quality;
	}
	uint8_t* SoundData::GetBuffer()
	{
		return buffer;
	}
	uint64_t SoundData::GetSize()
	{
		return size;
	}
	SoundQuality* SoundData::GetSoundQuality()
	{
		return &quality;
	}
}