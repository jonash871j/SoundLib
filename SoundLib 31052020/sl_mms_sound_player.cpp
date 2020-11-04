#include "sl_mms_sound_player.h"
#include "sl_sound_devices.h"
#include "sl_sound_device.h"
#include "sl_sound_data.h"
#include "sl_format.h"
#include "sl_format_any.h"
#include "sl_misc.h"

#include "sl_e_thread.h"
#include "sl_e_wave_format.h"
#include "sl_e_wave_header.h"
#include "sl_e_wave_out.h"

#include <iostream>
#include <vector>

namespace SoundLib{
namespace MMSystem
{
	using namespace Extern;

#pragma region ThreadSetup
	typedef struct Packet
	{
		uint32_t id;
		bool* isSoundWaiting;
		E_HWAVEOUT* waveOut;
		E_WAVEHDR* waveHeaders;
	}Packet;

	static uint32_t s_id = 0;
	static std::vector<Packet> s_packets;

	static void SetValue(Packet packet)
	{
		for (uint32_t i = 0; i < s_packets.size(); i++)
			if (s_packets[i].id == packet.id)
			{
				s_packets[i] = packet;
				return;
			}
	}
	static Packet GetValue(uint32_t id)
	{
		for (uint32_t i = 0; i < s_packets.size(); i++)
			if (s_packets[i].id == id)
				return s_packets[i];
		
		Packet failed = { 0, nullptr, nullptr, nullptr };
		return failed;
	}
	static void RemoveValue(uint32_t id)
	{
		for (uint32_t i = 0; i < s_packets.size(); i++)
			if (s_packets[i].id == id)
				s_packets.erase(s_packets.begin() + i);
	}
#pragma endregion

	static bool s_isSoundWaiting = false;
	static bool s_isTimingThreadActive = false;

	SoundPlayer::SoundPlayer(SoundDevice* soundDevice)
	{
		// Alocates memory
		soundDevices = new SoundDevices();
		soundThread = new E_Thread();
		
		// Sets output sound device
		SetSoundDevice(soundDevice);

		// Gives this soundplayer a unique id
		id = s_id;
		s_id++;

		// Alocates space in vector, that is used in sound thread 
		s_packets.push_back(Packet{ id, nullptr, nullptr, nullptr });
	}
	SoundPlayer::SoundPlayer(SoundData* sound, SoundDevice* soundDevice)
		: SoundPlayer(soundDevice)
	{
		Change(sound);
	}
	SoundPlayer::SoundPlayer(Format* format, SoundDevice* soundDevice)
		: SoundPlayer(soundDevice)
	{
		Change(format);
	}
	SoundPlayer::SoundPlayer(const char* path, SoundDevice* soundDevice)
		: SoundPlayer(soundDevice)
	{
		Load(path);
	}

	SoundPlayer::~SoundPlayer()
	{
		// Destruct sound thread
		delete soundThread;

		// Destruct sound device
		delete soundDevice;
		delete soundDevices;

		// Delete old sound data
		DeleteSoundData();

		// Destruct format if sound was loaded within the class
		if (format != nullptr)
			delete format;
	}

	void SoundPlayer::Change(SoundData* sound)
	{
		// Delete old sound data
		DeleteSoundData();

		// ??? Not sure if this is still required
		if (isLoadedFromSoundPlayer)
			isLoadedFromSoundPlayer = false;

		// Sets the new sound
		this->sound = sound;

		// Create sound structures
		CreateWaveHeaders();
		CreateWaveOut();
		CreateWaveFormat();

		isPlaying = false;
	}
	void SoundPlayer::Change(Format* format)
	{
		Change(format->GetSound());
	}
	void SoundPlayer::Load(const char* path)
	{ // TODO: Clean this mess up
		Format* oldFormat = nullptr;
		if (format != nullptr)
			oldFormat = format;

		format = FormatAny::Import(path);
		Change(format);

		if (oldFormat != nullptr)
			delete oldFormat;

		isLoadedFromSoundPlayer = true;
	}

	void SoundPlayer::Play()
	{
		loopAmount = 1;
		PlayInternal();
	}
	void SoundPlayer::Loop(LoopFlags flags, uint32_t amount)
	{
		switch (flags)
		{
		case LoopFlags::Normal : loopAmount = amount; break;
		case LoopFlags::Endless: loopAmount = -1; 	  break;
		default:								      return;
		}
		PlayInternal();
	}
	void SoundPlayer::Replay()
	{
		Resume();
		if ((waveOut->wo != nullptr) && (isPlaying))
		{
			isPlaying = false;
			waveOutReset(*waveOut->wo);
		}
		Play();
	}
	void SoundPlayer::Pause()
	{
		if (waveOut->wo != nullptr)
			waveOutPause(*waveOut->wo);
	}
	void SoundPlayer::Resume()
	{
		if (waveOut->wo != nullptr)
			waveOutRestart(*waveOut->wo);
	}
	void SoundPlayer::Stop()
	{
		if (waveHeader)
		{
			SetPositionIndex(0);
			StopInternal();
		}
	}

	void SoundPlayer::Speed(float speed)
	{
		if (waveOut != nullptr)
			waveOutSetPlaybackRate(*waveOut->wo, Misc::FloatToUInt32(speed));
	}

