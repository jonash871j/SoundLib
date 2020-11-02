#include "sl_sound.h"
#include <memory>

namespace SoundLib
{
	Sound::Sound()
	{
	}
	Sound::Sound(uint8_t bitsPerSample, uint32_t sampleRate, uint8_t channels, WaveType type)
	{
		SetSoundQuality(bitsPerSample, sampleRate, channels, type);
	}

	Sound::Sound(SoundQuality quality)
		: quality(quality){}

	Sound::~Sound()
	{
		delete[] buffer;
	}
	void Sound::SetBuffer(uint8_t* buffer, uint64_t size)
	{
		this->size = size;
		this->buffer = buffer;

		// Write zero to last hundred bytes to avoid clicking when sound stops
		for (uint32_t i = 0; i < 500; i += 1)
			buffer[size - 500 + i] = 0;
	}
	void Sound::SetValue(uint32_t index, uint8_t value)
	{
		buffer[index] = value;
	}
	uint32_t Sound::GetValue(uint32_t index)
	{
		return buffer[index];
	}
	void Sound::SetSoundQuality(uint16_t bitsPerSample, uint32_t sampleRate, uint16_t channels, WaveType type)
	{
		quality = SoundQuality(bitsPerSample, sampleRate, channels, type);
	}
	void Sound::SetSoundQuality(SoundQuality quality)
	{
		this->quality = quality;
	}
	uint8_t* Sound::GetBuffer()
	{
		return buffer;
	}
	uint64_t Sound::GetSize()
	{
		return size;
	}
	SoundQuality* Sound::GetSoundQuality()
	{
		return &quality;
	}
}