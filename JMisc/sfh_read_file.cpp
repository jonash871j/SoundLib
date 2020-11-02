#include "sfh_read_file.h"
#include <string>

namespace sfh
{
	ReadFile::ReadFile()
		: File()
	{
	}

	ReadFile::ReadFile(const char* path)
		: File()
	{
		File::Open(path);
	}

	char* ReadFile::ReadBuffer(size_t size)
	{
		char* buffer = new char[size];
		inFile.read(buffer, size);
		return buffer;
	}
	void ReadFile::ReadSkip(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			char byte = 0;
			inFile.read(&byte, 1);
		}
	}
	void ReadFile::Open()
	{
		inFile = std::ifstream(path.GetStrA(), std::ifstream::binary);

		if (inFile.fail())
			ThrowError(ErrorCode::InvalidPath, path);

		isFileOpen = true;
	}
	void ReadFile::Close()
	{
		inFile.close();
		isFileOpen = false;
	}
	std::ifstream& ReadFile::GetInFileStream()
	{
		return inFile;
	}
}