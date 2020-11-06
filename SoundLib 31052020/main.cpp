#include "sound_lib.h"
#include <Windows.h>
#include <iostream>

using namespace SoundLib;
using namespace DirectSound;

int main()
{
	try
	{
		Format* format = new FormatWave("Sounds/80S-Style-2.wav");
		SoundPlayer soundPlayer(format);
		soundPlayer.Play();

		while (1)
		{
			if (GetAsyncKeyState(VK_UP))
				soundPlayer.Mixer.Speed(soundPlayer.Mixer.Speed() + 0.01f);
			if (GetAsyncKeyState(VK_DOWN))
				soundPlayer.Mixer.Speed(soundPlayer.Mixer.Speed() - 0.01f);

			Sleep(10);
		}
	}
	catch (std::exception exception)
	{
		std::cout << exception.what() << '\n';
	}
}