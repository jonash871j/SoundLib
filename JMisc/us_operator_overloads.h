#pragma once
#include <iostream>
#include <string>
#include "us_string.h"

#ifdef _IOSTREAM_
static std::ostream& operator<<(std::ostream& os, us::String& usStr)
{
	return os << usStr.GetStrA();
}
#endif

#ifdef _STRING_
static std::string operator+(std::string& str, us::String& usStr)
{
	return str + usStr.GetStrA();
}
#endif