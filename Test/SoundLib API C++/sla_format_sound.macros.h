#pragma once
#include "sla_format_sound.h"

#define READ_DWORD(format_type)			sla_format_sound_read_dword(format_type->format_sound)
#define READ_WORD(format_type)			sla_format_sound_read_word(format_type->format_sound)
#define READ_BYTE(format_type)			sla_format_sound_read_byte(format_type->format_sound)
#define READ_SKIP(format_type, amount)	sla_format_sound_read_skip(format_type->format_sound, amount)