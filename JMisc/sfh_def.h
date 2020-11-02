#pragma once
#include "us_def.h"
#include "us_string.h"

namespace sfh
{
	typedef class File File;
	typedef class ReadFile ReadFile;
	typedef class WriteFile WriteFile;

	enum class JM_DLL_OUT ErrorCode
	{
		InvalidPath,
		FileAlreadyOpen,
	};

	void ThrowError(ErrorCode errorCode, us::String parameter1 = "", us::String parameter2 = "");
}