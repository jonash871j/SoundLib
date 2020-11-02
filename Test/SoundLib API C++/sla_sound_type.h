#pragma once
#include "sla_core.h"

typedef struct SLA_DLL_OUT sla_sound_type_t
{
	sla_wave_type_t wave_type;
	uint16 bits_per_sample;
	uint32 sample_rate;
	uint16 channels;
}sla_sound_type_t;

// Used to initialize and setting default values for sound_type_t 
sla_result_t SLA_DLL_OUT sla_sound_type_init_default(
	sla_sound_type_t* sound_type
);

// Used to initialize and alocate memory for sound_type_t
sla_result_t SLA_DLL_OUT sla_sound_type_init(
	sla_sound_type_t* sound_type,
	sla_wave_type_t wave_type,
	uint16 bits_per_sample,
	uint32 sample_rate,
	uint16 channels
);

// Used to get bytes per sample
uint8 SLA_DLL_OUT sla_sound_type_get_bytes_per_sample(
	sla_sound_type_t* sound_type
);

// Used to get block size
uint32 SLA_DLL_OUT sla_sound_type_get_block_size(
	sla_sound_type_t* sound_type
);

// Used to free memory for sound_type_t 
sla_result_t SLA_DLL_OUT sla_sound_type_destroy(
	sla_sound_type_t* sound_type
);