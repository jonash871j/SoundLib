#pragma once
#include "sl_def.h"
#include "sl_format.h"

namespace SoundLib
{
	static class SL_DLL_OUT FormatAny
	{
	public:
		/// <summary>
		/// Used to import any sound file from path
		/// </summary>
		/// <param name="path"></param>
		/// <returns>
		/// <para/>sound file
		/// <para/> raw sound file if not supported
		/// </returns>
		static Format* Import(const char* path);
	}FormatAny;
}

