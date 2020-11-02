#include "sla_format_wav.h"
#include "sla_format_sound.macros.h"

// Used to initialize format_wav_t
sla_result_t SLA_DLL_OUT sla_format_wav_init_default(
	sla_format_wav_t* format_wav
)
{
	// Chceks if type is nullptr
	if (!format_wav)
		return SLA_R_ERR_FORMAT_SOUND_INVALID;

	// Fills out format_wav_t struct
	format_wav->format_sound = new sla_format_sound_t();
	format_wav->format_chunk = 0;
	format_wav->format_data_length = 0;
	format_wav->data_section_size = 0;
	format_wav->size_data_section = 0;

	// Sets heap values
	sla_format_sound_init_default(format_wav->format_sound);

	return SLA_R_OK;
}

// Used to initialize format_wav_t and import wav file
sla_result_t SLA_DLL_OUT sla_format_wav_init_import(
	sla_format_wav_t* format_wav, 
	cwstring path
)
{
	// Intialize format_wav_t default
	sla_result_t result = sla_format_wav_init_default(format_wav);
	
	// Checks for error
	if (result != SLA_R_OK)
		return result;

	// Import wav file and return result 
	return sla_format_wav_import(format_wav, path);
}

sla_result_t SLA_DLL_OUT sla_format_wav_import(
	sla_format_wav_t* format_wav, 
	cwstring path
)
{
	/*****Header*****/
	// Reads file marker "RIFF"
	if (sla_format_sound_read_dword(format_wav->format_sound) != 1179011410)
		return SLA_R_ERR_INVALID_SOUND_FILE;

	// Reads file size
	format_wav->format_sound->size = sla_format_sound_read_dword(format_wav->format_sound);

	// Reads file type header should always be "WAVE"
	if (READ_DWORD(format_wav) != 1163280727)
		return SLA_R_ERR_INVALID_SOUND_FILE;

	// Reads format chunk marker
	format_wav->format_chunk = READ_DWORD(format_wav);

	// Reads length of format data
	format_wav->format_data_length = READ_DWORD(format_wav);

	// Reads type of format
	format_wav->format_sound->sound_type->wave_type = (sla_wave_type_t)READ_WORD(format_wav);

	// Reads number of Channels
	format_wav->format_sound->sound_type->channels = READ_WORD(format_wav);

	// Reads sample rate 44100hz CD quality
	format_wav->format_sound->sound_type->sample_rate = READ_DWORD(format_wav);

	// Skips (Sample Rate * BitsPerSample * Channels) / 8 & (BitsPerSample * Channels)
	READ_SKIP(format_wav, 6);

	// Reads Bits per sample
	format_wav->format_sound->sound_type->bits_per_sample = READ_WORD(format_wav);

	// Skibs file start marker					
	READ_SKIP(format_wav, 4);

	// Reads size of the data section		
	format_wav->size_data_section = READ_DWORD(format_wav);

	/*****BUFFER*****/

	return SLA_R_OK;
}
