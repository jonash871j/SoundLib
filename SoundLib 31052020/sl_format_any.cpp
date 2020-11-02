#include "sl_format_any.h"
#include "sl_format_wave.h"
#include "sl_format_flac.h"
#include "sl_format_raw.h"
#include "sfh_file_misc.h"

#include "us_string.h"

namespace SoundLib
{
	Format* FormatAny::Import(const char* path)
	{
		us::String extention = sfh::FileMisc::GetFileExtension(path);

		if (extention == ".wav")
			return new FormatWave(path);
		else if (extention == ".flac")
			return new FormatFlac(path);
		else
			return new FormatRaw(path);
	}
}
