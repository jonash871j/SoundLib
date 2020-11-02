#pragma once
#include "sl_def.h"
#pragma comment(lib, "winmm.lib")
#include <windows.h>

namespace SoundLib
{
	namespace Extern
	{
		struct E_WAVEHDR
		{
			WAVEHDR* wh = nullptr;
			E_WAVEHDR()
			{
				wh = new WAVEHDR();
			}
			~E_WAVEHDR()
			{
				delete wh;
			};
		};
	}
}