#pragma once
#include "sl_def.h"
#include "sl_format.h"
#include "sl_sound_devices.h"
#include "sl_sound_data.h"

namespace SoundLib{
namespace MMSystem {
	class SL_DLL_OUT SoundPlayer
	{
	private:
		bool isLoadedFromSoundPlayer = false;
		bool isPlaying = false;
		bool isSoundWaiting = false;

	private:
		uint32_t id;
		int32_t loopAmount;

	private:
		SoundDevices* soundDevices = nullptr;
		SoundDevice* soundDevice = nullptr;
		SoundData* sound = nullptr;
		Format* format = nullptr;

	private:
		Extern::E_Thread* soundThread = nullptr;
		Extern::E_WAVEHDR* waveHeader = nullptr;
		Extern::E_HWAVEOUT* waveOut = nullptr;
		Extern::E_WAVEFORMATEX* waveFormat = nullptr;

	public:
		SoundPlayer(SoundDevice* soundDevice = nullptr);

		// Used to change sound for preloaded sound
		SoundPlayer(SoundData* sound, SoundDevice* soundDevice = nullptr);

		// Used to change sound for preloaded sound
		SoundPlayer(Format* format, SoundDevice* soundDevice = nullptr);

		// Used to load any sound file from a path
		SoundPlayer(const char* path, SoundDevice* soundDevice = nullptr);

		~SoundPlayer();

	public:
		// Used to change sound for preloaded sound
		void Change(SoundData* sound);
		
		// Used to change sound for preloaded sound
		void Change(Format* format);

		// Used to load any sound file from a path
		void Load(const char* path);

	public:
		// Used to play sound 
		void Play();

		// Used to loop sound
		void Loop(LoopFlags flags, uint32_t amount = 1);

		// Used to replay sound from the beginning
		void Replay();

		// Used to pause the playing sound
		void Pause();

		// Used to resume paused sound
		void Resume();

		// Used to stop the sound completely
		void Stop();

	public:
		// Used to set the playback rate, works from 0.5x to 2.0x
		void Speed(float speed);

	public:
		// Used to change output sound device
		void SetSoundDevice(SoundDevice* soundDevice);

		// Used to set position index in sound
		void SetPositionIndex(uint32_t index);

		// Used to set position in seconds, in sound
		void SetPosition(uint32_t position);

	public:		
		// Used to get the sound active state
		bool GetSoundActive();

		// Used to get current loop index, -1 means endless
		int32_t GetLoopIndex();

		// Used to get the amount of loops left, -1 means endless
		int32_t GetLoopAmount();
		
		// Used to get current position index in sound
		uint32_t GetPositionIndex();

		// Used to get current position in seconds, in sound
		uint32_t GetPosition();

		// Used to get time amount of sound
		uint32_t GetTimeAmount();

	private:
		// Used to play sound
		void PlayInternal();

		// Used to stop sound
		void StopInternal();

	private:
		// Used alocates new memory for waveHeaders and filling out the structure
		void CreateWaveHeaders();

		// Used alocates new memory for waveOut and filling out the structure
		void CreateWaveOut();

		// Used alocates new memory for waveFormat, filling out the structure and open sound device for playback
		void CreateWaveFormat();

	private:
		// Used to set default sound device
		void SetDefaultSoundDevice();

	private:
		// Used to delete sound data: waveHeader, waveOut & waveFormat
		void DeleteSoundData();

	private:
		// Used to send sound data to soundcard
		static void SendToSoundCard(const uint32_t id);
	};
}}