#pragma once
#include "sl_format.h"
#include "sl_sound_quality.h"

namespace SoundLib
{
	class SL_DLL_OUT FormatRaw : public Format
	{
	private:
		SoundQuality quality;

	public:
		FormatRaw();
		FormatRaw(const char* path);
		FormatRaw(const char* path, SoundQuality quality);

	public:
		void Import(const char* path, SoundQuality quality);

	private:
		virtual void ImportHeader() override;
		virtual void ImportBlocks() override;
	};
}

