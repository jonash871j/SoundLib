//#include "sound_lib.h"
//
//#pragma comment(lib, "dsound.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "winmm.lib")
//
//#include <Windows.h>
//#include <mmsystem.h>
//#include <dsound.h>
//#include <stdio.h>
//
//void Play(const char* path)
//{
//	Format* format = new FormatFlac(path);
//	Sound* sound = format->GetSound();
//	SoundQuality* qulity = sound->GetSoundQuality();
//
//	HWND hwnd = GetConsoleWindow();
//
//	WAVEFORMATEX waveFormat;
//	waveFormat.wFormatTag = (WORD)qulity->GetType();
//	waveFormat.nSamplesPerSec = qulity->GetSampleRate();
//	waveFormat.wBitsPerSample = qulity->GetBitsPerSample();
//	waveFormat.nChannels = qulity->GetChannels();
//	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
//	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
//	waveFormat.cbSize = 0;
//
//	DSBUFFERDESC bufferDesc;
//	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
//	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
//	bufferDesc.dwBufferBytes = (DWORD)sound->GetSize();
//	bufferDesc.dwReserved = 0;
//	bufferDesc.lpwfxFormat = &waveFormat;
//	bufferDesc.guid3DAlgorithm = GUID_NULL;
//
//	IDirectSound8* directSound;
//	IDirectSoundBuffer* tempBuffer;
//	DirectSoundCreate8(NULL, &directSound, NULL);
//	directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
//	directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
//
//	IDirectSoundBuffer8* soundBuffer;
//	tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&soundBuffer);
//	tempBuffer->Release();
//	tempBuffer = nullptr;
//
//	long long int bufferSize = 0;
//	unsigned char* bufferPtr;
//
//	soundBuffer->Lock(0, sound->GetSize(), (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, NULL, 0);
//	memcpy(bufferPtr, sound->GetBuffer(), sound->GetSize());
//	soundBuffer->Unlock((void*)sound->GetBuffer(), sound->GetSize(), NULL, 0);
//
//	soundBuffer->SetCurrentPosition(0);
//	soundBuffer->SetVolume(DSBVOLUME_MAX);
//	soundBuffer->Play(0, 0, 0);
//	Sleep(1000);
//	soundBuffer->Stop();
//}

#include "sl_dsound_player.h"
#include <Windows.h>
#include <iostream>

using namespace SoundLib;

int main()
{
	DSoundPlayer sound;
	sound.Load("Sounds/80S-Style-2.wav");
	sound.Play();
	
	float speed = 1.0f;
	float volume = 50.0f;
	float pan = 0.0f;
	
	while (1)
	{
		if (GetAsyncKeyState('Q') & 0x8000)
			speed += 0.01f;

		if (GetAsyncKeyState('A') & 0x8000)
			speed -= 0.01f;

		if (GetAsyncKeyState('W') & 0x8000)
			volume += 0.5f;

		if (GetAsyncKeyState('S') & 0x8000)
			volume -= 0.5f;

		if (GetAsyncKeyState('E') & 0x8000)
			pan += 0.01f;

		if (GetAsyncKeyState('D') & 0x8000)
			pan -= 0.01f;

		sound.SetSpeed(speed);
		sound.SetVolume(volume);
		sound.SetPan(pan);
		
		std::cout << "SPEED: " << speed  << "   VOLUME: " << volume << "   PAN: " << pan << '\n';

		Sleep(10);
	}
	//int amount = midiOutGetNumDevs();
	//std::vector<MIDIOUTCAPSA> devices;

	//for (int i = 0; i < amount; i++)
	//{
	//	MIDIOUTCAPSA device;
	//	midiOutGetDevCapsA(i, &device, sizeof(MIDIOUTCAPSA));
	//	devices.push_back(device);
	//}
	//
	//for (int i = 0; i < devices.size(); i++)
	//	std::cout << devices[i].szPname << '\n';

	//HMIDIOUT midiOut;
	//int test = 0xFFFFFFFF;
	//std::cout << &midiOut;
	//if (midiOutOpen(&midiOut, 2, NULL, 0, NULL) == MMSYSERR_NOERROR)
	//	std::cout << "Works\n";
	//else
	//	return -1;

	//char octave = 5 * 12;
	//char notes[] = { octave + 1, octave + 4, octave + 7, octave + 9, octave + 8 };

	//while (1)
	//{
	//	midiOutShortMsg(midiOut, (0x50 << 16) | (notes[(rand() % 5)] << 8) | 0x90);
	//	midiOutShortMsg(midiOut, (0x50 << 16) | ((notes[rand() % 5] - 24) << 8) | 0x90);
	//	Sleep(500);
	//}

	//try
	//{
	//	Format* format = FormatAny::Import("Sounds/80S-Style-1.flac");
	//	
	//	SoundPlayer* sp1 = new SoundPlayer(format);
	//	SoundPlayer* sp2 = new SoundPlayer("Sounds/80S-Style-2.wav");
	//	
	//	sp1->Play();
	//	//sp2->Play();

	//	while (1)
	//	{

	//		Sleep(1000);
	//	}
	//}
	//catch (std::exception exception)
	//{
	//	std::cerr << exception.what();
	//}



	//SoundPlayer sound1(L"Sounds/INS36-2.wav");
	//SoundPlayer sound2(L"Sounds/INS31.wav");

	////sound1.Play();
	////sound1.Loop(LoopFlags::Normal, 32);

	//while (!(GetAsyncKeyState(VK_F11) & 0x8000))
	//{
	//	sound1.SetPosition(rand() % sound1.GetTimeAmount());
	//	sound1.Play();
	//	Sleep(1000);
	//	sound2.SetPosition(rand() % sound2.GetTimeAmount());
	//	sound2.Play();
	//	Sleep(1000);



	///*	printf("%i \n", sound1.GetPosition());
	//	if (!sound1.GetSoundActive())
	//		printf("Done\n");*/
	//}
}
