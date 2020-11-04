#include "sl_format_raw.h"
#include "sl_sound_data.h"
#include "sfh_read_file.h"
#include "sfh_file_misc.h"

#include <windows.h>

namespace SoundLib
{
	FormatRaw::FormatRaw(){}

	FormatRaw::FormatRaw(const char* path)
	{
		Format::Import(path);
	}

	FormatRaw::FormatRaw(const char* path, SoundQuality quality)
		: quality(quality)
	{
		Format::Import(path);
	}

	void FormatRaw::Import(const char* path, SoundQuality quality)
	{
		this->quality = quality;
		Format::Import(path);
	}

	void FormatRaw::ImportHeader()
	{
		sound.SetSoundQuality(quality);
	}

	void FormatRaw::ImportBlocks()
	{
		size_t size = sfh::FileMisc::GetFileSize(inFile->GetPath());
		uint8_t* buffers = (uint8_t*)inFile->ReadBuffer(size);
		sound.SetBuffer(buffers, size);
	}
}
