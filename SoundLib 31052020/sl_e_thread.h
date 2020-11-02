#pragma once
#include "sl_def.h"
#include <thread>

namespace SoundLib
{
	namespace Extern
	{
		struct E_Thread
		{
			std::thread t;
			~E_Thread()
			{
				if (t.joinable())
					t.detach();
			};
		};
	}
}