#pragma once
#define SLA_DLL_OUT /*__declspec(dllexport)*/

// General datatypes
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;

typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef const wchar_t* cwstring;
typedef const char* cstring;

// API structs
typedef struct sla_format_sound_t sla_format_sound_t;
typedef struct sla_format_wav_t sla_format_wav_t;

typedef struct sla_sound_type_t sla_sound_type_t;
typedef struct sla_sound_data_t sla_sound_data_t;

// API enums
typedef enum sla_wave_type_t sla_wave_type_t;
typedef enum sla_result_t sla_task_state_t;

// Externs structs
typedef struct sla_extern_thread_t sla_extern_thread_t;
typedef struct sla_extern_basic_if_stream_t sla_extern_basic_if_stream_t;