#include "data.h"
#include "config.h"

DataResult getDataWithOnlineMethod(DataOutput **dataOutput) {
    dataDebugLogger("Executing command %s [event:getDataWithOnlineMethod]", g_config.wget_cmd);
    FILE *file = popen(g_config.wget_cmd, "r");

    if (file == NULL) {
        dataDebugLogger("ERROR: Command error [event:getDataWithOnlineMethod]", FSPath);
        return DATA_RESULT_ERROR;
    }

    *dataOutput = createDataOutput(file);
    return DATA_RESULT_OK;
}