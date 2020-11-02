#pragma once
#include "sl_def.h"
#include "sl_sound.h"
#include "sfh_def.h"

namespace SoundLib
{
	class SL_DLL_OUT Format abstract
	{
	protected:
		sfh::ReadFile* inFile = nullptr;
		Sound sound;

	public:
		~Format();

	public:
		// Used to import sound file from path
		virtual void Import(const char* path);

	protected:
		virtual void ImportHeader() = 0;
		virtual void ImportBlocks() = 0;

	public:
		// Used to get sound
		Sound* GetSound();

		// Used to get sound file path
		const char* GetPath();
	};
}

