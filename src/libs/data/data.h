#ifndef DATA_H
#define DATA_H

#include "../logging/logging.h"
#include "stdio.h"

#define DATA_RESULT_OK 0
#define DATA_RESULT_ERROR 1

typedef struct DataOutput{
    FILE* file;
} DataOutput;

typedef int DataResult;
typedef DataResult (*DataMethod)(DataOutput**);

Logger dataDebugLogger;
void init_data(Logger);

DataResult _get_data_with_online_method(DataOutput**);
DataResult _get_data_with_fs_method(DataOutput**);

DataOutput *create_data_output(FILE* file);

#endif
