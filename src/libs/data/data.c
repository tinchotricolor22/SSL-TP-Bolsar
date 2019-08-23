#include "data.h"
#include "config.h"
#include "stdlib.h"

void initData(Logger debugLogger) {
    FSPath = g_config.fs_data_path;
    dataDebugLogger = debugLogger;
}

DataOutput *createDataOutput(FILE* file) {
    DataOutput *newOutput = malloc(sizeof *newOutput);
    newOutput->file = file;
    return newOutput;
}
