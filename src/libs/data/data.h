#ifndef DATA_H
#define DATA_H

#include "../logging/logging.h"
#include "stdio.h"

#define DATA_RESULT_OK 0
#define DATA_RESULT_ERROR 1

//DataOutput represents the output of data methods
typedef struct DataOutput{
    FILE* file;
} DataOutput;

//DataResult represents the result of data methods
typedef int DataResult;

//DataMethod represents the data methods
typedef DataResult (*DataMethod)(DataOutput**);

//data_debug_logger is logger for data
Logger data_debug_logger;

//init_data inits data_debug_logger
void init_data(const Logger);

//_get_data_with_online_method uses online method with WGET
//returns DATA_RESULT and fills DataOutput
DataResult _get_data_with_online_method(DataOutput**);

//_get_data_with_fs_method uses FS method
//returns DATA_RESULT and fills DataOutput
DataResult _get_data_with_fs_method(DataOutput**);

//create_data_output creates data output from file
DataOutput *create_data_output(FILE*);

#endif
