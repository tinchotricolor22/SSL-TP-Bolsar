#include "data.h"

DataResult getDataWithFSMethod(DataOutput** dataOutput){
    dataDebugLogger("Starting to extract data with filesystem method [event:getDataWithFSMethod]");
    FILE *file;

    dataDebugLogger("Opening file in filesystem path: %s [event:getDataWithFSMethod]", FSPath);
    file = fopen(FSPath, "r");

    if (file == NULL) {
        dataDebugLogger("ERROR: Cannot open file in path: %s [event:getDataWithFSMethod]", FSPath);
        return DATA_RESULT_ERROR;
    }

    *dataOutput = createDataOutput(file);
    return DATA_RESULT_OK;
}