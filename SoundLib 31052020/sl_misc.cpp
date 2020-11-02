#include "sl_misc.h"
#include <math.h>

namespace SoundLib
{
	namespace Misc
	{
		uint32_t FloatToUInt32(float value)
		{
			uint32_t whole = (uint32_t)floorf(value);
			uint32_t decimal = uint32_t((value - whole) * 0xF000);
			return (whole << 16) ^ decimal;
		}
		uint16_t FloatToUInt16(float value)
		{
			uint16_t whole = (uint32_t)floorf(value);
			uint16_t decimal = uint16_t((value - whole) * 0xF0);
			return (whole << 8) ^ decimal;
		}
		float UInt16ToFloat(uint32_t value)
		{
			return 0.0f;
		}
	}
}