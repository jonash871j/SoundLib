#include "sound_lib.h"

using namespace SoundLib;

inline FormatFlac format;
inline SoundPlayer soundPlayer;

int main()
{
	format = "Sounds/theme.flac";
	soundPlayer = &format;
	soundPlayer.Play();

	while (1)
	{

	}
}