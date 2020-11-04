#include "sl_ds_sound_player.h"
#include "sl_format_any.h"
#include <iostream>

namespace SoundLib{
namespace DirectSound
{
	#pragma comment(lib, "dsound.lib")
	#pragma comment(lib, "dxguid.lib")
	#pragma comment(lib, "winmm.lib")

	#include <wtypes.h>
	#include <mmsystem.h>
	#include <dsound.h>

	/* Mixer */
	void SoundPlayer::Mixer::Update(IDirectSoundBuffer8* sound)
	{
		this->sound = sound;

		Volume(volume);
		Speed(speed);
		Pan(pan);
	}

	float SoundPlayer::Mixer::Volume(float volume)
	{
		// Returns if sound is nullptr
		if (!sound) 
			return this->volume;
		
		const float maxVolume = -(float)DSBVOLUME_MIN; // Not a bug.

		if (volume < 1)
			volume = 1;
		else if (volume > maxVolume)
			volume = maxVolume;

		sound->SetVolume(-LONG(maxVolume / volume));

		this->volume = volume;
		return volume;
	}
	float SoundPlayer::Mixer::Volume()
	{
		return volume;
	}
	float SoundPlayer::Mixer::Speed(float speed)
	{
		// Returns if sound is nullptr
		if (!sound) 
			return this->speed;

		if (speed < 0.002f)
			speed = 0.002f;
		else if (speed > 4.545f)
			speed = 4.545f;

		sound->SetFrequency(DWORD(44000.0f * speed));

		this->speed = speed;
		return speed;
	}
	float SoundPlayer::Mixer::Speed()
	{
		return speed;
	}
	float SoundPlayer::Mixer::Pan(float pan)
	{
		// Returns if sound is nullptr
		if (!sound) 
			return this->pan;

		const float maxPan = (float)DSBPAN_RIGHT;

		if (pan < -maxPan)
			pan = -maxPan;
		else if (pan > maxPan)
			pan = maxPan;

		sound->SetPan(LONG(pan * maxPan));
		this->pan = pan;
		return pan;
	}
	float SoundPlayer::Mixer::Pan()
	{
		return pan;
	}

	/* SoundPlayer  */
	SoundPlayer::SoundPlayer()
	{
		waveFormat = new WAVEFORMATEX;
		bufferDesc = new DSBUFFERDESC;
	}
	SoundPlayer::SoundPlayer(SoundData* soundData)
		: SoundPlayer()
	{
		Change(soundData);
	}
	SoundPlayer::SoundPlayer(Format* format)
		: SoundPlayer()
	{
		Change(format);
	}
	SoundPlayer::SoundPlayer(const char* path)
		: SoundPlayer()
	{
		Load(path);
	}
	SoundPlayer::~SoundPlayer()
	{
		ClearMemory();
		delete waveFormat;
		delete bufferDesc;
	}

	void SoundPlayer::ClearMemory()
	{
		Stop();

		if (sound)
		{
			sound->Release();
			sound = nullptr;
		}

		if (directSound)
		{
			directSound->Release();
			directSound = nullptr;
		}
	}
	bool SoundPlayer::CheckError()
	{
		if ((!soundData) || (!sound))
			return false;
		return true;
	}

	void SoundPlayer::Change(SoundData* soundData)
	{
		this->soundData = soundData;

		ClearMemory();

		waveFormat->wFormatTag = (WORD)soundData->GetSoundQuality()->GetType();
		waveFormat->nSamplesPerSec = soundData->GetSoundQuality()->GetSampleRate();
		waveFormat->wBitsPerSample = soundData->GetSoundQuality()->GetBitsPerSample();
		waveFormat->nChannels = soundData->GetSoundQuality()->GetChannels();
		waveFormat->nBlockAlign = (waveFormat->wBitsPerSample / 8) * waveFormat->nChannels;
		waveFormat->nAvgBytesPerSec = waveFormat->nSamplesPerSec * waveFormat->nBlockAlign;
		waveFormat->cbSize = 0;

		bufferDesc->dwSize = sizeof(DSBUFFERDESC);
		bufferDesc->dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
		bufferDesc->dwBufferBytes = (DWORD)soundData->GetSize();
		bufferDesc->dwReserved = 0;
		bufferDesc->lpwfxFormat = waveFormat;
		bufferDesc->guid3DAlgorithm = GUID_NULL;

		DirectSoundCreate8(NULL, &directSound, NULL);
		directSound->SetCooperativeLevel(GetConsoleWindow(), DSSCL_PRIORITY);
		directSound->CreateSoundBuffer(bufferDesc, &tempBuffer, NULL);

		tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&sound);
		tempBuffer->Release();
		tempBuffer = nullptr;

		long long int bufferSize = 0;
		unsigned char* bufferPtr;

		sound->Lock(0, soundData->GetSize(), (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, NULL, 0);
		memcpy(bufferPtr, soundData->GetBuffer(), soundData->GetSize());
		sound->Unlock((void*)soundData->GetBuffer(), (DWORD)soundData->GetSize(), NULL, 0);
		
		Mixer.Update(sound);
	}
	void SoundPlayer::Change(Format* format)
	{
		Change(format->GetSound());
	}
	void SoundPlayer::Load(const char* path)
	{
		Format* format = FormatAny::Import(path);
		Change(format);
		delete format;
	}

	void SoundPlayer::Play()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		if (states == SoundStates::Stopped)
		{
			sound->Play(0, 0, 0);
			states = SoundStates::Active;
		}
	}
	void SoundPlayer::Replay()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		sound->SetCurrentPosition(0);
		states = SoundStates::Active;
	}
	void SoundPlayer::Loop()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		if (states == SoundStates::Stopped)
		{
			sound->Play(0, 0, DSBPLAY_LOOPING);
			states = SoundStates::Active;
		}
	}
	void SoundPlayer::Pause()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		if (states == SoundStates::Active)
		{
			sound->Stop();
			states = SoundStates::Paused;
		}
	}
	void SoundPlayer::Resume()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		if (states == SoundStates::Paused)
		{
			sound->Play(0, 0, 0);
			states = SoundStates::Active;
		}
	}
	void SoundPlayer::Stop()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		sound->Stop();
		states = SoundStates::Stopped;
	}

	void SoundPlayer::SetPosition(float second)
	{
		// Returns if there is errors
		if (!CheckError()) 
			return;

		sound->SetCurrentPosition((DWORD)(second * (float)soundData->GetSoundQuality()->GetSampleRate()));
	}

	float SoundPlayer::GetPosition()
	{
		// Returns if there is errors
		if (!CheckError()) 
			return 0.0f;

		DWORD position = 0;
		sound->GetCurrentPosition(&position, NULL);
		return (float)position / (float)soundData->GetSoundQuality()->GetSampleRate();
	}
	float SoundPlayer::GetLength()
	{
		// Returns if there is errors
		if (!CheckError())
			return 0.0f;

		return 0.0f;
	}
	SoundStates SoundPlayer::GetSoundStates()
	{
		// Returns if there is errors
		if (!CheckError())
			return SoundStates::Uninitialized;

		DWORD status;
		sound->GetStatus(&status);

		return states;
	}
}}
