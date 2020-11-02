#pragma once
#include "sl_format.h"

namespace SoundLib
{
	class SL_DLL_OUT FormatFlac : public Format
	{
    private:
		void* data = nullptr;

	public:
		FormatFlac();
		FormatFlac(const char* path);

	private:
		virtual void ImportHeader() override;
		virtual void ImportBlocks() override;
	};
}

