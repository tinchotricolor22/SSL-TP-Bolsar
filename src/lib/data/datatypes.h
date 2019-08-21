#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#define DATA_RESULT_OK 0
#define DATA_RESULT_ERROR 1

#include "stdio.h"

typedef struct DataOutput{
    FILE* file;
} DataOutput;

typedef int DataResult;

typedef DataResult (*DataMethod)(DataOutput*);

#endif
