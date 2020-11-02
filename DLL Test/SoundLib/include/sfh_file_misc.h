#pragma once
#include "sfh_def.h"
namespace sfh
{
	static class FileMisc
	{
	public:
		static size_t GetFileSize(us::String path);
		static us::String GetFileExtension(us::String path);
	}FileMisc;
}