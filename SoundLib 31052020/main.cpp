//#include "sound_lib.h"
//#include "simple_file_handler.h"
//#include <memory>
//#include <Windows.h>
//#include <iostream>
//#include <vector>
//
//#pragma comment(lib, "winmm.lib")
//
//using namespace SoundLib;
//
//int main()
//{
//	int amount = midiOutGetNumDevs();
//	std::vector<MIDIOUTCAPSA> devices;
//
//	for (int i = 0; i < amount; i++)
//	{
//		MIDIOUTCAPSA device;
//		midiOutGetDevCapsA(i, &device, sizeof(MIDIOUTCAPSA));
//		devices.push_back(device);
//	}
//	
//	for (int i = 0; i < devices.size(); i++)
//		std::cout << devices[i].szPname << '\n';
//
//	HMIDIOUT midiOut;
//	int test = 0xFFFFFFFF;
//	std::cout << &midiOut;
//	if (midiOutOpen(&midiOut, 2, NULL, 0, NULL) == MMSYSERR_NOERROR)
//		std::cout << "Works\n";
//	else
//		return -1;
//
//	char octave = 5 * 12;
//	char notes[] = { octave + 1, octave + 4, octave + 7, octave + 9, octave + 8 };
//
//	while (1)
//	{
//		midiOutShortMsg(midiOut, (0x50 << 16) | (notes[(rand() % 5)] << 8) | 0x90);
//		midiOutShortMsg(midiOut, (0x50 << 16) | ((notes[rand() % 5] - 24) << 8) | 0x90);
//		Sleep(500);
//	}
//
//	//try
//	//{
//	//	Format* format = FormatAny::Import("Sounds/80S-Style-1.flac");
//	//	
//	//	SoundPlayer* sp1 = new SoundPlayer(format);
//	//	SoundPlayer* sp2 = new SoundPlayer("Sounds/80S-Style-2.wav");
//	//	
//	//	sp1->Play();
//	//	//sp2->Play();
//
//	//	while (1)
//	//	{
//
//	//		Sleep(1000);
//	//	}
//	//}
//	//catch (std::exception exception)
//	//{
//	//	std::cerr << exception.what();
//	//}
//
//
//
//	//SoundPlayer sound1(L"Sounds/INS36-2.wav");
//	//SoundPlayer sound2(L"Sounds/INS31.wav");
//
//	////sound1.Play();
//	////sound1.Loop(LoopFlags::Normal, 32);
//
//	//while (!(GetAsyncKeyState(VK_F11) & 0x8000))
//	//{
//	//	sound1.SetPosition(rand() % sound1.GetTimeAmount());
//	//	sound1.Play();
//	//	Sleep(1000);
//	//	sound2.SetPosition(rand() % sound2.GetTimeAmount());
//	//	sound2.Play();
//	//	Sleep(1000);
//
//
//
//	///*	printf("%i \n", sound1.GetPosition());
//	//	if (!sound1.GetSoundActive())
//	//		printf("Done\n");*/
//	//}
//}
//
//#include "sound_lib.h"
//
//using namespace SoundLib;
//
//int main()
//{
//	FormatFlac format = "Sounds/theme.flac";
//	SoundPlayer sp = &format;
//
//	sp.Play();
//
//	while (1)
//	{
//
//	}
//}