	void SoundPlayer::SetSoundDevice(SoundDevice* soundDevice)
	{
		if (soundDevice == nullptr)
			SetDefaultSoundDevice();
		else
			this->soundDevice = soundDevice;

		if (waveFormat != nullptr)
		{
			Change(sound);
			CreateWaveFormat();
		}
	}
	void SoundPlayer::SetPositionIndex(uint32_t index)
	{
		if (index >= sound->GetSize())
			index = 0;

		StopInternal();

		uint32_t indexOffset = index - (index % sound->GetSoundQuality()->GetBytesPerSample());

		waveHeader->wh->lpData = (LPSTR)(sound->GetBuffer() + indexOffset);
		waveHeader->wh->dwBufferLength = (uint32_t)sound->GetSize() - indexOffset;
	}

	void SoundPlayer::SetDefaultSoundDevice()
	{
		soundDevice = soundDevices->GetDefaultDevice();
	}

	void SoundPlayer::DeleteSoundData()
	{
		if (waveOut != nullptr)
		{
			Stop();
			waveOutUnprepareHeader(*waveOut->wo, waveHeader->wh, sizeof(WAVEHDR));
			waveOutClose(*waveOut->wo);

			delete waveOut;
			delete waveHeader;
			delete waveFormat;
		}
	}

	bool SoundPlayer::GetSoundActive()
	{
		if (loopAmount == -1)
			return true;

		if ((waveOut != nullptr) && (sound != nullptr))
		{

			if (GetPositionIndex() >= sound->GetSize() * loopAmount)
				return false;
		}
		return true;

		/* BUG: Is inconsistent when to many sounds is being played at the same time */
	}

	int32_t SoundPlayer::GetLoopIndex()
	{
		if (loopAmount == -1)
			return -1;
		else
			return GetPositionIndex() / (uint32_t)sound->GetSize();
	}

	int32_t SoundPlayer::GetLoopAmount()
	{
		if (loopAmount == -1)
			return -1;
		else
			return loopAmount - GetLoopIndex();
	}

	uint32_t SoundPlayer::GetPositionIndex()
	{
		MMTIME time;
		waveOutGetPosition(*waveOut->wo, &time, sizeof(MMTIME));
		return time.u.ms;
	}

	uint32_t SoundPlayer::GetPosition()
	{
		return (GetPositionIndex() / waveFormat->wf->nAvgBytesPerSec);
	}

	uint32_t SoundPlayer::GetTimeAmount()
	{
		return (uint32_t)sound->GetSize() / waveFormat->wf->nAvgBytesPerSec;
	}

	void SoundPlayer::PlayInternal()
	{
		waveHeader->wh->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		waveHeader->wh->dwLoops = loopAmount;

		if ((!isPlaying) && (sound != nullptr))
		{
			if (isSoundWaiting)
				return;

			isPlaying = true;

			SetValue(Packet{ id, &isSoundWaiting, waveOut, waveHeader });
			if (soundThread->t.joinable())
				soundThread->t.detach();
			soundThread->t = std::thread(SendToSoundCard, id);
		}
	}

	void SoundPlayer::StopInternal()
	{
		if (waveHeader)
		{
			loopAmount = 0;

			waveHeader->wh->dwBufferLength = 1;
			waveOutReset(*waveOut->wo);
			waveHeader->wh->dwBufferLength = (uint32_t)sound->GetSize();
			isPlaying = false;
		}
	}

	void SoundPlayer::CreateWaveHeaders()
	{
		// Fills out the WAVEHDR structure
		waveHeader = new E_WAVEHDR();
		waveHeader->wh->lpData = (LPSTR)sound->GetBuffer();
		waveHeader->wh->dwBufferLength = (uint32_t)sound->GetSize();
	}
	void SoundPlayer::CreateWaveOut()
	{
		waveOut = new E_HWAVEOUT();
	}
	void SoundPlayer::CreateWaveFormat()
	{
		// Gets sound quality
		SoundQuality* quality = sound->GetSoundQuality();

		// Fills out the WAVEFORMATEX structure
		waveFormat = new E_WAVEFORMATEX();
		waveFormat->wf->wFormatTag = (uint16_t)quality->GetType();
		waveFormat->wf->nChannels = quality->GetChannels();
		waveFormat->wf->nSamplesPerSec = quality->GetSampleRate();
		waveFormat->wf->wBitsPerSample = quality->GetBitsPerSample();
		waveFormat->wf->nBlockAlign =  quality->GetBlockAlign();
		waveFormat->wf->nAvgBytesPerSec = quality->GetByteRate();
		waveFormat->wf->cbSize = 0;

		// Opens the given waveform-audio output device for playback
		if (waveOutOpen(
			waveOut->wo,
			soundDevice->GetDeviceId(),
			waveFormat->wf,
			NULL,
			NULL,
			CALLBACK_WINDOW
		) != S_OK)
			throw std::exception("Failed to open the waveform-audio output device for playback in SoundHandler...");
	}

	void SoundPlayer::SendToSoundCard(const uint32_t id)
	{
		// Get thread data packet
		Packet packet = GetValue(id);

		// If another sound is abount to be send to the soundcard wait
		while (s_isSoundWaiting)
			Sleep(1);

		// Sets state to next sound to wait
		s_isSoundWaiting = true;
		*packet.isSoundWaiting = true;

		// Sends sound data to soundcard
		waveOutPrepareHeader(*packet.waveOut->wo, packet.waveHeaders->wh, sizeof(WAVEHDR));
		waveOutWrite(*packet.waveOut->wo, packet.waveHeaders->wh, sizeof(WAVEHDR));

		// Wait a bit before allowing the next sound to be send, this is to avoid an overload and crash
		Sleep(2);

		// Sets state to allow next sound to be processed
		s_isSoundWaiting = false;
		*packet.isSoundWaiting = false;
	}
}}