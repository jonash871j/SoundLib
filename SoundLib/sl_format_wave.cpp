#include "sl_format_wave.h"
#include "sl_sound.h"
#include "sfh_read_file.h"
#include "sfh_file_misc.h"
#include <string>

namespace SoundLib
{
	FormatWave::FormatWave()
		: Format()
	{
	}

	FormatWave::FormatWave(const char* path)
	{
		Import(path);
	}

	void FormatWave::ImportHeader()
	{
		if (!(inFile->GetFileExtension() == ".wav"))
			ThrowError(ErrorCode::InvalidExtension, inFile->GetPath(), ".wav");

		// Reads wave header
		header = inFile->ReadClass<WaveHeader>();

		// Sets sound quality
		sound.SetSoundQuality(
			header.bitsPerSample,
			header.sampleRate,
			header.channels,
			header.waveType
		);
	}
	void FormatWave::ImportBlocks()
	{
		uint64_t size = header.fileSize - sizeof(WaveHeader);
		uint8_t* buffers = (uint8_t*)inFile->ReadBuffer(size);
		sound.SetBuffer(buffers, size);
	}
	WaveHeader FormatWave::GetHeader()
	{
		return header;
	}
}
