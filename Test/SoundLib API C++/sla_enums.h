#pragma once

enum sla_wave_type_t
{
	SLA_WT_INVALID = 0,
	SLA_WT_PCM = 1,
	SLA_WT_W1M08 = 0x00000001,
	SLA_WT_W1S08 = 0x00000002,
	SLA_WT_W1M16 = 0x00000004,
	SLA_WT_W1S16 = 0x00000008,
	SLA_WT_W2M08 = 0x00000010,
	SLA_WT_W2S08 = 0x00000020,
	SLA_WT_W2M16 = 0x00000040,
	SLA_WT_W2S16 = 0x00000080,
	SLA_WT_W4M08 = 0x00000100,
	SLA_WT_W4S08 = 0x00000200,
	SLA_WT_W4M16 = 0x00000400,
	SLA_WT_W4S16 = 0x00000800,
	SLA_WT_W44M08 = 0x00000100,
	SLA_WT_W44S08 = 0x00000200,
	SLA_WT_W44M16 = 0x00000400,
	SLA_WT_W44S16 = 0x00000800,
	SLA_WT_W48M08 = 0x00001000,
	SLA_WT_W48S08 = 0x00002000,
	SLA_WT_W48M16 = 0x00004000,
	SLA_WT_W48S16 = 0x00008000,
	SLA_WT_W96M08 = 0x00010000,
	SLA_WT_W96S08 = 0x00020000,
	SLA_WT_W96M16 = 0x00040000,
	SLA_WT_W96S16 = 0x00080000,
};

enum sla_result_t
{
	SLA_R_OK,
	SLA_R_EER_UNKNOWN,
	SLA_R_TS_ERR_FAILED_TO_LOAD_SOUND_FILE,
	SLA_R_ERR_INVALID_SOUND_FILE,
	SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER,
	SLA_R_ERR_NULL_PTR,
	SLA_R_ERR_FORMAT_SOUND_INVALID,
	SLA_R_ERR_SOUND_TYPE_INVALID,
	SLA_R_ERR_SOUND_DATA_INVALID,
};
