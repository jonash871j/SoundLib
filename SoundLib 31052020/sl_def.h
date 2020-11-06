/* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
/* |	SoundLib - v31/05/2020	 OO	   OO	 OO    OO    OO	 | */
/* |							O  O  O	 O  O  O  O  O  O  O | */
/* |	By Jonas				    OO	  OO	OO	  OO	 | */
/* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */

#pragma once
#include <stdint.h>
#include "sfh_def.h"
#include "us_string.h"

#define SL_DLL_OUT /*__declspec(dllexport)*/
#define SL_DELETE(object) if (object != nullptr) delete object
#define SL_CREATE(object) SL_DELETE(object); object 


namespace SoundLib
{
	namespace Extern
	{
		typedef struct E_Thread E_Thread;
		typedef struct E_WAVEFORMATEX E_WAVEFORMATEX;
		typedef struct E_WAVEHDR E_WAVEHDR;
		typedef struct E_HWAVEOUT E_HWAVEOUT;
	}

	namespace TypePtr
	{
		typedef class Format Format;
		typedef class FormatAny FormatAny;
		typedef class FormatWave FormatWave;
		typedef class FormatRaw FormatRaw;

		typedef class SoundData SoundData;
		typedef class SoundDevices SoundDevices;
		typedef class SoundDevice SoundDevice;
		typedef class SoundMixer SoundMixer;
		typedef class SoundQuality SoundQuality;
	}

	namespace MMSystem
	{
		namespace TypePtr
		{
			typedef class SoundPlayer SoundPlayer;
		}
	}
	namespace DirectSound
	{
		namespace TypePtr
		{
			typedef class SoundPlayer SoundPlayer;
		}
	}

	enum class SL_DLL_OUT WaveType : uint16_t
	{
		Invalid = 0,
		PCM = 0x0001,
		W1M08 = 0x0001,
		W1S08 = 0x0002,
		W1M16 = 0x0004,
		W1S16 = 0x0008,
		W2M08 = 0x0010,
		W2S08 = 0x0020,
		W2M16 = 0x0040,
		W2S16 = 0x0080,
		W4M08 = 0x0100,
		W4S08 = 0x0200,
		W4M16 = 0x0400,
		W4S16 = 0x0800,
		W44M08 = 0x0100,
		W44S08 = 0x0200,
		W44M16 = 0x0400,
		W44S16 = 0x0800,
		W48M08 = 0x1000,
		W48S08 = 0x2000,
		W48M16 = 0x4000,
		W48S16 = 0x8000,
	};

	enum class SL_DLL_OUT LoopFlags
	{
		Normal,
		Endless,
	};

	enum class SL_DLL_OUT SoundStates
	{
		Uninitialized,
		Active,
		Paused,
		Stopped,
	};

	enum class SL_DLL_OUT ErrorCode
	{
		None = 0,
		CorruptedFile,
		InvalidExtension,
		UnsupportedConfiguration,
	};

	void ThrowError(ErrorCode errorCode, us::String parameter1 = "", us::String parameter2 = "");
}      