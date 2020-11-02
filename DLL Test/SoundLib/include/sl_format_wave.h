#pragma once
#include "sl_format.h"

namespace SoundLib
{
	typedef struct WaveHeader
	{
		uint32_t riffMarker;
		uint32_t fileSize;
		uint32_t waveMarker;
		uint32_t formatChunk;
		uint32_t formatDataLength;
		WaveType waveType; // 16 bits
		uint16_t channels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t blockAlign;
		uint16_t bitsPerSample;
	}WaveHeader;

	class SL_DLL_OUT FormatWave : public Format
	{
	private:
		WaveHeader header = { 0 };

	public:
		FormatWave();
		FormatWave(const char* path);

	private:
		virtual void ImportHeader() override;
		virtual void ImportBlocks() override;

	public:
		WaveHeader GetHeader();
	};
}

