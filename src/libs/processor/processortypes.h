#ifndef PROCESSOR_TYPES_HEADER
#define PROCESSOR_TYPES_HEADER

#include "../exporter/exportertypes.h"
#include "../parser/parser.h"
#include "../formatter/formattertypes.h"
#include "../data/datatypes.h"
#include "../filter/filter.h"

#define PROCESS_OK 0
#define PROCESS_ERROR_DATA 1
#define PROCESS_ERROR_PARSER 2
#define PROCESS_ERROR_FILTER 3
#define PROCESS_ERROR_EXPORTER 4

typedef struct ProcessParams {
    DataMethod dataMethod;
    ParserMethod parserMethod;
    ExporterMethod exporterMethod;
    Formatter *formatter; //TODO:Estos dos últimos pueden ir en un type que sea view params
    ExporterColumns *columns;
    Filter **filters;
    int filters_length;
} ProcessParams;

typedef int ProcessResult;

#endif