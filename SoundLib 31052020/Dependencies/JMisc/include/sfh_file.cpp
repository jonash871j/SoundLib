#include "sfh_file.h"
#include "sfh_file_misc.h"

namespace sfh
{
	File::File()
	{

	}

	void File::Open(const char* path)
	{
		if (isFileOpen)
			ThrowError(ErrorCode::FileAlreadyOpen, this->path, path);

		this->path = path;
		this->fileExtension = FileMisc::GetFileExtension(path);

		Open();
	}

	// Used to get path
	const char* File::GetPath()
	{
		return path.GetStrA();
	}
	// Used to get file extension
	us::String File::GetFileExtension()
	{
		return fileExtension.GetStrA();
	}
	// Used to get file open state
	bool File::GetIsFileOpen()
	{
		return isFileOpen;
	}
}
