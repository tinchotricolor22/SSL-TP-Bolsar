#include "data.h"
#include "config.h"
#include "stdlib.h"

void initData(Logger debugLogger) {
    UserOS = getUserOS();
    FSPath = getParserFSPath();
    URL = getParserURL();
    dataDebugLogger = debugLogger;
}

DataOutput *createDataOutput(FILE* file) {
    DataOutput *newOutput = malloc(sizeof *newOutput);
    newOutput->file = file;
    return newOutput;
}
