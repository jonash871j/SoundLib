#include "sla_sound_type.h"
#include "sla_enums.h"

// Used to initialize and setting default values for sound_type_t 
sla_result_t SLA_DLL_OUT sla_sound_type_init_default(
    sla_sound_type_t* sound_type
)
{
    return sla_sound_type_init(sound_type, SLA_WT_PCM, 16, 44100, 2);
}

// Used to initialize sound_type_t
sla_result_t SLA_DLL_OUT sla_sound_type_init(
    sla_sound_type_t* sound_type,
    sla_wave_type_t wave_type,
    uint16 bits_per_sample,
    uint32 sample_rate,
    uint16 channels
)
{
    // Chceks if type is nullptr
    if (!sound_type)
        return SLA_R_ERR_SOUND_TYPE_INVALID;

    // Fills out sound type struct
    sound_type->wave_type           = wave_type;
    sound_type->bits_per_sample     = bits_per_sample;
    sound_type->sample_rate         = sample_rate;
    sound_type->channels            = channels;

    return SLA_R_OK;
}

// Used to get bytes per sample
uint8 SLA_DLL_OUT sla_sound_type_get_bytes_per_sample(sla_sound_type_t* sound_type)
{
    if (!sound_type)
        return 0;

    return sound_type->bits_per_sample / 8;
}

// Used to get block size
uint32 SLA_DLL_OUT sla_sound_type_get_block_size(sla_sound_type_t* sound_type)
{
    if (!sound_type)
        return 0;

    return sla_sound_type_get_bytes_per_sample(sound_type) * sound_type->channels;
}

// Used to free memory for sound_type_t 
sla_result_t SLA_DLL_OUT sla_sound_type_destroy(
    sla_sound_type_t* sound_type
)
{
    // Checks for nullptr
    if (sound_type)
    {
        delete sound_type;
        return SLA_R_OK;
    }
    else
    {
        return SLA_R_ERR_SOUND_TYPE_INVALID;
    }
}
