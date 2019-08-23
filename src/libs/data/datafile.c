#include "data.h"
#include "config.h"

DataResult _get_data_with_fs_method(DataOutput**){
    dataDebugLogger("Starting to extract data with filesystem method [event:_get_data_with_fs_method]");
    FILE *file;

    dataDebugLogger("Opening file in filesystem path: %s [event:_get_data_with_fs_method]", g_config.fs_data_path);
    file = fopen(g_config.fs_data_path, "r");

    if (file == NULL) {
        dataDebugLogger("ERROR: Cannot open file in path: %s [event:_get_data_with_fs_method]", g_config.fs_data_path);
        return DATA_RESULT_ERROR;
    }

    *dataOutput = create_data_output(file);
    return DATA_RESULT_OK;
}