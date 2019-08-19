#ifndef DATA_H
#define DATA_H

#include "datatypes.h"
#include "../logging/logging.h"

char *UserOS;
char *URL;
char *FSPath;

Logger dataDebugLogger;

void initData(Logger debugLogger);

DataResult getDataWithOnlineMethod(DataOutput**);
DataResult getDataWithFSMethod(DataOutput**);

DataOutput *createDataOutput(FILE* file);

#endif
