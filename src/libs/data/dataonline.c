#include "data.h"
#include "config.h"

DataResult _get_data_with_online_method(DataOutput **p_data_output) {
    data_debug_logger("Executing command %s [event:_get_data_with_online_method]", g_config.wget_cmd);
    FILE *file = popen(g_config.wget_cmd, "r");

    if (file == NULL) {
        data_debug_logger("ERROR: Command error %s [event:_get_data_with_online_method]", g_config.wget_cmd);
        return DATA_RESULT_ERROR;
    }

    *p_data_output = create_data_output(file);
    return DATA_RESULT_OK;
}