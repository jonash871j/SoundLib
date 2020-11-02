#include "sfh_file_misc.h"
#include <Windows.h>
#include <string>

#pragma comment(lib, "shlwapi.lib")
#include <Shlwapi.h>

namespace sfh
{
	size_t FileMisc::GetFileSize(us::String path)
	{
		LARGE_INTEGER lSize = { 0 };
		HANDLE hPath = CreateFile(path.GetStr(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		GetFileSizeEx(hPath, &lSize);

		return lSize.QuadPart;
	}
	us::String FileMisc::GetFileExtension(us::String path)
	{
		return us::String(PathFindExtension(path.GetStr()));
	}
}