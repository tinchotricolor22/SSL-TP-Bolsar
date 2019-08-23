#include "data.h"
#include "config.h"
#include "stdlib.h"

void init_data(Logger debugLogger) {
    FSPath = g_config.fs_data_path;
    dataDebugLogger = debugLogger;
}

DataOutput *create_data_output(FILE* file) {
    DataOutput *newOutput = malloc(sizeof *newOutput);
    newOutput->file = file;
    return newOutput;
}
