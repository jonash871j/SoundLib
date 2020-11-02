#pragma once
#include "sla_def.h"
#include "sla_sound_type.h"

typedef struct SLA_DLL_OUT sla_sound_data_t
{
	sla_sound_type_t* sound_type;
	uint8* buffer;
	uint32 size;
}sla_sound_data_t;


// Used to initialize and setting default values for sound_data_t 
sla_result_t sla_sound_data_init_default(
	sla_sound_data_t* sound_data
);

// Used to initialize sound_data_t
sla_result_t sla_sound_data_init(
	sla_sound_data_t* sound_data,
	sla_sound_type_t* sound_type,
	uint8* buffer,
	uint32 size
);

// Used to set value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value(
	sla_sound_data_t* sound_data,
	uint32 index, 
	float value
);

// Used to set 8-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_8bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int8 value
);

// Used to set 16-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_16bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int16 value
);

// Used to set 24-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_24bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int32 value
);

// Used to set 32-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_32bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int32 value
);

// Used to get value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_get_value(
	sla_sound_data_t* sound_data,
	uint32 index,
	float* value
);

// Used to get 8-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_get_value_8bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int8* value
);

// Used to get 16-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_get_value_16bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int16* value
);

// Used to get 24-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_get_value_24bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int32* value
);
 
// Used to get 32-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_get_value_32bit(
	sla_sound_data_t* sound_data,
	uint32 index,
	int32* value
);

// Used to free memory for sound_data_t 
sla_result_t SLA_DLL_OUT sla_sound_data_destroy(
	sla_sound_data_t* sound_data
);