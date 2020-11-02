#pragma once
#include <stdint.h>

#define JM_DELETE(object) if (object != nullptr) delete object

#define JM_DELETE_SWAP(object, from)		\
	void* temp_##object = object;			\
	object = from;							\
	delete temp_##object

#define JM_CREATE(object) JM_DELETE(object); object 

#define JM_DLL_OUT /*__declspec(dllexport)*/