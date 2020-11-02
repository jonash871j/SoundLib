#pragma once
#include "sfh_def.h"

namespace sfh
{
	class File abstract
	{
	protected:
		us::String path;
		us::String fileExtension;
		bool isFileOpen = false;

	public:
		File();

	protected:
		virtual void Open() = 0;

	public:
		virtual void Open(const char* path);
		virtual void Close() = 0;

	public:
		const char* GetPath();
		us::String GetFileExtension();
		bool GetIsFileOpen();
	};
}