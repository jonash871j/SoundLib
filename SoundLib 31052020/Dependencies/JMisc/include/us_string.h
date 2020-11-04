#pragma once
#include "us_def.h"

namespace us
{
	class JM_DLL_OUT String
	{
	private:
		enum class HeapState
		{
			None,
			AConst,
			WConst,
			Heap,
		};

	private:
		uint64_t length = 0;
		HeapState heapState = HeapState::None;
		const char* acString = nullptr;
		char* aString = nullptr;
	#ifdef UNICODE
		const wchar_t* wcString = nullptr;
		wchar_t* wString = nullptr;
	#endif

	public:
		String();
		String(const char* acString);
	#ifdef UNICODE
		String(const wchar_t* wcString);
	#endif
		~String();

	private: 
		void CreateHeap();
		bool Compare(String& compare);
		String Add(String add);

	public:
		String& operator=(const String& v) = default;

	public:
		bool operator==(String& compare);
		bool operator==(const char* compare); 
	#ifdef UNICODE 
		bool operator==(const wchar_t* compare); 
	#endif

	public:
		String operator+(String add);
		String operator+(const char* add);

	public:
		char operator[](int32_t index);

	public:
		bool GetIsNullOrEmpty();
		uint64_t GetLength();
		const char* GetStrA();
	#ifdef UNICODE
		const wchar_t* GetStrW();
		const wchar_t* GetStr();
	#elif
		const char* GetStr();
	#endif
	};
}

JM_DLL_OUT us::String operator+(const char* string, us::String& add);
