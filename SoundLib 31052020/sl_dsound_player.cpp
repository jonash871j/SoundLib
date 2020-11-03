#include "sl_dsound_player.h"
#include "sl_format_any.h"
#include <iostream>

namespace SoundLib
{
	#pragma region WINAPI_INDLUDES
	#pragma comment(lib, "dsound.lib")
	#pragma comment(lib, "dxguid.lib")
	#pragma comment(lib, "winmm.lib")

	#include <wtypes.h>
	#include <mmsystem.h>
	#include <dsound.h>
	#pragma endregion

	DSoundPlayer::DSoundPlayer()
	{
		waveFormat = new WAVEFORMATEX;
		bufferDesc = new DSBUFFERDESC;
	}
	DSoundPlayer::~DSoundPlayer()
	{
		delete waveFormat;
		delete bufferDesc;
	}
	void DSoundPlayer::Change(Sound* sound)
	{
		this->sound = sound;

		waveFormat->wFormatTag = (WORD)sound->GetSoundQuality()->GetType();
		waveFormat->nSamplesPerSec = sound->GetSoundQuality()->GetSampleRate();
		waveFormat->wBitsPerSample = sound->GetSoundQuality()->GetBitsPerSample();
		waveFormat->nChannels = sound->GetSoundQuality()->GetChannels();
		waveFormat->nBlockAlign = (waveFormat->wBitsPerSample / 8) * waveFormat->nChannels;
		waveFormat->nAvgBytesPerSec = waveFormat->nSamplesPerSec * waveFormat->nBlockAlign;
		waveFormat->cbSize = 0;

		bufferDesc->dwSize = sizeof(DSBUFFERDESC);
		bufferDesc->dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
		bufferDesc->dwBufferBytes = (DWORD)sound->GetSize();
		bufferDesc->dwReserved = 0;
		bufferDesc->lpwfxFormat = waveFormat;
		bufferDesc->guid3DAlgorithm = GUID_NULL;

		DirectSoundCreate8(NULL, &directSound, NULL);
		directSound->SetCooperativeLevel(GetConsoleWindow(), DSSCL_PRIORITY);
		directSound->CreateSoundBuffer(bufferDesc, &tempBuffer, NULL);

		tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&soundBuffer);
		tempBuffer->Release();
		tempBuffer = nullptr;

		long long int bufferSize = 0;
		unsigned char* bufferPtr;

		soundBuffer->Lock(0, sound->GetSize(), (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, NULL, 0);
		memcpy(bufferPtr, sound->GetBuffer(), sound->GetSize());
		soundBuffer->Unlock((void*)sound->GetBuffer(), (DWORD)sound->GetSize(), NULL, 0);
	}
	void DSoundPlayer::Change(Format* format)
	{
		Change(format->GetSound());
	}
	void DSoundPlayer::Load(const char* path)
	{
		Format* format = FormatAny::Import(path);
		Change(format);
		delete format;
	}
	void DSoundPlayer::Play()
	{
		if (states == States::Stopped)
		{
			soundBuffer->Play(0, 0, 0);
			states = States::Active;
		}
	}
	void DSoundPlayer::Replay()
	{
		soundBuffer->SetCurrentPosition(0);
		states = States::Active;
	}
	void DSoundPlayer::Pause()
	{
		if (states == States::Active)
		{
			soundBuffer->Stop();
			states = States::Paused;
		}
	}
	void DSoundPlayer::Resume()
	{
		if (states == States::Paused)
		{
			soundBuffer->Play(0, 0, 0);
			states = States::Active;
		}
	}
	void DSoundPlayer::Stop()
	{
		soundBuffer->Stop();
		states = States::Stopped;
	}
	void DSoundPlayer::SetSpeed(float speed)
	{
		if (speed < 0.002f)
			speed = 0.002f;
		else if (speed > 4.545f)
			speed = 4.545f;

		soundBuffer->SetFrequency(DWORD(44000.0f * speed));
	}
	void DSoundPlayer::SetVolume(float volume)
	{
		const float maxVolume = -(float)DSBVOLUME_MIN; // Not a bug.

		if (volume < 1)
			volume = 1;
		else if (volume > maxVolume)
			volume = maxVolume;

		soundBuffer->SetVolume(-LONG(maxVolume / volume));
	}
	void DSoundPlayer::SetPan(float pan)
	{
		const float maxPan = (float)DSBPAN_RIGHT;

		if (pan < -maxPan)
			pan = -maxPan;
		else if (pan > maxPan)
			pan = maxPan;

		soundBuffer->SetPan(LONG(pan * maxPan));
	}
}

