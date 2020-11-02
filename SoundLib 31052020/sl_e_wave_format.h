#pragma once
#include "sl_def.h"
#pragma comment(lib, "winmm.lib")
#include <windows.h>

namespace SoundLib
{
	namespace Extern
	{
		struct E_WAVEFORMATEX
		{
			WAVEFORMATEX* wf = nullptr;
			E_WAVEFORMATEX()
			{
				wf = new WAVEFORMATEX();
			}
			~E_WAVEFORMATEX()
			{
				delete wf;
			};
		};
	}
}