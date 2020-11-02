#pragma once
#include "sl_def.h"
#pragma comment(lib, "winmm.lib")
#include <windows.h>

namespace SoundLib
{
	namespace Extern
	{
		struct E_HWAVEOUT
		{
			HWAVEOUT* wo = nullptr;
			E_HWAVEOUT()
			{
				wo = new HWAVEOUT();
			}
			~E_HWAVEOUT()
			{
				delete wo;
			};
		};
	}
}