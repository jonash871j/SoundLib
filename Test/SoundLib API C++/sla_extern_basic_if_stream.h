#pragma once
#include "sla_def.h"
#include <fstream>

typedef struct sla_extern_basic_if_stream_t
{
	std::basic_ifstream<uint8> type;
}sla_extern_basic_if_stream_t;