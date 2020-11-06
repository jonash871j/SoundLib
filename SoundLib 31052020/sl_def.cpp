#include "sl_def.h"
#include <vcruntime_exception.h>

#define SP(string) throw std::exception(string)
#define SX(string) throw std::exception(us::String(string).GetStrA())
#define P(parameter) (us::String&)(parameter.GetIsNullOrEmpty() == true ? #parameter : parameter)

namespace SoundLib
{

	void ThrowError(ErrorCode errorCode, us::String parameter1, us::String parameter2)
	{
		typedef enum ErrorCode EC;

		switch (errorCode)
		{
		case EC::CorruptedFile				: SX("Sound file corrupted, couldn't read: " + P(parameter1));
		case EC::InvalidExtension			: SX("Invalid file extension on " + P(parameter1) + ", expects " + P(parameter2) + " file");
		case EC::UnsupportedConfiguration	: SX("Unsupported configuration on " + P(parameter1) + ", does not support " + P(parameter2));
		default								: SP("Invalid error code");
		}
	}
}
