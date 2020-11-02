#pragma once
#include "sla_def.h"
#include "sla_sound_data.h"
#include "sla_sound_type.h"

typedef struct SLA_DLL_OUT sla_format_sound_t
{
	sla_extern_basic_if_stream_t* in_file;
	sla_sound_data_t* sound_data;
	sla_sound_type_t* sound_type;
	uint32 size;
	cwstring path;
}sla_format_sound_t;

// Used to initialize format_sound_t
sla_result_t sla_format_sound_init_default(
	sla_format_sound_t* format_sound
);

// Used to open sound file
sla_result_t sla_format_sound_open(
	sla_format_sound_t* format_sound,
	cwstring path
);

// Used to read byte from sound file
uint8 sla_format_sound_read_byte(
	sla_format_sound_t* format_sound
);

// Used to read word from sound file
uint16 sla_format_sound_read_word(
	sla_format_sound_t* format_sound
);

// Used to read dword from sound file
uint32 sla_format_sound_read_dword(
	sla_format_sound_t* format_sound
);

// Used to skip x amount of data from sound file
void sla_format_sound_read_skip(
	sla_format_sound_t* format_sound,
	uint32 amount
);

// Used to free memory for format_sound_t 
sla_result_t sla_format_sound_destroy(
	sla_format_sound_t* format_sound
);