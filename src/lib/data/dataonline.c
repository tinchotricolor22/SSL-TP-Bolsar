#include "data.h"
#include "config.h"

DataResult getDataWithOnlineMethod(DataOutput **dataOutput) {
    FILE *file = popen(ONLINE_CMD, "r");

    if (file == NULL) {
        dataDebugLogger("ERROR: Cannot open file in path: %s [event:getDataWithOnlineMethod]", FSPath);
        return DATA_RESULT_ERROR;
    }

    *dataOutput = createDataOutput(file);
    return DATA_RESULT_OK;
}