#include "sla_sound_data.h"
#include "sla_sound_type.h"
#include "sla_core.h"

// Used to initialize and setting default values for sound_data_t 
sla_result_t sla_sound_data_init_default(sla_sound_data_t* sound_data)
{
    // Creates default values
    uint8 buffer[256]{ 0 };
    sla_sound_type_t sound_type;
    sla_sound_type_init_default(&sound_type);

    return sla_sound_data_init(sound_data, &sound_type, buffer, 256);
}

// Used to initialize sound_type_t
sla_result_t sla_sound_data_init(
    sla_sound_data_t* sound_data, 
    sla_sound_type_t* sound_type, 
    uint8* buffer, 
    uint32 size
)
{
    // Chceks if type is nullptr
    if (!sound_type)
        return SLA_R_ERR_SOUND_TYPE_INVALID;

    // Fills out sound_data_t struct
    sound_data->sound_type  = sound_type;
    sound_data->buffer      = buffer;
    sound_data->size        = size;

    return SLA_R_OK;
}

// Used to set value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    float value
)
{
    switch (sound_data->sound_type->bits_per_sample)
    {
    case 8  : return sla_sound_data_set_value_8bit(sound_data, index, (int8)value);
    case 16 : return sla_sound_data_set_value_16bit(sound_data, index, (int16)value);
    case 24 : return sla_sound_data_set_value_24bit(sound_data, index, (int32)value);
    case 32 : return sla_sound_data_set_value_32bit(sound_data, index, (int32)value);
    default : return SLA_R_ERR_SOUND_DATA_INVALID;
    }
}

// Used to set 8-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_8bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int8 value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Sets new sound buffer value in 8 bits
    sound_data->buffer[index] = value + 128;

    return SLA_R_OK;
}

// Used to set 16-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_16bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int16 value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Sets new sound buffer value in 16 bits
    sound_data->buffer[index + 0] = (value & 0x00FF);
    sound_data->buffer[index + 1] = (value & 0xFF00) >> 8;

    return SLA_R_OK;
}

// Used to set 24-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_24bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int32 value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Sets new sound buffer value in 24 bits
    sound_data->buffer[index + 0] = (value & 0x0000FF);
    sound_data->buffer[index + 1] = (value & 0x00FF00) >> 8;
    sound_data->buffer[index + 2] = (value & 0xFF0000) >> 16;

    return SLA_R_OK;
}

// Used to set 32-bit value in sound buffer array
sla_result_t SLA_DLL_OUT sla_sound_data_set_value_32bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int32 value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Sets new sound buffer value in 32 bits
    sound_data->buffer[index + 0] = (value & 0x000000FF);
    sound_data->buffer[index + 1] = (value & 0x0000FF00) >> 8;
    sound_data->buffer[index + 2] = (value & 0x00FF0000) >> 16;
    sound_data->buffer[index + 4] = (value & 0xFF000000) >> 24;

    return SLA_R_OK;
}

sla_result_t SLA_DLL_OUT sla_sound_data_get_value(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    float* value
)
{
    switch (sound_data->sound_type->bits_per_sample)
    {
    case 8 : return sla_sound_data_get_value_8bit(sound_data, index, (int8*)value);
    case 16: return sla_sound_data_get_value_16bit(sound_data, index, (int16*)value);
    case 24: return sla_sound_data_get_value_24bit(sound_data, index, (int32*)value);
    case 32: return sla_sound_data_get_value_32bit(sound_data, index, (int32*)value);
    default: return SLA_R_ERR_SOUND_DATA_INVALID;
    }
}

sla_result_t SLA_DLL_OUT sla_sound_data_get_value_8bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int8* value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Gets buffer value
    *value = sound_data->buffer[index] - 128;

    return SLA_R_OK;
}

sla_result_t SLA_DLL_OUT sla_sound_data_get_value_16bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int16* value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;
    
    // Converts buffer value to 16 bit value
    *value = (sound_data->buffer[index + 1] << 8) | 
              sound_data->buffer[index + 0];

    return SLA_R_OK;
}

sla_result_t SLA_DLL_OUT sla_sound_data_get_value_24bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int32* value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Converts buffer value to 24 bit value
    *value = ((sound_data->buffer[index + 2] << 16) |
              (sound_data->buffer[index + 1] << 8) |
               sound_data->buffer[index + 0]);

    return SLA_R_OK;
}

sla_result_t SLA_DLL_OUT sla_sound_data_get_value_32bit(
    sla_sound_data_t* sound_data, 
    uint32 index, 
    int32* value
)
{
    // Checks if index is inbound of sound buffer
    if (index >= sound_data->size)
        return SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER;

    // Converts buffer value to 24 bit value
    *value = ((sound_data->buffer[index + 3] << 24) |
              (sound_data->buffer[index + 2] << 16) |
              (sound_data->buffer[index + 1] << 8) |
               sound_data->buffer[index + 0]);

    return SLA_R_OK;
}

// Used to free memory for sound_data_t 
sla_result_t SLA_DLL_OUT sla_sound_data_destroy(sla_sound_data_t* sound_data)
{
    // Checks for nullptr
    if (sound_data)
    {
        delete sound_data;
        return SLA_R_OK;
    }
    else
    {
        return SLA_R_ERR_SOUND_DATA_INVALID;
    }
}
