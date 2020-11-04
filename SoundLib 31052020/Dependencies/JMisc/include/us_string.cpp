#include "us_string.h"
#include <string.h>

namespace us
{
	
	String::String()
	{
	}
	String::String(const char* acString)
	{
		this->length = strlen(acString);
		this->acString = acString;
		heapState = HeapState::AConst;
	}
#ifdef UNICODE
	String::String(const wchar_t* wcString)
	{
		this->length = wcslen(wcString);
		this->wcString = wcString;
		heapState = HeapState::WConst;
	}
#endif
	String::~String()
	{
	//	JM_DELETE(aString);
	//#ifdef UNICODE
	//	JM_DELETE(wString);
	//#endif
	}

	void String::CreateHeap()
	{
		if (heapState == HeapState::AConst)
		{
			JM_CREATE(aString) = new char[length + 1];
			#ifdef UNICODE
			JM_CREATE(wString) = new wchar_t[length + 1];

			for (uint64_t i = 0; i < length; i++)
			{
				aString[i] = acString[i];
				wString[i] = (wchar_t)acString[i];
			}
			wString[length] = 0;
			aString[length] = 0;
		#elif
			for (int32_t i = 0; i < length; i++)
			{
				aString[i] = acString[i];
			}
			aString[length] = 0;
		#endif
		}
	#ifdef UNICODE
		else if (heapState == HeapState::WConst)
		{
			JM_CREATE(wString) = new wchar_t[length + 1];
			JM_CREATE(aString) = new char[length + 1];
			
			for (uint64_t i = 0; i < length; i++)
			{
				wString[i] = wcString[i];
				aString[i] = (char)wcString[i];
			}
			wString[length] = 0;
			aString[length] = 0;
		}
	#endif

		heapState = HeapState::Heap;
	}

	// Used to compare string to another string
	bool String::Compare(String& compare)
	{
		if (compare.length != length)
			return false;

		if (heapState != HeapState::Heap)
			CreateHeap();

		const char* compareArray = compare.GetStrA();

		for (uint64_t i = 0; i < length; i++)
			if (aString[i] != compareArray[i])
				return false;

		return true;
	}

	String String::Add(String add)
	{
		const char* firstString = GetStrA();
		const char* secondString = add.GetStrA();

		uint64_t newLength = length + add.length;
		char* newAString = new char[newLength + 1];

		// Null terminater
		newAString[newLength] = 0;

		for (uint64_t i = 0; i < newLength; i++)
			if (i < length)
				newAString[i] = firstString[i];
			else
				newAString[i] = secondString[i - length];


		return String(newAString);
	}

	// Used to compare string to another string
	bool String::operator==(const char* compare)
	{
		String str = compare;
		return Compare(str);
	}
	// Used to compare string to another string
	bool String::operator==(String& compare)
	{
		return Compare(compare);
	}
	// Used to compare string to another string
	bool String::operator==(const wchar_t* compare)
	{
		String str = compare;
		return Compare(str);
	}

	String String::operator+(String add)
	{
		return Add(add);
	}

	String String::operator+(const char* add)
	{
		return Add(add);
	}



	char String::operator[](int32_t index)
	{
		if (index > length)
			return '\0';

		return GetStrA()[index];
	}

	bool String::GetIsNullOrEmpty()
	{
		if ((heapState == HeapState::None) || (length == 0))
			return true;
		return false;
	}

	// Used to get length of string
	uint64_t String::GetLength()
	{
		return length;
	}

	// Used to get ascii string array
	const char* String::GetStrA()
	{
		if (heapState == HeapState::AConst)
			return acString;
		else
		{
			if (heapState != HeapState::Heap)
				CreateHeap();
			return aString;
		}
	}
	#ifdef UNICODE
	// Used to get unicode string array
	const wchar_t* String::GetStrW()
	{
		if (heapState == HeapState::WConst)
			return wcString;
		else
		{
			if (heapState != HeapState::Heap)
				CreateHeap();
			return wString;
		}
	} 
	// Used to get unicode string array #define UNICODE
	// If not defined returns ascii string array
	const wchar_t* String::GetStr()
	{
		return GetStrW();
	}
#elif
	const char* String::GetStr()
	{
		return GetAStr();
	}
#endif
}

us::String operator+(const char* string, us::String& add)
{
	return us::String(string) + add;
}
