#pragma once
#include "sla_core.h"

typedef struct SLA_DLL_OUT sla_format_wav_t
{
	sla_format_sound_t* format_sound;
	uint32 format_chunk;
	uint32 format_data_length;
	uint32 data_section_size;
	uint32 size_data_section;
}sla_format_wav_t;

// Used to initialize format_wav_t
sla_result_t SLA_DLL_OUT sla_format_wav_init_default(
	sla_format_wav_t* format_wav
);

// Used to initialize format_wav_t and import wav file
sla_result_t SLA_DLL_OUT sla_format_wav_init_import(
	sla_format_wav_t* format_wav,
	cwstring path
);

// Used to import wav file
sla_result_t SLA_DLL_OUT sla_format_wav_import(
	sla_format_wav_t* format_wav,
	cwstring path
);