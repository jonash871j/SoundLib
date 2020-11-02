#include "sla_format_sound.h"
#include "sla_sound_data.h"
#include "sla_extern_basic_if_stream.h"

// Used to initialize format_sound_t
sla_result_t sla_format_sound_init_default(
    sla_format_sound_t* format_sound
)
{
    // Chceks if type is nullptr
    if (!format_sound)
        return SLA_R_ERR_FORMAT_SOUND_INVALID;

    // Fills out format_sound_t struct
    format_sound->in_file       = new sla_extern_basic_if_stream_t();
    format_sound->sound_data    = new sla_sound_data_t();
    format_sound->sound_type    = new sla_sound_type_t();
    format_sound->path          = L"null";
    format_sound->size          = 0;

    // Sets heap values
    sla_sound_data_init_default(format_sound->sound_data);
    sla_sound_type_init_default(format_sound->sound_type);

    return SLA_R_OK;
}

// Used to open sound file
sla_result_t sla_format_sound_open(
    sla_format_sound_t* format_sound, 
    cwstring path
)
{
    format_sound->path = path;

    // Sets file mode and opens file
    format_sound->in_file->type = std::basic_ifstream<uint8>(path, std::ifstream::binary);

    // Checks if file could't be opened
    if (format_sound->in_file->type.fail())
        return SLA_R_TS_ERR_FAILED_TO_LOAD_SOUND_FILE;

    return sla_result_t();
}

// Used to read byte from sound file
uint8 sla_format_sound_read_byte(
    sla_format_sound_t* format_sound
)
{
    uint8 byte = 0;
    format_sound->in_file->type.read(&byte, 1);
    return byte;
}

// Used to read word from sound file
uint16 sla_format_sound_read_word(
    sla_format_sound_t* format_sound
)
{
    uint8 bytes[2];
    format_sound->in_file->type.read(bytes, 2);
    return (bytes[1] << 8) | (bytes[0]);
}


// Used to read dword from sound file
uint32 sla_format_sound_read_dword(
    sla_format_sound_t* format_sound
)
{
    uint8 bytes[4];
    format_sound->in_file->type.read(bytes, 4);
    return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | (bytes[0]);
}

// Used to skip x amount of data from sound file
void sla_format_sound_read_skip(
    sla_format_sound_t* format_sound, 
    uint32 amount
)
{
    for (uint32 i = 0; i < amount; i++)
        sla_format_sound_read_byte(format_sound);
}

// Used to free memory for format_sound_t 
sla_result_t sla_format_sound_destroy(sla_format_sound_t* format_sound)
{
    // Checks for nullptr
    if (format_sound)
    {
        // Frees memory for the struct attributes
        sla_sound_data_destroy(format_sound->sound_data);
        sla_sound_type_destroy(format_sound->sound_type);

        delete format_sound;
        return SLA_R_OK;
    }
    else
    {
        return SLA_R_ERR_FORMAT_SOUND_INVALID;
    }
}
