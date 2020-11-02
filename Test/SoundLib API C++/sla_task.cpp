#include "sla_task.h"

// Used to get task_state message
cstring SLA_DLL_OUT sla_task_get_message(
    sla_result_t task_state
)
{
    switch (task_state)
    {
    case SLA_R_OK                    : return "[OK] No errors was found!";
    case SLA_R_EER_UNKNOWN                     : return "[ERROR] Unknown error!";
    case SLA_R_TS_ERR_FAILED_TO_LOAD_SOUND_FILE   : return "[ERROR] Could't open sound file!";
    case SLA_R_ERR_INVALID_SOUND_FILE          : return "[ERROR] Could't load sound file, because it was invalid!";
    case SLA_R_ERR_OUT_OF_BOUNDS_SOUND_BUFFER  : return "[ERROR] Value is out of bounds in sound buffer!";
    case SLA_R_ERR_NULL_PTR                    : return "[ERROR] Type is nullptr!";
    case SLA_R_ERR_FORMAT_SOUND_INVALID        : return "[ERROR] Type format_sound_t is invalid or nullptr!";
    case SLA_R_ERR_SOUND_TYPE_INVALID          : return "[ERROR] Type sound_type_t is invalid or nullptr!";
    case SLA_R_ERR_SOUND_DATA_INVALID          : return "[ERROR] Type sound_data_t is invalid or nullptr!";
    default                                     : return "[UNKNOWN] Task does not exists!";
    }
}
