#include "sfh_write_file.h"

namespace sfh
{
	WriteFile::WriteFile()
		: File()
	{
	}
	WriteFile::WriteFile(const char* path)
		: File()
	{
		File::Open(path);
	}
	void WriteFile::WriteBuffer(char* buffer, size_t size)
	{
		outFile.write(buffer, size);
	}
	void WriteFile::Open()
	{
		outFile = std::ofstream(path.GetStrA(), std::ios::out | std::ios::binary);

		if (outFile.fail())
			ThrowError(ErrorCode::InvalidPath, path);

		isFileOpen = true;
	}
	void WriteFile::Close()
	{
		outFile.close();
		isFileOpen = false;
	}
	std::ofstream& WriteFile::GetOutFileStream()
	{
		return outFile;
	}
}