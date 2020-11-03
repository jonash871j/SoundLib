#pragma once
#include "sl_def.h"
#include "sl_format.h"
#include "sl_sound_devices.h"
#include "sl_sound.h"

namespace SoundLib
{
	class DSoundPlayer
	{
	private:
		struct tWAVEFORMATEX* waveFormat = nullptr;
		struct _DSBUFFERDESC* bufferDesc = nullptr;
		struct IDirectSound8* directSound = nullptr;
		struct IDirectSoundBuffer* tempBuffer = nullptr;
		struct IDirectSoundBuffer8* soundBuffer = nullptr;

	private:
		Sound* sound = nullptr;

	private:
		enum class States
		{
			Active,
			Paused,
			Stopped,
		}states = States::Stopped;

	public:
		DSoundPlayer();
		~DSoundPlayer();

	public:
		void Change(Sound* sound);
		void Change(Format* format);
		void Load(const char* path);

	public:
		void Play();
		void Replay();
		void Loop(LoopFlags flags, uint32_t amount = 1);
		void Pause();
		void Resume();
		void Stop();

	public:
		// Range between 0.002x - 4.545x
		void SetSpeed(float speed);

		// Range between 0.0 - 100
		void SetVolume(float volume);

		// Range between -1.00L - 1.00R
		void SetPan(float pan);

	/*public:
		DSoundPlayer(SoundDevice* soundDevice = nullptr);
		DSoundPlayer(Sound* sound, SoundDevice* soundDevice = nullptr);
		DSoundPlayer(Format* format, SoundDevice* soundDevice = nullptr);
		DSoundPlayer(const char* path, SoundDevice* soundDevice = nullptr);
		~DSoundPlayer();


	public:
		void Play();
		void Loop(LoopFlags flags, uint32_t amount = 1);
		void Replay();
		void Pause();
		void Resume();
		void Stop();

	public:
		void SetFrequency(float frequency);
		void SetVolume(float volume);
		void SetPan(float pan);

	public:
		void SetSoundDevice(SoundDevice* soundDevice);*/
	};


}
