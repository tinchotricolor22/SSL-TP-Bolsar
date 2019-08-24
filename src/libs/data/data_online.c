#include "data.h"
#include "config.h"

DataResult _get_data_with_online_method(DataOutput **p_data_output) {
    data_debug_logger("Executing command %s [event:_get_data_with_online_method]", g_config.wget_cmd);
    FILE *p_file = popen(g_config.wget_cmd, "r");

    if (p_file == NULL) {
        data_debug_logger("ERROR: Command error %s [event:_get_data_with_online_method]", g_config.wget_cmd);
        return DATA_RESULT_ERROR;
    }

    *p_data_output = create_data_output(p_file);
    return DATA_RESULT_OK;
}