#include "sl_format.h"
#include "sl_sound_data.h"
#include "sfh_read_file.h"

#include <vcruntime_exception.h>

namespace SoundLib
{
	Format::~Format()
	{
		SL_DELETE(inFile);
	}
	void Format::Import(const char* path)
	{
		SL_CREATE(inFile) = new sfh::ReadFile(path);

		ImportHeader();
		ImportBlocks();

		inFile->Close();
	}
	SoundData* Format::GetSound()
	{
		return &sound;
	}
	const char* Format::GetPath()
	{
		return inFile->GetPath();
	}
}