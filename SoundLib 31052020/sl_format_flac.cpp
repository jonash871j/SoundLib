#include "sl_format_flac.h"
#include "sl_sound.h"
#include "sfh_read_file.h"

#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.hpp"


namespace SoundLib
{
	FormatFlac::FormatFlac()
		: Format()
	{
	}
	FormatFlac::FormatFlac(const char* path)
	{
		Import(path);
	}

	void FormatFlac::ImportHeader()
	{
	/*	if ((std::wstring)inFile->GetFileExtension() != L".flac")
			ThrowError(ErrorCode::InvalidExtension, inFile->GetPath(), L".wav");*/

		// Not used to read flac file
		inFile->Close();

		// Reads header
		drflac* data = drflac_open_file(inFile->GetPath(), NULL);

		// Checks if data is NULL 
		if (data == NULL)
			ThrowError(ErrorCode::CorruptedFile, inFile->GetPath());

		// Sets sound quality
		sound.SetSoundQuality(
			data->bitsPerSample,
			data->sampleRate,
			data->channels,
			WaveType::PCM
		);
		this->data = data;
	}
	void FormatFlac::ImportBlocks()
	{
		drflac* data = (drflac*)this->data;

		size_t size = data->totalPCMFrameCount * data->channels * sizeof(int16_t);
		int16_t* pSampleData = (int16_t*)malloc(size);
		drflac_read_pcm_frames_s16(data, data->totalPCMFrameCount, pSampleData);

		sound.SetBuffer((uint8_t*)pSampleData, size);

		drflac_close(data);
	}
}
