#include "data.h"
#include "config.h"

DataResult _get_data_with_online_method(DataOutput **) {
    dataDebugLogger("Executing command %s [event:_get_data_with_online_method]", g_config.wget_cmd);
    FILE *file = popen(g_config.wget_cmd, "r");

    if (file == NULL) {
        dataDebugLogger("ERROR: Command error [event:_get_data_with_online_method]", FSPath);
        return DATA_RESULT_ERROR;
    }

    *dataOutput = create_data_output(file);
    return DATA_RESULT_OK;
}