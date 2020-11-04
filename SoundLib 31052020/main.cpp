#include "sound_lib.h"
#include <Windows.h>

using namespace SoundLib;
using namespace DirectSound;

int main()
{
	SoundPlayer player("Sounds/brick_armored.flac");
	SoundMixer::SetVolume(50.0f);


	while (1)
	{
		player.Replay();
		Sleep(100);
	}
}