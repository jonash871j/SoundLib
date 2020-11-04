#pragma once
#include "sl_def.h"
#include "sl_format.h"
#include "sl_sound_devices.h"
#include "sl_sound_data.h"

namespace SoundLib{
namespace DirectSound
{
	class SoundPlayer
	{
	private:
		struct tWAVEFORMATEX* waveFormat = nullptr;
		struct _DSBUFFERDESC* bufferDesc = nullptr;
		struct IDirectSound8* directSound = nullptr;
		struct IDirectSoundBuffer* tempBuffer = nullptr;
		struct IDirectSoundBuffer8* sound = nullptr;

	private:
		SoundData* soundData = nullptr;
		SoundStates states = SoundStates::Stopped;

	public:
		struct Mixer
		{
			friend class SoundPlayer;
		private:
			struct IDirectSoundBuffer8* sound = nullptr;

		private:
			float volume = 50.0f;	// Range between 0.0 - 100
			float speed = 1.0f;		// Range between 0.002x - 4.545x
			float pan = 0.0f;		// Range between -1.00L - 1.00R

		private:
			void Update(IDirectSoundBuffer8* sound);

		public:
			float Volume(float volume);
			float Volume();
			float Speed(float speed);
			float Speed();
			float Pan(float pan);
			float Pan();
		}Mixer;

	public:
		SoundPlayer();
		SoundPlayer(SoundData* soundData);
		SoundPlayer(Format* format);
		SoundPlayer(const char* path);
		~SoundPlayer();

	private:
		void ClearMemory();
		bool CheckError();

	public:
		void Change(SoundData* soundData);
		void Change(Format* format);
		void Load(const char* path);

	public:
		void Play();
		void Replay();
		void Loop();
		void Pause();
		void Resume();
		void Stop();

	public:
		void SetPosition(float second);

	public:
		float GetPosition();
		float GetLength();
		SoundStates GetSoundStates();
	};
}}
