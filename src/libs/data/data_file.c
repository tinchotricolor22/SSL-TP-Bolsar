#include "data.h"
#include "config.h"

DataResult _get_data_with_fs_method(DataOutput **p_data_output) {
    data_debug_logger("Opening file in filesystem path: %s [event:_get_data_with_fs_method]", g_config.fs_data_path);
    FILE *file = fopen(g_config.fs_data_path, "r");

    if (file == NULL) {
        data_debug_logger("ERROR: Cannot open file in path: %s [event:_get_data_with_fs_method]", g_config.fs_data_path);
        return DATA_RESULT_ERROR;
    }

    *p_data_output = create_data_output(file);
    return DATA_RESULT_OK;
}