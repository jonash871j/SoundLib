#include "sfh_def.h"
#include <vcruntime_exception.h>

#define SP(string) throw std::exception(string)
#define SX(string) throw std::exception(us::String(string).GetStrA())
#define P(parameter) (us::String&)(parameter.GetIsNullOrEmpty() == true ? #parameter : parameter)

namespace sfh
{
	void ThrowError(ErrorCode errorCode, us::String parameter1, us::String parameter2)
	{
		typedef enum ErrorCode EC;
	
		switch (errorCode)
		{
		case EC::InvalidPath	: SX("Invalid path, couldn't open: " + P(parameter1));
		case EC::FileAlreadyOpen: SX(P(parameter1) + " is still open, couldn't open: " + P(parameter2));
		default					: SP("Invalid error code");
		}
	}
}